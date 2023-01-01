from PyQt6 import QtWidgets
from PyQt6.QtWidgets import *
import sys

import UI_main

class MainWindow(UI_main.Ui_Form, QWidget):
    def __init__(self, parent=None):
        super(MainWindow, self).__init__(parent)
        self.setupUi(self)
        self.init_ui()
        self.init_slot()
        
    def init_ui(self):
        pass
    
    def init_slot(self):
        self.btn_choose_file.clicked.connect(lambda x: self.choose_file())
        self.btn_start_collect.clicked.connect(lambda x: self.start_collect())
    
    def choose_file(self):
        fdlg = QFileDialog()
        fdlg.setFileMode(QFileDialog.FileMode.AnyFile)

        if fdlg.exec():
            #接受选中文件的路径，默认为列表
            filenames = fdlg.selectedFiles()
            self.le_file_input.setText(filenames[0])
            #列表中的第一个元素即是文件路径，以只读的方式打开文件
            f=open(filenames[0],'r')

            with f:
                #接受读取的内容，并显示到多行文本框中
                data=f.read()
                self.file_data = data
    
    def start_collect(self):
        try:
            data = self.file_data.split()
        
            self.le_ammonia_concentration.setText(data[0])
            self.le_toluene_concentration.setText(data[1])
            self.le_propanol_concentration.setText(data[2])
        except Exception as e:
            QMessageBox.warning(self, "文件格式有误", "文件格式有误")
        

if __name__ == '__main__':
    app = QApplication(sys.argv)
    w = MainWindow()
    w.show()
    sys.exit(app.exec())
    