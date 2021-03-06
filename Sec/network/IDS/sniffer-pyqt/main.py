# -*- coding: utf8 -*-

from PyQt5 import QtCore,QtGui,QtWidgets
from PyQt5.QtCore import *
from PyQt5.QtGui import *
from PyQt5.QtWidgets import *
from Ui_main import *

# import alarm
from scapy.all import *
import os
import time
import multiprocessing
from scapy.layers import http
import numpy as np
import matplotlib.pyplot as plt

import pcapy
import argparse
import logging
import scapy
from re import findall
from scapy.all import *
from base64 import b64decode
from datetime import datetime

# Static Global Vars
NULL_FLAG = 0b00000000
FIN_FLAG = 0b00000001
XMAS_FLAG = 0b00101001
HTTP_AUTH_KEYWD = "Authorization: Basic"
NIKTO_KEYWORDS = ["Nikto", "nikto", "NIKTO"]
SHOCK_KEYWORDS = ["() { :; };", "(){:;};", "() { :;};", "() { : ; } ;", "() {:; };"]
USER_KEYWORDS = ["mac", "log", "login", "wpname", "ahd_username", "unickname", "nickname", "user", "user_name", "alias",
                 "pseudo", "email", "username", "_username", "userid", "form_loginname", "loginname", "login_id",
                 "loginid", "session_key", "sessionkey", "pop_login", " uid", " id", "user_id", "screenname", "uname",
                 "ulogin", "acctname", "account", "member", "mailaddress", "membername", "login_username",
                 "login_email", "loginusername", "loginemail", "uin", "sign-in"]
PASS_KEYWORDS = ["pass", "ahd_password", "pass password", "_password passwd", "session_password", "sessionpassword",
                 "login_password", "loginpassword", "form_pw", "pw", "userpassword", "pwd", "upassword",
                 "login_password", "passwort", "passwrd", "wppassword", "upasswd"]
PROTOCOLS = ["HOPOPT", "ICMP", "IGMP", "GGP", "IPv4", "ST", "TCP", "CBT", "EGP", "IGP", "BBN-RCC-MON", "NVP-II", "PUP",
             "ARGUS", "EMCON", "XNET", "CHAOS", ]
LOG = "logs\\{{{}}}.log"

# Dynamic Global Vars
ALERT_COUNTER = 1
tempUserPass = ''


# Packet class
#
# Holds information from the packet so the instance of a Scapy Packet does not need to be passed around.
class Packet:
    srcIP = ''
    protocol = ''
    rawData = ''
    flags = 0x00

    def __init__(self, in_packet):
        self.srcIP = str(in_packet[IP].src)
        self.protocol = int(in_packet.proto)
        self.rawData = str(in_packet)
        self.flags = in_packet[TCP].flags


# print_alert()
#
# Prints an alert pertinent to what was picked up on the alarm.
def print_alert(scan_type, src, proto, payload):
    global ALERT_COUNTER

    ALERT_COUNTER += 1
    if payload == "":
        print("ALERT #%d: %s is detected from %s (%s)!" % (ALERT_COUNTER, scan_type, src, PROTOCOLS[proto]))
        logging.info("ALERT #%d: %s is detected from %s (%s)!" % (ALERT_COUNTER, scan_type, src, PROTOCOLS[proto]
                                                                   ))
    else:
        print("ALERT #%d: %s from %s (%s) !" % (ALERT_COUNTER, scan_type, src, PROTOCOLS[proto] ))
        logging.info("ALERT #%d: %s from %s (%s)!" % (ALERT_COUNTER, scan_type, src, PROTOCOLS[proto]))


# scan_check()
#
# Checks given Packet object for traces of a NULL, FIN, or XMAS nmap stealthy scan. Does this by checking what flags are
# set in the TCP layer, which will allow for the detection of a stealthy scan. Calls on print_alert() if packet seems to
# be from an nmap stealth scan.
def scan_check(in_packet):
    global ALERT_COUNTER

    if in_packet.flags == NULL_FLAG:  # NULL SCAN
        print("NULL scan detected from " + in_packet.srcIP)
        # print_alert("NULL scan", in_packet.srcIP, in_packet.protocol, "aaa")
        # print("NULL scan"+ in_packet.srcIP+ in_packet.protocol)
        return 1
    elif in_packet.flags == FIN_FLAG:  # FIN SCAN
        # print_alert("FIN scan", in_packet.srcIP, in_packet.protocol, "aaa")
        print("FIN scan detected")
        return 1
    elif in_packet.flags == XMAS_FLAG:  # XMAS SCAN
        # print_alert("XMAS scan", in_packet.srcIP, in_packet.protocol, "aaa")
        print("XMAS scan detected")
        return 1


# nikto_check()
#
# Checks given Packet object for traces of a Nikto scan. Does this by checking for references to keywords associated
# with the Nikto program (NIKTO_KEYWORDS) to identify a Nikto scan.
def nikto_check(in_packet):
    global ALERT_COUNTER

    for keyword in NIKTO_KEYWORDS:
        if keyword in in_packet.rawData:
            print_alert("Nikto scan", in_packet.srcIP, in_packet.protocol, "")


# get_shock_script()
#
# Helper function to obtain the command that was attempted to be run in a Shellshock attack. Used by shellshock_check().
def get_shock_script(packet_data):
    shellshock_line = ""  # Return empty string if not found

    data = packet_data.splitlines()
    for line in data:
        for keyword in SHOCK_KEYWORDS:
            if keyword in line:
                shellshock_line = line
                break

    return shellshock_line


# shellshock_check()
#
# Checks a packet for traces of a Shellshock attack. Does this by looking for shellshock entry queries.
def shellshock_check(in_packet):
    global ALERT_COUNTER

    for keyword in SHOCK_KEYWORDS:
        if keyword in in_packet.rawData:
            print_alert("Shellshock attack", in_packet.srcIP, in_packet.protocol,
                        get_shock_script(in_packet.rawData))
            return 1


# get_username()
#
# Returns the username that was found in the raw data of a network packet. Helper function to find_user_pass().
def get_username(raw_data):
    words = str(raw_data).split()

    for i in range(len(words)):
        for keyword in USER_KEYWORDS:
            if keyword in words[i].lower():
                # coolder modified
                # return words[i + 1]
                return words[i]


# getPassword()
#
# Returns the password that was found in the raw data of a network packet. Helper function to find_user_pass().
def get_password(raw_data):
    words = str(raw_data).split()

    for i in range(len(words)):
        for keyword in PASS_KEYWORDS:
            if keyword in words[i].lower():
                # return words[i + 1]
                return words[i]


# find_user_pass()
#
# Helper function to user_pass_check, where after it is determined that a username and password was sent in the clear,
# it will call on this function in order to find the username and password combination (even if split between packets)
# and calls on the print_alert() function.
def find_user_pass(raw_packet, parsed_packet):
    global ALERT_COUNTER, tempUserPass
    raw_data = parsed_packet.getlayer(Raw)  # Get only the Raw layer of the raw_packet

    for keyword in USER_KEYWORDS:
        if keyword in str(raw_data).lower():
            username = get_username(raw_data)
            tempUserPass = username

    for keyword in PASS_KEYWORDS:
        if keyword in str(raw_data).lower():
            password = get_password(raw_data)
            user_pass = tempUserPass + ":" + password

            if not check_if_printable(user_pass):
                continue

            tempUserPass = ""
            print_alert("Username and password sent in the clear", raw_packet.srcIP, raw_packet.protocol, user_pass)
            tempUserPass = ""


# check_if_printable()
#
# In order to try and decrease false positives for credentials sent in-the-clear, check if the username and password are
# ASCII characters and non-control characters
def check_if_printable(username_password):
    try:
        for character in username_password:
            # Check that credentials only use extended-ASCII and non-control characters
            if ord(character) > 255 or ord(character) < 32:
                return False
    # Unable to get char value
    except TypeError:
        return False

    return True


# user_pass_check()
#
# Checks whether or not credentials have been sent in-the-clear. If it believes
# there are credentials in the packet, sends to find_user_pass() to find and
# report them.
def user_pass_check(raw_packet, parsed_packet):
    global ALERT_COUNTER, tempUserPass

    # print("user pass fun called")
    data = raw_packet.rawData.splitlines()
    for line in data:

        for user_keyword in USER_KEYWORDS:
            if user_keyword in line:
                return True

        for pass_keyword in PASS_KEYWORDS:
            if pass_keyword in line:
                return True
        # if HTTP_AUTH_KEYWD in line:
        # words = line.split()
        # user_pass = words[2]
        # if ((len(user_pass) % 4) == 0) and (user_pass[-1] == '='):
        #     if not check_if_printable(user_pass):
        #         pass
        #     return TRUE
            # print_alert("Username and password sent in-the-clear", raw_packet.srcIP, raw_packet.protocol,
                        # b64decode(user_pass))
        # if USER_KEYWORDS in line  or PASS_KEYWORDS in line:
        #     return TRUE

    # raw_data = str(parsed_packet.getlayer(Raw))
    # for keyword in USER_KEYWORDS:
    #     if keyword in raw_data.lower() or (len(tempUserPass) > 1):
    #         # find_user_pass(raw_packet, parsed_packet)
    #         return TRUE


# credit_card_check()
#
# Checks whether or not credit card numbers have been sent in-the-clear. If it believes
# there are credentials in the packet,
def credit_card_check(in_packet):
    data = in_packet.rawData.splitlines()

    for line in data:

        visa_num = findall('4[0-9]{12}(?:[0-9]{3})?', str(line))
        mastercard_num = findall('(?:5[1-5][0-9]{2}|222[1-9]|22[3-9][0-9]|2[3-6][0-9]{2}|27[01][0-9]|2720)[0-9]{12}', str(line))
        diners_club_num = findall('3(?:0[0-5]|[68][0-9])[0-9]{11}', str(line))
        discover_num = findall('6(?:011|5[0-9]{2})[0-9]{12}', str(line))
        jcb_num = findall('(?:2131|1800|35\d{3})\d{11}', str(line))
        american_express_num = findall('3[47][0-9]{13}', str(line))
        bcglobal_num = findall('^(6541|6556)[0-9]{12}', str(line))
        korean_local_num = findall('^9[0-9]{15}', str(line))
        laser_card_num = findall('^(6304|6706|6709|6771)[0-9]{12,15}', str(line))
        maestro_num = findall('^(5018|5020|5038|6304|6759|6761|6763)[0-9]{8,15}', str(line))
        union_pay_num = findall('^(62[0-9]{14,17})', str(line))

        if visa_num or mastercard_num or diners_club_num:
            return True



# sniff_packet()
#
# Sniffs a given packet. Will call on four functions to protect against: nmap
# stealthy scans, Nikto scans, Shellshock attacks, and credentials sent
# in-the-clear.
def sniff_packet(in_packet):
    temp_packet = Packet(in_packet)

    scan_check(temp_packet)
    nikto_check(temp_packet)
    shellshock_check(temp_packet)
    user_pass_check(temp_packet, in_packet)
    credit_card_check(temp_packet)


def packet_callback(in_packet):
    try:
        sniff_packet(in_packet)
    except IndexError:
        pass
    ## except StandardError:
    ##     pass


