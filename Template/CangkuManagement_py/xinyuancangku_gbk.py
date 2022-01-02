import pathlib
import sqlite3
import os

# ��澯������
inventoryAlertValue = 5

# ������Ԫ��
def insertInStorage(conn, data):
    cur = conn.cursor()
    insert = 'insert into electronicComponents ' \
             'values (?,?,?,?,?,?,?,?,?)'
    cur.execute(insert, data)
    conn.commit()
    cur.close()


# ��ʼ��
def init(db_filename):
    path = pathlib.Path(db_filename)

    if (not path.exists()):
        try:
            conn = sqlite3.connect(db_filename)
        except sqlite3.Error as e:
            print(e)
            return
        cur = conn.cursor()
        creatElectronicComponentsTable = 'create table electronicComponents(' \
                                         'no integer,' \
                                         'name text,' \
                                         'type text,' \
                                         'resistance integer,' \
                                         'nominalVoltage integer,' \
                                         'nominalCurrent integer,' \
                                         'price integer,' \
                                         'quantity integer,' \
                                         'info text,' \
                                         'primary key(no))'

        createRecordTable = 'create table record(' \
                            'rno integer,' \
                            'cno integer, ' \
                            'quantity integer,' \
                            'date datetime, ' \
                            'primary key(rno autoincrement),' \
                            'foreign key(cno) references electronicComponents(no))'
        creatIndex = 'create index time on record(date)'
        cur.execute(creatElectronicComponentsTable)
        cur.execute(createRecordTable)
        cur.execute(creatIndex)
        # loadData(conn)
        cur.close()
    else:
        conn = sqlite3.connect(db_filename)
    return conn


# ���¿��
def updateStorage(conn, data):
    cur = conn.cursor()
    update = 'update electronicComponents set quantity = quantity + ?  where no = ?'
    cur.execute(update, data)
    conn.commit()
    cur.close()


# д�����ۼ�¼
def insertRecord(conn, data):
    cur = conn.cursor()
    insert = 'insert into record(cno,quantity,date) ' \
             'values (?,?,datetime("now"))'
    cur.execute(insert, data)
    conn.commit()
    cur.close()


# ������Ƿ����
def checkInventory(conn, data):
    cur = conn.cursor()
    select = 'select  quantity ' \
             'from electronicComponents ' \
             'where no = ? '
    cur.execute(select, data)
    res = cur.fetchall()
    conn.commit()
    cur.close()
    if (res[0][0] <= inventoryAlertValue):
        return False
    else:
        return True


# ���¿��
def update(conn, data):
    updateStorage(conn, (data[1], data[0]))
    if (data[1] < 0):
        insertRecord(conn, (data[0], -data[1]))
    res = checkInventory(conn, (data[0],))
    return res


# �������Ͳ�ѯ����
def getByType(conn, data):
    cur = conn.cursor()
    select = 'select * ' \
             'from electronicComponents ' \
             'where type = ?'
    cur.execute(select, data)
    res = cur.fetchall()
    cur.close()
    return res


# ���ݱ�Ų�ѯ��Ϣ
def getByNo(conn, data):
    cur = conn.cursor()
    select = 'select * ' \
             'from electronicComponents ' \
             'where no = ? '
    cur.execute(select, data)
    res = cur.fetchall()
    cur.close()
    return res


# ��ȡ����ܼ�ֵ
def getInventoryValue(conn):
    cur = conn.cursor()
    select = 'select sum(quantity*price) ' \
             'from electronicComponents '
    cur.execute(select)
    res = cur.fetchall()
    cur.close()
    return res

def login():
    username = input("���������Ա�˺ţ�")
    passwd = input("���������Ա���룺")

    if username != "root" and passwd != "123":
        print("�˻����������")
        exit(-1)


login()
conn = init('xinyuancangku.db')
while (True):
    print('-' * 10 + '��Ժ����ϵͳ' + '-' * 10)
    print('1.���')
    print('2.����')
    print('3.������豸')
    print('4.�������Ͳ鿴����')
    print('5.���ձ�Ų鿴��Ϣ')
    print('6.�ֿ��豸�ܼ�ֵ')
    print('0.�˳�')
    print('������ѡ��Ĺ��ܱ�ţ�')
    idex = input()
    if idex == '1':
        os.system('cls')
        print('�����������豸��ź�������ʹ�ÿո������')
        data = input().split()
        data[0] = int(data[0])
        data[1] = int(data[1])
        data = tuple(data)
        update(conn, data)
    elif idex == '2':
        os.system('cls')
        print('�����������豸����ź�������ʹ�ÿո������')
        data = input().split()
        data[0] = int(data[0])
        data[1] = -int(data[1])
        data = tuple(data)
        res = update(conn, data)
        if res == False:
            print('��治��')
            print('���س�����������')
            input()
    elif idex == '3':
        os.system('cls')
        print('�����������豸���(����)�����֣����ͣ�����(����)�����ѹ(����)�������(����)���۸�(����)������(����)��˵����ʹ�ÿո������')
        data = input().split()
        for i in range(4, 8):
            data[i] = int(data[i])
        data = tuple(data)
        insertInStorage(conn, data)
    elif idex == '4':
        os.system('cls')
        print('�������豸���ͣ�')
        data = input()
        data = (data,)
        res = getByType(conn, data)
        print('���' + '\t' + '����')
        for row in res:
            print(row[1] + '\t' + row[-1])
        print('���س�����������')
        input()
        os.system('cls')
    elif idex == '5':
        os.system('cls')
        print('�������豸��ţ�')
        data = int(input())
        data = (data,)
        res = getByNo(conn, data)
        print(
            '���' + '\t' + '����' + '\t' + '����' + '\t' + '����' + '\t' + '���ѹ' + '\t' + '�����' + '\t' + '�۸�' + '\t' + '����' + '\t' + '��Ϣ')
        for row in res:
            for item in row:
                print(item, end='')
                print('\t', end='')
            print()
        print('���س�����������')
        input()
        os.system('cls')
    elif idex == '6':
        res = getInventoryValue(conn)
        print('�ܼ�ֵΪ��', end='')
        print(res[0][0])
        print('���س�����������')
        input()
        os.system('cls')
    elif idex == '0':
        break

conn.close()