isDDOSCheckBoxChecked = False
isPlainInfoCheckBoxChecked = False
isUserCheckBoxChecked = False
isCreditCheckBoxChecked = False
isScanAttackCheckBoxChecked = False
isForkBoomCheckBoxChecked = False




class SnifferMainWindow(Ui_MainWindow,QtWidgets.QMainWindow):
    filter = ""   #????????????
    iface = ""   #??????
    packetList = []
    q = multiprocessing.Queue()
    def __init(self):
        super(SnifferMainWindow,self).__init__()

    def setupUi(self, MainWindow):
        super(SnifferMainWindow, self).setupUi(MainWindow)

        #col = self.tableWidget.columnCount()
        self.tableWidget.insertColumn(7)
        self.tableWidget.setColumnHidden(7,True)#?????????????????????
        self.tableWidget.horizontalHeader().setSectionsClickable(False) #??????????????????????????????
        #self.tableWidget.horizontalHeader().setStyleSheet('QHeaderView::section{background:green}')#?????????????????????????????????
        self.tableWidget.setSelectionBehavior(QtWidgets.QAbstractItemView.SelectRows) #?????? ???????????????????????????????????????????????????
        self.tableWidget.setEditTriggers(QtWidgets.QAbstractItemView.NoEditTriggers) #????????????????????????
        self.tableWidget.verticalHeader().setVisible(False) #??????????????????
        self.tableWidget.setColumnWidth(0,60)
        self.tableWidget.setColumnWidth(2,150)
        self.tableWidget.setColumnWidth(3,150)
        self.tableWidget.setColumnWidth(4,60)
        self.tableWidget.setColumnWidth(5,60)
        self.tableWidget.setColumnWidth(6,600)

        self.treeWidget.setHeaderHidden(True) #????????????
        self.treeWidget.setColumnCount(1)

        MainWindow.setWindowIcon(QtGui.QIcon('./img/title'))


    #???????????????
    def setSlot(self):
        self.tableWidget.itemClicked.connect(self.clickInfo)  #????????????
        # ?????????ContextMenuPolicy?????????Qt.CustomContextMenu
        # ??????????????????customContextMenuRequested??????
        self.tableWidget.setContextMenuPolicy(Qt.CustomContextMenu)
        self.tableWidget.customContextMenuRequested.connect(self.showContextMenu)

        # ??????QMenu
        self.contextMenu = QMenu(self.tableWidget)
        self.pdfdumpActionA = self.contextMenu.addAction(u'?????????pdf')
        # ?????????????????????????????????
        # ??????????????????????????????action????????????????????????????????????
        # ???????????????????????????????????????????????????????????????????????????
        self.pdfdumpActionA.triggered.connect(self.pdfdump)

        global count
        count = 0
        global display
        display = 0
        self.timer = QTimer(self)
        self.timer.timeout.connect(self.statistics)
        #????????????
        self.timer.start(1000)

        self.comboBoxIface = QComboBox()
        self.toolBar.addWidget(self.comboBoxIface)
        self.LookupIface()

        startAction = QAction(QIcon('./img/start'),'&????????????(Ctrl+E)',self)
        startAction.setShortcut('Ctrl+E')
        startAction.triggered.connect(self.Start)
        self.toolBar.addAction(startAction)

        stopAction = QAction(QIcon('./img/stop'),'&????????????(Ctrl+Q)',self)
        stopAction.setShortcut('Ctrl+Q')
        stopAction.triggered.connect(self.Stop)
        self.toolBar.addAction(stopAction)

        preFilterAction = QAction(QIcon('./img/PreFilter'),'&????????????(Ctrl+T)',self)
        preFilterAction.setShortcut('Ctrl+T')
        preFilterAction.triggered.connect(self.PreFilter)
        self.toolBar.addAction(preFilterAction)

        postFilterAction = QAction(QIcon('./img/PostFilter'),'&????????????(Ctrl+F)',self)
        postFilterAction.setShortcut('Ctrl+F')
        postFilterAction.triggered.connect(self.PostFilter)
        self.toolBar.addAction(postFilterAction)

        saveAction = QAction(QIcon('./img/save'),'&??????(Ctrl+S)',self)
        saveAction.setShortcut('Ctrl+S')
        saveAction.triggered.connect(self.savePackets)
        self.toolBar.addAction(saveAction)

        statisticsAction = QAction(QIcon('./img/statistics'),'&????????????(Ctrl+G)',self)
        statisticsAction.setShortcut('Ctrl+G')
        statisticsAction.triggered.connect(self.statisticsMenu)
        self.toolBar.addAction(statisticsAction)

        aboutAction = QAction(QIcon('./img/about'),'&??????(Ctrl+B)',self)
        aboutAction.setShortcut('Ctrl+B')
        aboutAction.triggered.connect(self.about)
        self.toolBar.addAction(aboutAction)

        self.checkBoxDDOS.stateChanged.connect(self.choose)
        self.checkBoxCredit.stateChanged.connect(self.choose)
        self.checkBoxForkBoom.stateChanged.connect(self.choose)
        self.checkBoxScanAttack.stateChanged.connect(self.choose)
        self.checkBoxUser.stateChanged.connect(self.choose)



    def choose(self):
        # QMessageBox(text="ddos checked").exec() if self.checkBoxDDOS.isChecked() else QMessageBox(text="ddos not checked").exec()
        global isDDOSCheckBoxChecked
        global isPlainInfoCheckBoxChecked
        global isUserCheckBoxChecked
        global isCreditCheckBoxChecked
        global isScanAttackCheckBoxChecked
        global isForkBoomCheckBoxChecked

        if self.checkBoxDDOS.isChecked():
            isDDOSCheckBoxChecked = True
        else:
            isDDOSCheckBoxChecked = False

        if self.checkBoxForkBoom.isChecked():
            isForkBoomCheckBoxChecked = True
        else:
            isForkBoomCheckBoxChecked = False

        if self.checkBoxUser.isChecked():
            isUserCheckBoxChecked = True
        else:
            isUserCheckBoxChecked = False

        if self.checkBoxCredit.isChecked():
            isCreditCheckBoxChecked = True
        else:
            isCreditCheckBoxChecked = False


        if self.checkBoxScanAttack.isChecked():
             isScanAttackCheckBoxChecked = True
        else:
             isScanAttackCheckBoxChecked = False


    def about(self):
        msg = QMessageBox()
        msg.setWindowTitle("?????????")
        msg.setText("??????: xxxxx\nEmail:xxxx.com")
        msg.exec()

    #??????????????????
    def statisticsMenu(self):
        list = ["?????????", "?????????"]

         #????????????????????? ??????????????? ???QLineEdit.Normal????????????????????? QLineEdit. Password?????????????????????????????? QLineEdit. NoEcho???
        #stringNum,ok3 = QInputDialog.getText(self, "??????","??????:",QLineEdit.Normal, "?????????")
         #1???????????????????????????True/False  ???????????????????????????
        item, ok = QInputDialog.getItem(self, "??????","????????????", list, 1, False)
        if ok:
            if item =="?????????"  :
                ip = 0
                arp = 0
                count = 0
                for pkt in self.packetList:
                    if pkt.type == 0x800:
                        ip += 1
                        count += 1
                    elif pkt.type == 0x806:
                        arp += 1
                        count += 1
                ipPercent = '{:.1f}'.format(ip/count)
                arpPercent = '{:.1f}'.format(arp/count)
                plt.rcParams['font.sans-serif']=['SimHei'] #??????????????????????????????
                plt.rcParams['axes.unicode_minus']=False #????????????????????????
                labels = 'IP(%s)' % ip ,'ARP(%s)' % arp
                fracs = [ipPercent,arpPercent]
                explode = [0,0]#??????,????????????????????????
                plt.axes(aspect=1)#?????????aspect=1?????????????????????????????????????????????????????????
                plt.pie(x=fracs, labels=labels, explode=explode, autopct='%3.1f %%',
                    shadow=True, labeldistance=1.1, startangle=90, pctdistance=0.6
                )
                '''
                labeldistance???????????????????????????????????????1.1???1.1??????????????????
                autopct??????????????????????????????%3.1f%%???????????????????????????????????????????????????
                shadow?????????????????????
                startangle??????????????????0????????????0???????????????????????????????????????????????????90?????????????????????
                pctdistance???????????????text??????????????????
                patches, l_texts, p_texts????????????????????????????????????p_texts????????????????????????l_texts?????????label?????????
                '''
                plt.title("???????????????(?????????%s)" %count)
                plt.show()
            elif item =="?????????":
                tcp = 0
                udp = 0
                icmp = 0
                igmp = 0
                count = 0
                for pkt in self.packetList:
                    if pkt.haslayer('IP') and pkt[IP].proto == 6:
                        tcp += 1
                        count += 1
                    elif pkt.haslayer('IP') and pkt[IP].proto == 17:
                        udp += 1
                        count += 1
                    elif pkt.haslayer('IP') and pkt[IP].proto == 1:
                        icmp += 1
                        count += 1
                    elif pkt.haslayer('IP') and pkt[IP].proto == 2:
                        igmp += 1
                        count += 1
                tcpPercent = '{:.1f}'.format(tcp/count)
                udpPercent = '{:.1f}'.format(udp/count)
                icmpPercent = '{:.1f}'.format(icmp/count)
                igmpPercent = '{:.1f}'.format(igmp/count)
                plt.rcParams['font.sans-serif']=['SimHei'] #??????????????????????????????
                plt.rcParams['axes.unicode_minus']=False #????????????????????????
                labels = 'TCP(%s)' % tcp ,'UDP(%s)' % udp ,'ICMP(%s)' % icmp ,'IGMP(%s)' % igmp
                fracs = [tcpPercent,udpPercent,icmpPercent,igmpPercent]
                explode = [0,0,0,0]#??????,????????????????????????
                plt.axes(aspect=1)#?????????aspect=1?????????????????????????????????????????????????????????
                plt.pie(x=fracs, labels=labels, explode=explode, autopct='%3.1f %%',
                    shadow=True, labeldistance=1.1, startangle=90, pctdistance=0.6
                )
                '''
                labeldistance???????????????????????????????????????1.1???1.1??????????????????
                autopct??????????????????????????????%3.1f%%???????????????????????????????????????????????????
                shadow?????????????????????
                startangle??????????????????0????????????0???????????????????????????????????????????????????90?????????????????????
                pctdistance???????????????text??????????????????
                patches, l_texts, p_texts????????????????????????????????????p_texts????????????????????????l_texts?????????label?????????
                '''
                plt.title("???????????????(???????????????%s)" % count)
                plt.show()



    #?????????????????????
    def savePackets(self):
        path, filetype = QtWidgets.QFileDialog.getSaveFileName(None,
                                    "??????????????????",
                                    "./",
                                    "pcap??????(*.cap);;??????(*)")
        if path == "":
            return
        if os.path.exists(os.path.dirname(path)) == False:
            QtWidgets.QMessageBox.critical(None,"??????","???????????????")
            return
        packets = scapy.plist.PacketList(self.packetList)
        wrpcap(path,packets)
        QtWidgets.QMessageBox.information(None,"??????","????????????")

    #????????????????????????
    def showContextMenu(self,pos):
        '''
        ??????????????????????????????
        '''
        # ??????????????????????????????????????????????????????
        # self.contextMenu.move(self.pos() + pos)
        self.contextMenu.exec_(QCursor.pos())
    #?????????????????????pdf
    def pdfdump(self):
        '''
        ??????????????????action???????????????
        '''
        row = self.tableWidget.currentRow()     #??????????????????
        p = self.tableWidget.item(row,7).text()
        packet = scapy.layers.l2.Ether(p.encode('Windows-1252'))
        path, filetype = QtWidgets.QFileDialog.getSaveFileName(None,
                                    "??????????????????",
                                    "./",
                                    "pdf??????(*.pdf);;??????(*)")
        if path == "":
            return
        if os.path.exists(os.path.dirname(path)) == False:
            QtWidgets.QMessageBox.critical(None,"??????","???????????????")
            return
        self.pdfdumpThread = pdfdumpThread(packet,path)
        self.pdfdumpThread.pdfdumpSignal.connect(self.pdfdumpFinish)
        self.pdfdumpThread.start()

    #pdfdump??????????????????
    def pdfdumpFinish(self,info):
        if info == True:
            QtWidgets.QMessageBox.information(None,"??????","????????????")


    #????????????
    def Start(self):
        global count
        count = 0
        global display
        display = 0
        self.packetList = []

        self.startTime = time.time()
        self.iface = self.comboBoxIface.currentText()

        self.tableWidget.setRowCount(0)
        self.tableWidget.removeRow(0)

        self.SnifferThread = SnifferThread(self.filter,self.iface)
        self.SnifferThread.HandleSignal.connect(self.display)
        self.SnifferThread.start()






    #????????????????????????
    def display(self,packet):



        # if self.checkBoxDDOS.isChecked():
        #     QMessageBox("ddos checked")
        global count
        global display
        packetTime = '{:.7f}'.format(packet.time - self.startTime)
        type = packet.type

        if type == 0x800 :
            count += 1
            display = count
            row = self.tableWidget.rowCount()
            self.tableWidget.insertRow(row)
            self.tableWidget.setItem(row,0, QtWidgets.QTableWidgetItem(str(count)))
            self.tableWidget.setItem(row,1,QtWidgets.QTableWidgetItem(str(packetTime)))
            self.tableWidget.setItem(row,2, QtWidgets.QTableWidgetItem(packet[IP].src))
            self.tableWidget.setItem(row,3, QtWidgets.QTableWidgetItem(packet[IP].dst))
            self.tableWidget.setItem(row,5, QtWidgets.QTableWidgetItem(str(len(packet))))

            '''
            # import chardet
            # print(chardet.detect(raw(packet)))
            ??????????????????
          '''

            '''
            ?????????????????????????????????????????????????????????????????????????????????????????????????????????gb2312???????????????????????????decode???????????????????????????????????????????????????decode('gb18030')????????????????????????????????????????????????????????????????????????????????????decode????????????????????????????????????????????? String??????s???gbk???????????????UTF-8?????????????????????
            `s.decode('gbk').encode('utf-8???) `
            ??????????????????????????????????????????????????????????????????????????????
            >UnicodeDecodeError: ???gbk' codec can't decode bytes in position 30664-30665: illegal multibyte sequence

            ????????????????????????????????????????????????????????????C/C++?????????????????????***????????????***?????????????????????????????????????????????`\xa3\xa0`?????????`\xa4\x57`????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????`\xa1\xa1`???????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????? ???????????????
            `s.decode('gbk', ???ignore').encode('utf-8???) `
            ??????decode?????????????????? `decode([encoding], [errors='strict'])`??????????????????????????????????????????????????????????????????????????????strict?????????????????????????????????????????????

            * ???????????????ignore??????????????????????????????
            * ???????????????replace??????????????????????????????????
            * ???????????????xmlcharrefreplace????????????XML??????????????????

            ?????????

            * http://blog.chinaunix.net/u2/68206/showart.php?id=668359
            * http://www.pythonclub.org/python-basic/codec
            * http://www.pythonclub.org/python-scripts/quanjiao-banjiao
            * http://www.pythonclub.org/python-basic/chardet
            Edit By [MaHua](http://mahua.jser.me)
           '''

            self.tableWidget.setItem(row,7, QtWidgets.QTableWidgetItem(raw(packet).decode('Windows-1252','ignore')))

            #TCP
            if packet[IP].proto == 6:


                temp_packet = Packet(packet)

                if isDDOSCheckBoxChecked:
                    a = 1
                    #print("Hll")
                    # DDOS
                if isForkBoomCheckBoxChecked:
                    if shellshock_check(temp_packet):
                        row = self.tableWidgetAttackInfo.rowCount()
                        self.tableWidgetAttackInfo.insertRow(row)
                        self.tableWidgetAttackInfo.setItem(row,0, QtWidgets.QTableWidgetItem(str(count)))
                        self.tableWidgetAttackInfo.setItem(row,1, QtWidgets.QTableWidgetItem(packet[IP].src))
                        self.tableWidgetAttackInfo.setItem(row,2, QtWidgets.QTableWidgetItem(packet[IP].dst))
                        self.tableWidgetAttackInfo.setItem(row,3, QtWidgets.QTableWidgetItem(str("fork boom!!!")))

                if isUserCheckBoxChecked:
                    # print(isUserCheckBoxChecked)
                    # print("Hello, user check enable")
                    if user_pass_check(temp_packet, packet):
                        row = self.tableWidgetAttackInfo.rowCount()
                        self.tableWidgetAttackInfo.insertRow(row)
                        self.tableWidgetAttackInfo.setItem(row,0, QtWidgets.QTableWidgetItem(str(count)))
                        self.tableWidgetAttackInfo.setItem(row,1, QtWidgets.QTableWidgetItem(packet[IP].src))
                        self.tableWidgetAttackInfo.setItem(row,2, QtWidgets.QTableWidgetItem(packet[IP].dst))
                        self.tableWidgetAttackInfo.setItem(row,3, QtWidgets.QTableWidgetItem(str("username or passwd leak")))

                if isCreditCheckBoxChecked:
                    # print("Hello, credit check enable")
                    if credit_card_check(temp_packet):
                        row = self.tableWidgetAttackInfo.rowCount()
                        self.tableWidgetAttackInfo.insertRow(row)
                        self.tableWidgetAttackInfo.setItem(row,0, QtWidgets.QTableWidgetItem(str(count)))
                        self.tableWidgetAttackInfo.setItem(row,1, QtWidgets.QTableWidgetItem(packet[IP].src))
                        self.tableWidgetAttackInfo.setItem(row,2, QtWidgets.QTableWidgetItem(packet[IP].dst))
                        self.tableWidgetAttackInfo.setItem(row,3, QtWidgets.QTableWidgetItem(str("credit card leak")))

                if isScanAttackCheckBoxChecked:
                    # print("Hello, scan check enable")
                    if scan_check(temp_packet):
                        row = self.tableWidgetAttackInfo.rowCount()
                        self.tableWidgetAttackInfo.insertRow(row)
                        self.tableWidgetAttackInfo.setItem(row,0, QtWidgets.QTableWidgetItem(str(count)))
                        self.tableWidgetAttackInfo.setItem(row,1, QtWidgets.QTableWidgetItem(packet[IP].src))
                        self.tableWidgetAttackInfo.setItem(row,2, QtWidgets.QTableWidgetItem(packet[IP].dst))
                        self.tableWidgetAttackInfo.setItem(row,3, QtWidgets.QTableWidgetItem(str("scan check")))

                    # nikto_check(packet)
                #HTTP
                if packet[TCP].dport == 80 or packet[TCP].sport == 80:
                    self.tableWidget.setItem(row,4, QtWidgets.QTableWidgetItem('HTTP'))
                    if packet.haslayer('HTTPRequest'):
                        self.tableWidget.setItem(row,6, QtWidgets.QTableWidgetItem('%s %s %s' % (packet.sprintf("{HTTPRequest:%HTTPRequest.Method%}").strip("'"),packet.sprintf("{HTTPRequest:%HTTPRequest.Path%}").strip("'"),packet.sprintf("{HTTPRequest:%HTTPRequest.Http-Version%}").strip("'"))))
                    elif packet.haslayer('HTTPResponse'):
                        self.tableWidget.setItem(row,6, QtWidgets.QTableWidgetItem('%s' % packet.sprintf("{HTTPResponse:%HTTPResponse.Status-Line%}").strip("'")))
                    else:
                        self.tableWidget.setItem(row,6, QtWidgets.QTableWidgetItem(''))
                else:
                    self.tableWidget.setItem(row,4, QtWidgets.QTableWidgetItem('TCP'))
                    if packet.haslayer('TCP'):
                        flag = ''
                        if packet[TCP].flags.A:
                            if flag == '':
                                flag += 'ACK'
                            else:
                                flag += ',ACK'
                        if packet[TCP].flags.R:
                            if flag == '':
                                flag += 'RST'
                            else:
                                flag += ',RST'
                        if packet[TCP].flags.S:
                            if flag == '':
                                flag += 'SYN'
                            else:
                                flag += ',SYN'
                        if packet[TCP].flags.F:
                            if flag == '':
                                flag += 'FIN'
                            else:
                                flag += ',FIN'
                        if packet[TCP].flags.U:
                            if flag == '':
                                flag += 'URG'
                            else:
                                flag += ',URG'
                        if packet[TCP].flags.P:
                            if flag == '':
                                flag += 'PSH'
                            else:
                                flag += ',PSH'
                        if flag == '':
                            self.tableWidget.setItem(row,6, QtWidgets.QTableWidgetItem('%s -> %s Seq???%s Ack???%s Win???%s' % (packet[TCP].sport,packet[TCP].dport,packet[TCP].seq,packet[TCP].ack,packet[TCP].window)))
                        else:
                            self.tableWidget.setItem(row,6, QtWidgets.QTableWidgetItem('%s -> %s [%s] Seq???%s Ack???%s Win???%s' % (packet[TCP].sport,packet[TCP].dport,flag,packet[TCP].seq,packet[TCP].ack,packet[TCP].window)))
            #UDP
            elif packet[IP].proto == 17:
                self.tableWidget.setItem(row,4, QtWidgets.QTableWidgetItem('UDP'))
                self.tableWidget.setItem(row,6, QtWidgets.QTableWidgetItem('%s -> %s ??????(len)???%s' % (packet[UDP].sport,packet[UDP].dport,packet[UDP].len)))
            #ICMP
            elif packet[IP].proto == 1:
                self.tableWidget.setItem(row,4, QtWidgets.QTableWidgetItem('ICMP'))
                if packet.haslayer('ICMP'):
                    if packet[ICMP].type == 8:
                        self.tableWidget.setItem(row,6, QtWidgets.QTableWidgetItem('Echo (ping) request id???%s seq???%s' % (packet[ICMP].id,packet[ICMP].seq)))
                    elif packet[ICMP].type == 0:
                        self.tableWidget.setItem(row,6, QtWidgets.QTableWidgetItem('Echo (ping) reply id???%s seq???%s' % (packet[ICMP].id,packet[ICMP].seq)))
                    else:
                        self.tableWidget.setItem(row,6, QtWidgets.QTableWidgetItem('type???%s id???%s seq???%s' % (packet[ICMP].type,packet[ICMP].id,packet[ICMP].seq)))
            #IGMP
            elif packet[IP].proto == 2:
                self.tableWidget.setItem(row,4, QtWidgets.QTableWidgetItem('IGMP'))
                self.tableWidget.setItem(row,6, QtWidgets.QTableWidgetItem(''))
            #????????????
            else:
                self.tableWidget.setItem(row,4, QtWidgets.QTableWidgetItem(str(packet[IP].proto)))

            #????????????
            self.colorItem(row,packet)

            #??????packetList???
            self.packetList.append(packet)
        #ARP
        elif type == 0x806 :
            count += 1
            display = count
            row = self.tableWidget.rowCount()
            self.tableWidget.insertRow(row)
            self.tableWidget.setItem(row,0, QtWidgets.QTableWidgetItem(str(count)))
            self.tableWidget.setItem(row,1,QtWidgets.QTableWidgetItem(str(packetTime)))
            self.tableWidget.setItem(row,2, QtWidgets.QTableWidgetItem(packet[ARP].psrc))
            self.tableWidget.setItem(row,3, QtWidgets.QTableWidgetItem(packet[ARP].pdst))
            self.tableWidget.setItem(row,4, QtWidgets.QTableWidgetItem('ARP'))
            self.tableWidget.setItem(row,5, QtWidgets.QTableWidgetItem(str(len(packet))))
            if packet[ARP].op == 1:  #request
                self.tableWidget.setItem(row,6, QtWidgets.QTableWidgetItem('Who has %s? Tell %s' % (packet[ARP].pdst,packet[ARP].psrc)))
            elif packet[ARP].op == 2:  #reply
                self.tableWidget.setItem(row,6, QtWidgets.QTableWidgetItem('%s is at %s' % (packet[ARP].psrc,packet[ARP].hwsrc)))
            self.tableWidget.setItem(row,7, QtWidgets.QTableWidgetItem(raw(packet).decode('Windows-1252','ignore')))

            #????????????
            self.colorItem(row,packet)

            #??????packetList???
            self.packetList.append(packet)


    #????????????
    def colorItem(self,row,packet):
        type = packet.type
        #IP
        if type == 0x800 :
            #IP??????
            if packet.haslayer('IP') == 0:
                for i in range(7):
                    self.tableWidget.item(row,i).setBackground(Qt.black)   #??????????????????
                    self.tableWidget.item(row,i).setForeground(Qt.red)     #??????????????????
            #TCP
            if packet[IP].proto == 6:
                #HTTP
                if packet[TCP].dport == 80 or packet[TCP].sport == 80:
                    #HTTP??????
                    if packet.haslayer('HTTP') == 0:
                        for i in range(7):
                            self.tableWidget.item(row,i).setBackground(Qt.black)   #??????????????????
                            self.tableWidget.item(row,i).setForeground(Qt.red)     #??????????????????
                    else:
                        for i in range(7):
                            self.tableWidget.item(row,i).setBackground(QColor('#99FF99'))   #??????????????????
                else:
                    #TCP??????
                    if packet.haslayer('TCP') == 0:
                        for i in range(7):
                            self.tableWidget.item(row,i).setBackground(Qt.black)   #??????????????????
                            self.tableWidget.item(row,i).setForeground(Qt.red)     #??????????????????
                    #TCP SYN/FIN
                    elif packet[TCP].flags.S or packet[TCP].flags.F:
                        for i in range(7):
                            self.tableWidget.item(row,i).setBackground(QColor('#646464'))   #??????????????????
                    #TCP RST
                    elif packet[TCP].flags.R:
                        for i in range(7):
                            self.tableWidget.item(row,i).setBackground(QColor('#990000'))   #??????????????????
                            self.tableWidget.item(row,i).setForeground(QColor('#FFCC33'))     #??????????????????
                    else:
                        for i in range(7):
                            self.tableWidget.item(row,i).setBackground(QColor('#DDDDDD'))   #??????????????????
            #UDP
            elif packet[IP].proto == 17:
                #UDP??????
                if packet.haslayer('UDP') == 0:
                    for i in range(7):
                        self.tableWidget.item(row,i).setBackground(Qt.black)   #??????????????????
                        self.tableWidget.item(row,i).setForeground(Qt.red)     #??????????????????
                else:
                    for i in range(7):
                        self.tableWidget.item(row,i).setBackground(QColor('#CCFFFF'))   #??????????????????
            #ICMP
            elif packet[IP].proto == 1:
                #ICMP??????
                if packet.haslayer('ICMP') == 0:
                    for i in range(7):
                        self.tableWidget.item(row,i).setBackground(Qt.black)   #??????????????????
                        self.tableWidget.item(row,i).setForeground(Qt.red)     #??????????????????
                #ICMP errors
                elif packet[ICMP].type == 3 or packet[ICMP].type == 4 or packet[ICMP].type == 5 or packet[ICMP].type == 11:
                    for i in range(7):
                        self.tableWidget.item(row,i).setBackground(Qt.black)   #??????????????????
                        self.tableWidget.item(row,i).setForeground(QColor('#66FF66'))     #??????????????????
            #IGMP
            elif packet[IP].proto == 2:
                for i in range(7):
                    self.tableWidget.item(row,i).setBackground(QColor('#FFCCFF'))   #??????????????????
        #ARP
        elif type == 0x806 :
            #ARP??????
            if packet.haslayer('ARP') == 0:
                for i in range(7):
                    self.tableWidget.item(row,i).setBackground(Qt.black)   #??????????????????
                    self.tableWidget.item(row,i).setForeground(Qt.red)     #??????????????????
            else:
                for i in range(7):
                    self.tableWidget.item(row,i).setBackground(QColor('#FFFFCC'))   #??????????????????

    #????????????
    def Stop(self):
        self.SnifferThread.terminate()

    #????????????????????????????????????
    def clickInfo(self):
        row = self.tableWidget.currentRow()     #??????????????????
        p = self.tableWidget.item(row,7).text()
        packet = scapy.layers.l2.Ether(p.encode('Windows-1252'))

        num = self.tableWidget.item(row,0).text()
        Time = self.tableWidget.item(row,1).text()
        length = self.tableWidget.item(row,5).text()
        iface = self.iface
        import time
        timeformat = time.strftime("%Y-%m-%d %H:%M:%S",time.localtime(packet.time))


        #packet.show()

        self.treeWidget.clear()
        self.treeWidget.setColumnCount(1)

        #Frame
        Frame = QtWidgets.QTreeWidgetItem(self.treeWidget)
        Frame.setText(0,'Frame %s???%s bytes on %s' % (num,length,iface))
        FrameIface = QtWidgets.QTreeWidgetItem(Frame)
        FrameIface.setText(0,'???????????????%s' % iface)
        FrameArrivalTime = QtWidgets.QTreeWidgetItem(Frame)
        FrameArrivalTime.setText(0,'???????????????%s' % timeformat)
        FrameTime = QtWidgets.QTreeWidgetItem(Frame)
        FrameTime.setText(0,'????????????????????????%s' % Time)
        FrameNumber = QtWidgets.QTreeWidgetItem(Frame)
        FrameNumber.setText(0,'?????????%s' % num)
        FrameLength = QtWidgets.QTreeWidgetItem(Frame)
        FrameLength.setText(0,'????????????%s' % length)


        #Ethernet
        Ethernet = QtWidgets.QTreeWidgetItem(self.treeWidget)
        Ethernet.setText(0,'Ethernet??????MAC??????(src)???'+ packet.src + '?????????MAC??????(dst)???'+packet.dst)
        EthernetDst = QtWidgets.QTreeWidgetItem(Ethernet)
        EthernetDst.setText(0,'??????MAC??????(dst)???'+ packet.dst)
        EthernetSrc = QtWidgets.QTreeWidgetItem(Ethernet)
        EthernetSrc.setText(0,'???MAC??????(src)???'+ packet.src)

        try:
            type = packet.type
        except:
            type = 0
        #IP
        if type == 0x800 :
            EthernetType = QtWidgets.QTreeWidgetItem(Ethernet)
            EthernetType.setText(0,'????????????(type)???IPv4(0x800)')

            IPv4 = QtWidgets.QTreeWidgetItem(self.treeWidget)
            IPv4.setText(0,'IPv4????????????(src)???'+packet[IP].src+'???????????????(dst)???'+packet[IP].dst)
            IPv4Version = QtWidgets.QTreeWidgetItem(IPv4)
            IPv4Version.setText(0,'??????(version)???%s'% packet[IP].version)
            IPv4Ihl = QtWidgets.QTreeWidgetItem(IPv4)
            IPv4Ihl.setText(0,'????????????(ihl)???%s' % packet[IP].ihl)
            IPv4Tos = QtWidgets.QTreeWidgetItem(IPv4)
            IPv4Tos.setText(0,'????????????(tos)???%s'% packet[IP].tos)
            IPv4Len = QtWidgets.QTreeWidgetItem(IPv4)
            IPv4Len.setText(0,'?????????(len)???%s' % packet[IP].len) #IP?????????????????????????????????????????????????????????????????????
            IPv4Id = QtWidgets.QTreeWidgetItem(IPv4)
            IPv4Id.setText(0,'??????(id)???%s' % packet[IP].id)  #??????????????????????????????????????????????????????????????????????????????????????????????????????IP?????????????????????????????????MTU?????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????
            IPv4Flags = QtWidgets.QTreeWidgetItem(IPv4)
            IPv4Flags.setText(0,'??????(flags)???%s' % packet[IP].flags) #R???DF???MF???????????????????????????????????????DF?????????1?????????????????????0???????????????MF??????1??????????????????????????????0???????????????????????????
            IPv4Frag = QtWidgets.QTreeWidgetItem(IPv4)

            IPv4FlagsDF = QtWidgets.QTreeWidgetItem(IPv4Flags)
            IPv4FlagsDF.setText(0,'?????????(DF)???%s' % packet[IP].flags.DF)
            IPv4FlagsMF = QtWidgets.QTreeWidgetItem(IPv4Flags)
            IPv4FlagsMF.setText(0,'????????????(MF)???%s' % packet[IP].flags.MF)

            IPv4Frag.setText(0,'?????????(frag)???%s ' % packet[IP].frag)  #??????????????????????????????????????????????????????????????????????????????8???
            IPv4Ttl = QtWidgets.QTreeWidgetItem(IPv4)
            IPv4Ttl.setText(0,'????????????(ttl)???%s' % packet[IP].ttl)

            #TCP
            if packet[IP].proto == 6:
                if packet.haslayer('TCP'):
                    IPv4Proto = QtWidgets.QTreeWidgetItem(IPv4)
                    IPv4Proto.setText(0,'????????????(proto)???TCP(6)')
                    tcp = QtWidgets.QTreeWidgetItem(self.treeWidget)
                    tcp.setText(0,'TCP????????????(sport)???%s???????????????(dport)???%s???Seq???%s???Ack???%s' % (packet[TCP].sport,packet[TCP].dport,packet[TCP].seq,packet[TCP].ack))
                    tcpSport = QtWidgets.QTreeWidgetItem(tcp)
                    tcpSport.setText(0,'?????????(sport)???%s' % packet[TCP].sport)
                    tcpDport = QtWidgets.QTreeWidgetItem(tcp)
                    tcpDport.setText(0,'????????????(dport)???%s' % packet[TCP].dport)
                    tcpSeq = QtWidgets.QTreeWidgetItem(tcp)
                    tcpSeq.setText(0,'??????(Seq)???%s' % packet[TCP].seq)
                    tcpAck = QtWidgets.QTreeWidgetItem(tcp)
                    tcpAck.setText(0,'?????????(Ack)???%s' % packet[TCP].ack)
                    tcpDataofs = QtWidgets.QTreeWidgetItem(tcp)
                    tcpDataofs.setText(0,'????????????(dataofs)???%s' % packet[TCP].dataofs)
                    tcpReserved = QtWidgets.QTreeWidgetItem(tcp)
                    tcpReserved.setText(0,'??????(reserved)???%s' % packet[TCP].reserved)
                    tcpFlags = QtWidgets.QTreeWidgetItem(tcp)
                    tcpFlags.setText(0,'??????(flags)???%s' % packet[TCP].flags)
                    '''
                    ACK ???1????????????????????????????????????0?????????????????????????????????????????????????????????????????????
                    RST ???1?????????????????????????????????RST??????????????????????????????????????????
                    SYN ???1??????????????????????????????
                    FIN ???1??????????????????????????????????????????????????????????????????????????????????????????????????????
                    URG ???????????????????????????TCP??????????????????????????????????????????????????????????????????
                    PSH ???1?????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????
                  '''
                    tcpFlagsACK = QtWidgets.QTreeWidgetItem(tcpFlags)
                    tcpFlagsACK.setText(0,'??????(ACK)???%s' % packet[TCP].flags.A)
                    tcpFlagsRST = QtWidgets.QTreeWidgetItem(tcpFlags)
                    tcpFlagsRST.setText(0,'????????????(RST)???%s' % packet[TCP].flags.R)
                    tcpFlagsSYN = QtWidgets.QTreeWidgetItem(tcpFlags)
                    tcpFlagsSYN.setText(0,'????????????(SYN)???%s' % packet[TCP].flags.S)
                    tcpFlagsFIN = QtWidgets.QTreeWidgetItem(tcpFlags)
                    tcpFlagsFIN.setText(0,'????????????(FIN)???%s' % packet[TCP].flags.F)
                    tcpFlagsURG = QtWidgets.QTreeWidgetItem(tcpFlags)
                    tcpFlagsURG.setText(0,'????????????(URG)???%s' % packet[TCP].flags.U)
                    tcpFlagsPSH = QtWidgets.QTreeWidgetItem(tcpFlags)
                    tcpFlagsPSH.setText(0,'????????????(PSH)???%s' % packet[TCP].flags.P)
                    tcpWindow = QtWidgets.QTreeWidgetItem(tcp)
                    tcpWindow.setText(0,'??????(window)???%s' % packet[TCP].window)
                    tcpChksum = QtWidgets.QTreeWidgetItem(tcp)
                    tcpChksum.setText(0,'?????????(chksum)???0x%x' % packet[TCP].chksum)
                    tcpUrgptr = QtWidgets.QTreeWidgetItem(tcp)
                    tcpUrgptr.setText(0,'????????????(urgptr)???%s' % packet[TCP].urgptr)  #?????????U R G?????????1????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????
                    tcpOptions = QtWidgets.QTreeWidgetItem(tcp)
                    tcpOptions.setText(0,'??????(options)???%s' % packet[TCP].options)
                    '''
                    ??????????????????????????????????????????????????????????????????????????????????????????????????????MSS??????????????????????????????????????????????????????????????????????????????????????????????????????????????????
                    ?????????????????????????????????????????????????????????MSS (Maximum Segment Size)?????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????1460??????????????????????????????
                  '''
                    #HTTP
                    if packet[TCP].dport == 80 or packet[TCP].sport == 80:
                        #HTTP Request
                        if packet.haslayer('HTTPRequest'):
                            http = QtWidgets.QTreeWidgetItem(self.treeWidget)
                            http.setText(0,'HTTP Request')
                            if packet.sprintf("{HTTPRequest:%HTTPRequest.Method%}") != 'None':
                                httpMethod = QtWidgets.QTreeWidgetItem(http)
                                httpMethod.setText(0,'Method???%s' % packet.sprintf("{HTTPRequest:%HTTPRequest.Method%}").strip("'"))
                            if packet.sprintf("{HTTPRequest:%HTTPRequest.Path%}") != 'None':
                                httpPath = QtWidgets.QTreeWidgetItem(http)
                                httpPath.setText(0,'Path???%s' % packet.sprintf("{HTTPRequest:%HTTPRequest.Path%}").strip("'"))
                            if packet.sprintf("{HTTPRequest:%HTTPRequest.Http-Version%}") != 'None':
                                httpHttpVersion = QtWidgets.QTreeWidgetItem(http)
                                httpHttpVersion.setText(0,'Http-Version???%s' % packet.sprintf("{HTTPRequest:%HTTPRequest.Http-Version%}").strip("'"))
                            if packet.sprintf("{HTTPRequest:%HTTPRequest.Host%}") != 'None':
                                httpHost = QtWidgets.QTreeWidgetItem(http)
                                httpHost.setText(0,'Host???%s' % packet.sprintf("{HTTPRequest:%HTTPRequest.Host%}").strip("'"))
                            if packet.sprintf("{HTTPRequest:%HTTPRequest.User-Agent%}") != 'None':
                                httpUserAgent = QtWidgets.QTreeWidgetItem(http)
                                httpUserAgent.setText(0,'User-Agent???%s' % packet.sprintf("{HTTPRequest:%HTTPRequest.User-Agent%}").strip("'"))
                            if packet.sprintf("{HTTPRequest:%HTTPRequest.Accept%}") != 'None':
                                httpAccept = QtWidgets.QTreeWidgetItem(http)
                                httpAccept.setText(0,'Accept???%s' % packet.sprintf("{HTTPRequest:%HTTPRequest.Accept%}").strip("'"))
                            if packet.sprintf("{HTTPRequest:%HTTPRequest.Accept-Language%}") != 'None':
                                httpAcceptLanguage = QtWidgets.QTreeWidgetItem(http)
                                httpAcceptLanguage.setText(0,'Accept-Language???%s' % packet.sprintf("{HTTPRequest:%HTTPRequest.Accept-Language%}").strip("'"))
                            if packet.sprintf("{HTTPRequest:%HTTPRequest.Accept-Encoding%}") != 'None':
                                httpAcceptEncoding = QtWidgets.QTreeWidgetItem(http)
                                httpAcceptEncoding.setText(0,'Accept-Encoding???%s' % packet.sprintf("{HTTPRequest:%HTTPRequest.Accept-Encoding%}").strip("'"))
                            if packet.sprintf("{HTTPRequest:%HTTPRequest.Accept-Charset%}") != 'None':
                                httpAcceptCharset = QtWidgets.QTreeWidgetItem(http)
                                httpAcceptCharset.setText(0,'Accept-Charset???%s' % packet.sprintf("{HTTPRequest:%HTTPRequest.Accept-Charset%}").strip("'"))
                            if packet.sprintf("{HTTPRequest:%HTTPRequest.Referer%}") != 'None':
                                httpReferer = QtWidgets.QTreeWidgetItem(http)
                                httpReferer.setText(0,'Referer???%s' % packet.sprintf("{HTTPRequest:%HTTPRequest.Referer%}").strip("'"))
                            if packet.sprintf("{HTTPRequest:%HTTPRequest.Authorization%}") != 'None':
                                httpAuthorization = QtWidgets.QTreeWidgetItem(http)
                                httpAuthorization.setText(0,'Authorization???%s' % packet.sprintf("{HTTPRequest:%HTTPRequest.Authorization%}").strip("'"))
                            if packet.sprintf("{HTTPRequest:%HTTPRequest.Expect%}") != 'None':
                                httpExpect = QtWidgets.QTreeWidgetItem(http)
                                httpExpect.setText(0,'Expect???%s' % packet.sprintf("{HTTPRequest:%HTTPRequest.Expect%}").strip("'"))
                            if packet.sprintf("{HTTPRequest:%HTTPRequest.From%}") != 'None':
                                httpFrom = QtWidgets.QTreeWidgetItem(http)
                                httpFrom.setText(0,'From???%s' % packet.sprintf("{HTTPRequest:%HTTPRequest.From%}").strip("'"))
                            if packet.sprintf("{HTTPRequest:%HTTPRequest.If-Match%}") != 'None':
                                httpIfMatch = QtWidgets.QTreeWidgetItem(http)
                                httpIfMatch.setText(0,'If-Match???%s' % packet.sprintf("{HTTPRequest:%HTTPRequest.If-Match%}").strip("'"))
                            if packet.sprintf("{HTTPRequest:%HTTPRequest.If-Modified-Since%}") != 'None':
                                httpIfModifiedSince = QtWidgets.QTreeWidgetItem(http)
                                httpIfModifiedSince.setText(0,'If-Modified-Since???%s' % packet.sprintf("{HTTPRequest:%HTTPRequest.If-Modified-Since%}").strip("'"))
                            if packet.sprintf("{HTTPRequest:%HTTPRequest.If-None-Match%}") != 'None':
                                httpIfNoneMatch = QtWidgets.QTreeWidgetItem(http)
                                httpIfNoneMatch.setText(0,'If-None-Match???%s' % packet.sprintf("{HTTPRequest:%HTTPRequest.If-None-Match%}").strip("'"))
                            if packet.sprintf("{HTTPRequest:%HTTPRequest.If-Range%}") != 'None':
                                httpIfRange = QtWidgets.QTreeWidgetItem(http)
                                httpIfRange.setText(0,'If-Range???%s' % packet.sprintf("{HTTPRequest:%HTTPRequest.If-Range%}").strip("'"))
                            if packet.sprintf("{HTTPRequest:%HTTPRequest.If-Unmodified-Since%}") != 'None':
                                httpIfUnmodifiedSince = QtWidgets.QTreeWidgetItem(http)
                                httpIfUnmodifiedSince.setText(0,'If-Unmodified-Since???%s' % packet.sprintf("{HTTPRequest:%HTTPRequest.If-Unmodified-Since%}").strip("'"))
                            if packet.sprintf("{HTTPRequest:%HTTPRequest.Max-Forwards%}") != 'None':
                                httpMaxForwards = QtWidgets.QTreeWidgetItem(http)
                                httpMaxForwards.setText(0,'Max-Forwards???%s' % packet.sprintf("{HTTPRequest:%HTTPRequest.Max-Forwards%}").strip("'"))
                            if packet.sprintf("{HTTPRequest:%HTTPRequest.Proxy-Authorization%}") != 'None':
                                httpProxyAuthorization = QtWidgets.QTreeWidgetItem(http)
                                httpProxyAuthorization.setText(0,'Proxy-Authorization???%s' % packet.sprintf("{HTTPRequest:%HTTPRequest.Proxy-Authorization%}").strip("'"))
                            if packet.sprintf("{HTTPRequest:%HTTPRequest.Range%}") != 'None':
                                httpRange = QtWidgets.QTreeWidgetItem(http)
                                httpRange.setText(0,'Range???%s' % packet.sprintf("{HTTPRequest:%HTTPRequest.Range%}").strip("'"))
                            if packet.sprintf("{HTTPRequest:%HTTPRequest.TE%}") != 'None':
                                httpTE = QtWidgets.QTreeWidgetItem(http)
                                httpTE.setText(0,'TE???%s' % packet.sprintf("{HTTPRequest:%HTTPRequest.TE%}").strip("'"))
                            if packet.sprintf("{HTTPRequest:%HTTPRequest.Cache-Control%}") != 'None':
                                httpCacheControl = QtWidgets.QTreeWidgetItem(http)
                                httpCacheControl.setText(0,'Cache-Control???%s' % packet.sprintf("{HTTPRequest:%HTTPRequest.Cache-Control%}").strip("'"))
                            if packet.sprintf("{HTTPRequest:%HTTPRequest.Connection%}") != 'None':
                                httpConnection = QtWidgets.QTreeWidgetItem(http)
                                httpConnection.setText(0,'Connection???%s' % packet.sprintf("{HTTPRequest:%HTTPRequest.Connection%}").strip("'"))
                            if packet.sprintf("{HTTPRequest:%HTTPRequest.Date%}") != 'None':
                                httpDate = QtWidgets.QTreeWidgetItem(http)
                                httpDate.setText(0,'Date???%s' % packet.sprintf("{HTTPRequest:%HTTPRequest.Date%}").strip("'"))
                            if packet.sprintf("{HTTPRequest:%HTTPRequest.Pragma%}") != 'None':
                                httpPragma = QtWidgets.QTreeWidgetItem(http)
                                httpPragma.setText(0,'Pragma???%s' % packet.sprintf("{HTTPRequest:%HTTPRequest.Pragma%}").strip("'"))
                            if packet.sprintf("{HTTPRequest:%HTTPRequest.Trailer%}") != 'None':
                                httpTrailer = QtWidgets.QTreeWidgetItem(http)
                                httpTrailer.setText(0,'Trailer???%s' % packet.sprintf("{HTTPRequest:%HTTPRequest.Trailer%}").strip("'"))
                            if packet.sprintf("{HTTPRequest:%HTTPRequest.Transfer-Encoding%}") != 'None':
                                httpTransferEncoding = QtWidgets.QTreeWidgetItem(http)
                                httpTransferEncoding.setText(0,'Transfer-Encoding???%s' % packet.sprintf("{HTTPRequest:%HTTPRequest.Transfer-Encoding%}").strip("'"))
                            if packet.sprintf("{HTTPRequest:%HTTPRequest.Upgrade%}") != 'None':
                                httpUpgrade = QtWidgets.QTreeWidgetItem(http)
                                httpUpgrade.setText(0,'Upgrade???%s' % packet.sprintf("{HTTPRequest:%HTTPRequest.Upgrade%}").strip("'"))
                            if packet.sprintf("{HTTPRequest:%HTTPRequest.Via%}") != 'None':
                                httpVia = QtWidgets.QTreeWidgetItem(http)
                                httpVia.setText(0,'Via???%s' % packet.sprintf("{HTTPRequest:%HTTPRequest.Via%}").strip("'"))
                            if packet.sprintf("{HTTPRequest:%HTTPRequest.Warning%}") != 'None':
                                httpWarning = QtWidgets.QTreeWidgetItem(http)
                                httpWarning.setText(0,'Warning???%s' % packet.sprintf("{HTTPRequest:%HTTPRequest.Warning%}").strip("'"))
                            if packet.sprintf("{HTTPRequest:%HTTPRequest.Keep-Alive%}") != 'None':
                                httpKeepAlive = QtWidgets.QTreeWidgetItem(http)
                                httpKeepAlive.setText(0,'Keep-Alive???%s' % packet.sprintf("{HTTPRequest:%HTTPRequest.Keep-Alive%}").strip("'"))
                            if packet.sprintf("{HTTPRequest:%HTTPRequest.Allow%}") != 'None':
                                httpAllow = QtWidgets.QTreeWidgetItem(http)
                                httpAllow.setText(0,'Allow???%s' % packet.sprintf("{HTTPRequest:%HTTPRequest.Allow%}").strip("'"))
                            if packet.sprintf("{HTTPRequest:%HTTPRequest.Content-Encoding%}") != 'None':
                                httpContentEncoding = QtWidgets.QTreeWidgetItem(http)
                                httpContentEncoding.setText(0,'Content-Encoding???%s' % packet.sprintf("{HTTPRequest:%HTTPRequest.Content-Encoding%}").strip("'"))
                            if packet.sprintf("{HTTPRequest:%HTTPRequest.Content-Language%}") != 'None':
                                httpContentLanguage = QtWidgets.QTreeWidgetItem(http)
                                httpContentLanguage.setText(0,'Content-Language???%s' % packet.sprintf("{HTTPRequest:%HTTPRequest.Content-Language%}").strip("'"))
                            if packet.sprintf("{HTTPRequest:%HTTPRequest.Content-Length%}") != 'None':
                                httpContentLength = QtWidgets.QTreeWidgetItem(http)
                                httpContentLength.setText(0,'Content-Length???%s' % packet.sprintf("{HTTPRequest:%HTTPRequest.Content-Length%}").strip("'"))
                            if packet.sprintf("{HTTPRequest:%HTTPRequest.Content-Location%}") != 'None':
                                httpContentLocation = QtWidgets.QTreeWidgetItem(http)
                                httpContentLocation.setText(0,'Content-Location???%s' % packet.sprintf("{HTTPRequest:%HTTPRequest.Content-Location%}").strip("'"))
                            if packet.sprintf("{HTTPRequest:%HTTPRequest.Content-MD5%}") != 'None':
                                httpContentMD5 = QtWidgets.QTreeWidgetItem(http)
                                httpContentMD5.setText(0,'Content-MD5???%s' % packet.sprintf("{HTTPRequest:%HTTPRequest.Content-MD5%}").strip("'"))
                            if packet.sprintf("{HTTPRequest:%HTTPRequest.Content-Range%}") != 'None':
                                httpContentRange = QtWidgets.QTreeWidgetItem(http)
                                httpContentRange.setText(0,'Content-Range???%s' % packet.sprintf("{HTTPRequest:%HTTPRequest.Content-Range%}").strip("'"))
                            if packet.sprintf("{HTTPRequest:%HTTPRequest.Content-Type%}") != 'None':
                                httpContentType = QtWidgets.QTreeWidgetItem(http)
                                httpContentType.setText(0,'Content-Type???%s' % packet.sprintf("{HTTPRequest:%HTTPRequest.Content-Type%}").strip("'"))
                            if packet.sprintf("{HTTPRequest:%HTTPRequest.Expires%}") != 'None':
                                httpExpires = QtWidgets.QTreeWidgetItem(http)
                                httpExpires.setText(0,'Expires???%s' % packet.sprintf("{HTTPRequest:%HTTPRequest.Expires%}").strip("'"))
                            if packet.sprintf("{HTTPRequest:%HTTPRequest.Last-Modified%}") != 'None':
                                httpLastModified = QtWidgets.QTreeWidgetItem(http)
                                httpLastModified.setText(0,'Last-Modified???%s' % packet.sprintf("{HTTPRequest:%HTTPRequest.Last-Modified%}").strip("'"))
                            if packet.sprintf("{HTTPRequest:%HTTPRequest.Cookie%}") != 'None':
                                httpCookie = QtWidgets.QTreeWidgetItem(http)
                                httpCookie.setText(0,'Cookie???%s' % packet.sprintf("{HTTPRequest:%HTTPRequest.Cookie%}").strip("'"))
                        #HTTP Response
                        if packet.haslayer('HTTPResponse'):
                            http = QtWidgets.QTreeWidgetItem(self.treeWidget)
                            http.setText(0,'HTTP Response')
                            if packet.sprintf("{HTTPResponse:%HTTPResponse.Status-Line%}") != 'None':
                                httpStatusLine = QtWidgets.QTreeWidgetItem(http)
                                httpStatusLine.setText(0,'Status-Line???%s' % packet.sprintf("{HTTPResponse:%HTTPResponse.Status-Line%}").strip("'"))
                            if packet.sprintf("{HTTPResponse:%HTTPResponse.Accept-Ranges%}") != 'None':
                                httpAcceptRanges = QtWidgets.QTreeWidgetItem(http)
                                httpAcceptRanges.setText(0,'Accept-Ranges???%s' % packet.sprintf("{HTTPResponse:%HTTPResponse.Accept-Ranges%}").strip("'"))
                            if packet.sprintf("{HTTPResponse:%HTTPResponse.Age%}") != 'None':
                                httpAge = QtWidgets.QTreeWidgetItem(http)
                                httpAge.setText(0,'Age???%s' % packet.sprintf("{HTTPResponse:%HTTPResponse.Age%}").strip("'"))
                            if packet.sprintf("{HTTPResponse:%HTTPResponse.E-Tag%}") != 'None':
                                httpETag = QtWidgets.QTreeWidgetItem(http)
                                httpETag.setText(0,'E-Tag???%s' % packet.sprintf("{HTTPResponse:%HTTPResponse.E-Tag%}").strip("'"))
                            if packet.sprintf("{HTTPResponse:%HTTPResponse.Location%}") != 'None':
                                httpLocation = QtWidgets.QTreeWidgetItem(http)
                                httpLocation.setText(0,'Location???%s' % packet.sprintf("{HTTPResponse:%HTTPResponse.Location%}").strip("'"))
                            if packet.sprintf("{HTTPResponse:%HTTPResponse.Proxy-Authenticate%}") != 'None':
                                httpProxyAuthenticate = QtWidgets.QTreeWidgetItem(http)
                                httpProxyAuthenticate.setText(0,'Proxy-Authenticate???%s' % packet.sprintf("{HTTPResponse:%HTTPResponse.Proxy-Authenticate%}").strip("'"))
                            if packet.sprintf("{HTTPResponse:%HTTPResponse.Retry-After%}") != 'None':
                                httpRetryAfter = QtWidgets.QTreeWidgetItem(http)
                                httpRetryAfter.setText(0,'Retry-After???%s' % packet.sprintf("{HTTPResponse:%HTTPResponse.Retry-After%}").strip("'"))
                            if packet.sprintf("{HTTPResponse:%HTTPResponse.Server%}") != 'None':
                                httpServer = QtWidgets.QTreeWidgetItem(http)
                                httpServer.setText(0,'Server???%s' % packet.sprintf("{HTTPResponse:%HTTPResponse.Server%}").strip("'"))
                            if packet.sprintf("{HTTPResponse:%HTTPResponse.Vary%}") != 'None':
                                httpVary = QtWidgets.QTreeWidgetItem(http)
                                httpVary.setText(0,'Vary???%s' % packet.sprintf("{HTTPResponse:%HTTPResponse.Vary%}").strip("'"))
                            if packet.sprintf("{HTTPResponse:%HTTPResponse.WWW-Authenticate%}") != 'None':
                                httpWWWAuthenticate = QtWidgets.QTreeWidgetItem(http)
                                httpWWWAuthenticate.setText(0,'WWW-Authenticate???%s' % packet.sprintf("{HTTPResponse:%HTTPResponse.WWW-Authenticate%}").strip("'"))
                            if packet.sprintf("{HTTPResponse:%HTTPResponse.Cache-Control%}") != 'None':
                                httpCacheControl = QtWidgets.QTreeWidgetItem(http)
                                httpCacheControl.setText(0,'Cache-Control???%s' % packet.sprintf("{HTTPResponse:%HTTPResponse.Cache-Control%}").strip("'"))
                            if packet.sprintf("{HTTPResponse:%HTTPResponse.Connection%}") != 'None':
                                httpConnection = QtWidgets.QTreeWidgetItem(http)
                                httpConnection.setText(0,'Connection???%s' % packet.sprintf("{HTTPResponse:%HTTPResponse.Connection%}").strip("'"))
                            if packet.sprintf("{HTTPResponse:%HTTPResponse.Date%}") != 'None':
                                httpDate = QtWidgets.QTreeWidgetItem(http)
                                httpDate.setText(0,'Date???%s' % packet.sprintf("{HTTPResponse:%HTTPResponse.Date%}").strip("'"))
                            if packet.sprintf("{HTTPResponse:%HTTPResponse.Pragma%}") != 'None':
                                httpPragma = QtWidgets.QTreeWidgetItem(http)
                                httpPragma.setText(0,'Pragma???%s' % packet.sprintf("{HTTPResponse:%HTTPResponse.Pragma%}").strip("'"))
                            if packet.sprintf("{HTTPResponse:%HTTPResponse.Trailer%}") != 'None':
                                httpTrailer = QtWidgets.QTreeWidgetItem(http)
                                httpTrailer.setText(0,'Trailer???%s' % packet.sprintf("{HTTPResponse:%HTTPResponse.Trailer%}").strip("'"))
                            if packet.sprintf("{HTTPResponse:%HTTPResponse.Transfer-Encoding%}") != 'None':
                                httpTransferEncoding = QtWidgets.QTreeWidgetItem(http)
                                httpTransferEncoding.setText(0,'Transfer-Encoding???%s' % packet.sprintf("{HTTPResponse:%HTTPResponse.Transfer-Encoding%}").strip("'"))
                            if packet.sprintf("{HTTPResponse:%HTTPResponse.Upgrade%}") != 'None':
                                httpUpgrade = QtWidgets.QTreeWidgetItem(http)
                                httpUpgrade.setText(0,'Upgrade???%s' % packet.sprintf("{HTTPResponse:%HTTPResponse.Upgrade%}").strip("'"))
                            if packet.sprintf("{HTTPResponse:%HTTPResponse.Via%}") != 'None':
                                httpVia = QtWidgets.QTreeWidgetItem(http)
                                httpVia.setText(0,'Via???%s' % packet.sprintf("{HTTPResponse:%HTTPResponse.Via%}").strip("'"))
                            if packet.sprintf("{HTTPResponse:%HTTPResponse.Warning%}") != 'None':
                                httpWarning = QtWidgets.QTreeWidgetItem(http)
                                httpWarning.setText(0,'Warning???%s' % packet.sprintf("{HTTPResponse:%HTTPResponse.Warning%}").strip("'"))
                            if packet.sprintf("{HTTPResponse:%HTTPResponse.Keep-Alive%}") != 'None':
                                httpKeepAlive = QtWidgets.QTreeWidgetItem(http)
                                httpKeepAlive.setText(0,'Keep-Alive???%s' % packet.sprintf("{HTTPResponse:%HTTPResponse.Keep-Alive%}").strip("'"))
                            if packet.sprintf("{HTTPResponse:%HTTPResponse.Allow%}") != 'None':
                                httpAllow = QtWidgets.QTreeWidgetItem(http)
                                httpAllow.setText(0,'Allow???%s' % packet.sprintf("{HTTPResponse:%HTTPResponse.Allow%}").strip("'"))
                            if packet.sprintf("{HTTPResponse:%HTTPResponse.Content-Encoding%}") != 'None':
                                httpContentEncoding = QtWidgets.QTreeWidgetItem(http)
                                httpContentEncoding.setText(0,'Content-Encoding???%s' % packet.sprintf("{HTTPResponse:%HTTPResponse.Content-Encoding%}").strip("'"))
                            if packet.sprintf("{HTTPResponse:%HTTPResponse.Content-Language%}") != 'None':
                                httpContentLanguage = QtWidgets.QTreeWidgetItem(http)
                                httpContentLanguage.setText(0,'Content-Language???%s' % packet.sprintf("{HTTPResponse:%HTTPResponse.Content-Language%}").strip("'"))
                            if packet.sprintf("{HTTPResponse:%HTTPResponse.Content-Length%}") != 'None':
                                httpContentLength = QtWidgets.QTreeWidgetItem(http)
                                httpContentLength.setText(0,'Content-Length???%s' % packet.sprintf("{HTTPResponse:%HTTPResponse.Content-Length%}").strip("'"))
                            if packet.sprintf("{HTTPResponse:%HTTPResponse.Content-Location%}") != 'None':
                                httpContentLocation = QtWidgets.QTreeWidgetItem(http)
                                httpContentLocation.setText(0,'Content-Location???%s' % packet.sprintf("{HTTPResponse:%HTTPResponse.Content-Location%}").strip("'"))
                            if packet.sprintf("{HTTPResponse:%HTTPResponse.Content-MD5%}") != 'None':
                                httpContentMD5 = QtWidgets.QTreeWidgetItem(http)
                                httpContentMD5.setText(0,'Content-MD5???%s' % packet.sprintf("{HTTPResponse:%HTTPResponse.Content-MD5%}").strip("'"))
                            if packet.sprintf("{HTTPResponse:%HTTPResponse.Content-Range%}") != 'None':
                                httpContentRange = QtWidgets.QTreeWidgetItem(http)
                                httpContentRange.setText(0,'Content-Range???%s' % packet.sprintf("{HTTPResponse:%HTTPResponse.Content-Range%}").strip("'"))
                            if packet.sprintf("{HTTPResponse:%HTTPResponse.Content-Type%}") != 'None':
                                httpContentType = QtWidgets.QTreeWidgetItem(http)
                                httpContentType.setText(0,'Content-Type???%s' % packet.sprintf("{HTTPResponse:%HTTPResponse.Content-Type%}").strip("'"))
                            if packet.sprintf("{HTTPResponse:%HTTPResponse.Expires%}") != 'None':
                                httpExpires = QtWidgets.QTreeWidgetItem(http)
                                httpExpires.setText(0,'Expires???%s' % packet.sprintf("{HTTPResponse:%HTTPResponse.Expires%}").strip("'"))
                            if packet.sprintf("{HTTPResponse:%HTTPResponse.Last-Modified%}") != 'None':
                                httpLastModified = QtWidgets.QTreeWidgetItem(http)
                                httpLastModified.setText(0,'Last-Modified???%s' % packet.sprintf("{HTTPResponse:%HTTPResponse.Last-Modified%}").strip("'"))


            #UDP
            elif packet[IP].proto == 17:
                IPv4Proto = QtWidgets.QTreeWidgetItem(IPv4)
                IPv4Proto.setText(0,'????????????(proto)???UDP(17)')
                udp = QtWidgets.QTreeWidgetItem(self.treeWidget)
                udp.setText(0,'UDP????????????(sport)???%s???????????????(dport)???%s'% (packet[UDP].sport , packet[UDP].dport))
                udpSport = QtWidgets.QTreeWidgetItem(udp)
                udpSport.setText(0,'?????????(sport)???%s' % packet[UDP].sport)
                udpDport = QtWidgets.QTreeWidgetItem(udp)
                udpDport.setText(0,'????????????(dport)???%s' % packet[UDP].dport)
                udpLen = QtWidgets.QTreeWidgetItem(udp)
                udpLen.setText(0,'??????(len)???%s' % packet[UDP].len)
                udpChksum = QtWidgets.QTreeWidgetItem(udp)
                udpChksum.setText(0,'?????????(chksum)???0x%x' % packet[UDP].chksum)
                #DNS
                if packet.haslayer('DNS'):
                    pass
                    # nds = QtWidgets.QTreeWidgetItem(self.treeWidget)
                    # nds.setText(0,'DNS')
            #ICMP
            elif packet[IP].proto == 1:
                IPv4Proto = QtWidgets.QTreeWidgetItem(IPv4)
                IPv4Proto.setText(0,'????????????(proto)???ICMP(1)')

                '''
                8????????????8??????????????????????????????ICMP??????????????????
                    ??????8?????????0?????????????????????(ping??????)???
                    ??????0?????????0?????????????????????(ping??????)
                    ??????11?????????0?????????
               '''
                icmp = QtWidgets.QTreeWidgetItem(self.treeWidget)
                icmp.setText(0,'ICMP')
                icmpType = QtWidgets.QTreeWidgetItem(icmp)
                if packet[ICMP].type == 8:
                    icmpType.setText(0,'??????(type)???%s (Echo (ping) request)' % packet[ICMP].type)
                elif packet[ICMP].type == 0:
                    icmpType.setText(0,'??????(type)???%s (Echo (ping) reply)' % packet[ICMP].type)
                else:
                    icmpType.setText(0,'??????(type)???%s' % packet[ICMP].type)  #?????????????????????ICMP????????????????????????????????????14????????????????????????ICMP???????????????????????????????????????????????????1~127?????????????????????2????????????128????????????????????????
                icmpCode = QtWidgets.QTreeWidgetItem(icmp)
                icmpCode.setText(0,'??????(code)???%s' % packet[ICMP].code)  #???????????????????????????ICMP?????????????????????????????????????????????????????????ICMP????????????????????????
                icmpChksum = QtWidgets.QTreeWidgetItem(icmp)
                icmpChksum.setText(0,'?????????(chksum)???0x%x' % packet[ICMP].chksum)
                icmpId = QtWidgets.QTreeWidgetItem(icmp)
                icmpId.setText(0,'??????(id)???%s' % packet[ICMP].id)  #??????????????????????????????ICMP?????????????????????????????????????????????ICMP??????????????????????????????ICMP???????????????ICMP??????????????????????????????0???
                icmpSeq = QtWidgets.QTreeWidgetItem(icmp)
                icmpSeq.setText(0,'seq???%s' % packet[ICMP].seq)
                icmpTs_ori = QtWidgets.QTreeWidgetItem(icmp)
                icmpTs_ori.setText(0,'ts_ori???%s' % packet[ICMP].ts_ori)
                icmpTs_rx = QtWidgets.QTreeWidgetItem(icmp)
                icmpTs_rx.setText(0,'ts_rx???%s' % packet[ICMP].ts_rx)
                icmpTs_tx = QtWidgets.QTreeWidgetItem(icmp)
                icmpTs_tx.setText(0,'ts_tx???%s' % packet[ICMP].ts_tx)
                icmpGw = QtWidgets.QTreeWidgetItem(icmp)
                icmpGw.setText(0,'gw???%s' % packet[ICMP].gw)
                icmpPtr = QtWidgets.QTreeWidgetItem(icmp)
                icmpPtr.setText(0,'ptr???%s' % packet[ICMP].ptr)
                icmpReserved = QtWidgets.QTreeWidgetItem(icmp)
                icmpReserved.setText(0,'reserved???%s' % packet[ICMP].reserved)
                icmpLength = QtWidgets.QTreeWidgetItem(icmp)
                icmpLength.setText(0,'length???%s' % packet[ICMP].length)
                icmpAddr_mask = QtWidgets.QTreeWidgetItem(icmp)
                icmpAddr_mask.setText(0,'addr_mask???%s' % packet[ICMP].addr_mask)
                icmpnexthopmtu = QtWidgets.QTreeWidgetItem(icmp)
                icmpnexthopmtu.setText(0,'nexthopmtu???%s' % packet[ICMP].nexthopmtu)
            #IGMP
            elif packet[IP].proto == 2:
                IPv4Proto = QtWidgets.QTreeWidgetItem(IPv4)
                IPv4Proto.setText(0,'????????????(proto)???IGMP(2)')

                igmp = QtWidgets.QTreeWidgetItem(self.treeWidget)
                igmp.setText(0,'IGMP')
                igmpCopy_flag = QtWidgets.QTreeWidgetItem(igmp)
                igmpCopy_flag.setText(0,'copy_flag???%s' % packet[IPOption_Router_Alert].copy_flag)
                igmpOptclass = QtWidgets.QTreeWidgetItem(igmp)
                igmpOptclass.setText(0,'optclass???%s' % packet[IPOption_Router_Alert].optclass)
                igmpOption = QtWidgets.QTreeWidgetItem(igmp)
                igmpOption.setText(0,'option???%s' % packet[IPOption_Router_Alert].option)
                igmpLength = QtWidgets.QTreeWidgetItem(igmp)
                igmpLength.setText(0,'length???%s' % packet[IPOption_Router_Alert].length)
                igmpAlert = QtWidgets.QTreeWidgetItem(igmp)
                igmpAlert.setText(0,'alert???%s' % packet[IPOption_Router_Alert].alert)
            else:
                IPv4Proto = QtWidgets.QTreeWidgetItem(IPv4)
                IPv4Proto.setText(0,'????????????(proto)???%s'% packet[IP].proto)


            IPv4Chksum = QtWidgets.QTreeWidgetItem(IPv4)
            IPv4Chksum.setText(0,'?????????(chksum)???0x%x' % packet[IP].chksum)
            IPv4Src = QtWidgets.QTreeWidgetItem(IPv4)
            IPv4Src.setText(0,'???IP??????(src)???%s' % packet[IP].src)
            IPv4Dst = QtWidgets.QTreeWidgetItem(IPv4)
            IPv4Dst.setText(0,'??????IP??????(dst)???%s' % packet[IP].dst)
            IPv4Options = QtWidgets.QTreeWidgetItem(IPv4)
            IPv4Options.setText(0,'????????????(options)???%s' %packet[IP].options)

        #ARP
        elif type == 0x806 :
            EthernetType = QtWidgets.QTreeWidgetItem(Ethernet)
            EthernetType.setText(0,'????????????(type)???ARP(0x806)')

            arp = QtWidgets.QTreeWidgetItem(self.treeWidget)
            arp.setText(0,'ARP')
            arpHwtype = QtWidgets.QTreeWidgetItem(arp)
            arpHwtype.setText(0,'????????????(hwtype)???0x%x' % packet[ARP].hwtype) #1?????????????????????
            arpPtype = QtWidgets.QTreeWidgetItem(arp)
            arpPtype.setText(0,'????????????(ptype)???0x%x' % packet[ARP].ptype) #???????????????????????????,?????????0x0800,?????????????????????IP??????
            arpHwlen = QtWidgets.QTreeWidgetItem(arp)
            arpHwlen.setText(0,'??????????????????(hwlen)???%s' % packet[ARP].hwlen)
            arpPlen = QtWidgets.QTreeWidgetItem(arp)
            arpPlen.setText(0,'????????????(plen)???%s' % packet[ARP].plen)
            arpOp = QtWidgets.QTreeWidgetItem(arp)
            if packet[ARP].op == 1:  #request
                arpOp.setText(0,'????????????(op)???request (%s)' % packet[ARP].op)
            elif packet[ARP].op == 2:
                arpOp.setText(0,'????????????(op)???reply (%s)' % packet[ARP].op)
            else:
                arpOp.setText(0,'????????????(op)???%s' % packet[ARP].op) #???????????????2?????????,1??????ARP??????,2??????ARP??????,3??????RARP??????,4??????RARP??????
            arpHwsrc = QtWidgets.QTreeWidgetItem(arp)
            arpHwsrc.setText(0,'???MAC??????(hwsrc)???%s' % packet[ARP].hwsrc)
            arpPsrc = QtWidgets.QTreeWidgetItem(arp)
            arpPsrc.setText(0,'???IP??????(psrc)???%s' % packet[ARP].psrc)
            arpHwdst = QtWidgets.QTreeWidgetItem(arp)
            arpHwdst.setText(0,'??????MAC??????(hwdst)???%s' % packet[ARP].hwdst)
            arpPdst = QtWidgets.QTreeWidgetItem(arp)
            arpPdst.setText(0,'??????IP??????(pdst)???%s' % packet[ARP].pdst)

        self.textBrowserRaw.clear()
        if packet.haslayer('Raw'):
            # raw = QtWidgets.QTreeWidgetItem(self.treeWidget)
            # raw.setText(0,'Raw???%s' % packet[Raw].load.decode('utf-8','ignore'))
            self.textBrowserRaw.append('Raw???%s' % packet[Raw].load.decode('utf-8','ignore'))

        if packet.haslayer('Padding'):
            # padding = QtWidgets.QTreeWidgetItem(self.treeWidget)
            # padding.setText(0,'Padding???%s' % packet[Padding].load.decode('utf-8','ignore'))
            self.textBrowserRaw.append('Padding???%s' % packet[Padding].load.decode('utf-8','ignore'))

        self.textBrowserDump.clear()
        f = open('hexdump.tmp','w')
        old = sys.stdout #??????????????????????????????????????????
        sys.stdout = f   #????????????????????????
        hexdump(packet)
        sys.stdout = old
        f.close()
        f = open('hexdump.tmp','r')
        content = f.read()
        self.textBrowserDump.append(content)
        f.close()
        os.remove('hexdump.tmp')



    #????????????
    def LookupIface(self):
        netcards = os.listdir('/sys/class/net/')
        eth_local=[]
        # a = repr(conf.route).split('\n')[1:]
        # for x in a:
        #     b = re.search(r'[a-zA-Z](.*)[a-zA-Z]',x)
        #     eth_local.append(b.group())
        # #??????
        # c = []
        # c.append(eth_local[0])
        # for i in range(0,len(eth_local),1):
        #     m = 0
        #     for j in range(0,len(c),1):
        #         if c[j] == eth_local[i]:
        #             m += 1
        #     if m==0:
        #         c.append(eth_local[i])
        # #?????????comboBoxIface???
        self.comboBoxIface.addItems(netcards)
    #????????????
    def PreFilter(self):
        list = ["?????????IP??????","????????????IP??????", "???????????????","??????????????????","??????????????????","???????????????"]

         #????????????????????? ??????????????? ???QLineEdit.Normal????????????????????? QLineEdit. Password?????????????????????????????? QLineEdit. NoEcho???
        #stringNum,ok3 = QInputDialog.getText(self, "??????","??????:",QLineEdit.Normal, "?????????")
         #1???????????????????????????True/False  ???????????????????????????
        item, ok = QInputDialog.getItem(self, "??????","????????????", list, 1, False)
        type=0
        if ok:
            if item=="?????????IP??????":
                 filter,ok_1 = QInputDialog.getText(self, "??????","??????????????????IP??????:",QLineEdit.Normal, "*.*.*.*")
                 rule = "src host "+filter
            elif item =="????????????IP??????"  :
                 filter,ok_2 = QInputDialog.getText(self, "??????","?????????????????????IP??????:",QLineEdit.Normal, "*.*.*.*")
                 rule= "dst host "+filter
            elif item =="???????????????":
                 filter,ok_3 = QInputDialog.getInt(self, "??????","????????????????????????:",80, 0, 65535)
                 rule="src port "+str(filter)
            elif item =="??????????????????":
                 filter,ok_4 = QInputDialog.getInt(self, "??????","???????????????????????????:",80, 0, 65535)
                 rule ="dst port "+str(filter)
            elif item =="??????????????????" :
                 filter,ok_2 = QInputDialog.getText(self, "??????","???????????????????????????:",QLineEdit.Normal, "icmp")
                 rule =filter
            elif item =="???????????????":
                 filter,ok_2 = QInputDialog.getText(self, "??????","???????????????:",QLineEdit.Normal, "host 202.120.2.1")
                 rule=filter
            rule=rule.lower()
            self.setPreFilter(rule)

    def setPreFilter(self,filter):
        self.filter = filter

    #????????????
    def PostFilter(self):
        filter,ok = QInputDialog.getText(self, "???????????????????????????","??????????????????????????????:",QLineEdit.Normal, "http")
        if ok:
            global display
            display = 0
            if filter == None:
                for row in range(self.tableWidget.rowCount()):
                    self.tableWidget.setRowHidden(row,True)
                    display += 1
            else:
                for row in range(self.tableWidget.rowCount()):
                    if(self.tableWidget.item(row, 7))!=None:
                        p = self.tableWidget.item(row,7).text()
                        packet = scapy.layers.l2.Ether(p.encode('Windows-1252'))

                        f = open('search.tmp','w')
                        old = sys.stdout #??????????????????????????????????????????
                        sys.stdout = f   #????????????????????????
                        packet.show()
                        sys.stdout = old
                        f.close()
                        f = open('search.tmp','r')
                        data = f.read()
                        f.close()
                        os.remove('search.tmp')
                        obj= re.search(filter.lower(),data.lower())
                        if  obj is None:
                            self.tableWidget.setRowHidden(row,True)
                            display += 1
                        else:
                            self.tableWidget.setRowHidden(row,False)
    #???????????????
    def statistics(self):
        global count
        global display
        if count != 0:
            percent = '{:.1f}'.format(display/count*100)
            self.statusbar.showMessage('?????????%s   ????????????%s (%s%%)' % (count,display,percent))



#????????????
class SnifferThread(QtCore.QThread):
    HandleSignal = QtCore.pyqtSignal(scapy.layers.l2.Ether)

    def __init__(self,filter,iface):
        super().__init__()
        self.filter = filter
        self.iface = iface

    def run(self):
        sniff(filter=self.filter,iface=self.iface,prn=lambda x:self.HandleSignal.emit(x))

    # def pack_callback(self,packet):
    #     packet.show()

#pdfdump??????
class pdfdumpThread(QtCore.QThread):

    pdfdumpSignal = QtCore.pyqtSignal(bool)
    def __init__(self,packet,path):
        super().__init__()
        self.packet = packet
        self.path = path

    def run(self):
        self.packet.pdfdump(self.path,layer_shift=1)
        self.pdfdumpSignal.emit(True)




if __name__ == "__main__":
    import sys
    app = QtWidgets.QApplication(sys.argv)
    MainWindow = QtWidgets.QMainWindow()
    ui = SnifferMainWindow()
    ui.setupUi(MainWindow)
    ui.setSlot()
    MainWindow.show()
    sys.exit(app.exec())
