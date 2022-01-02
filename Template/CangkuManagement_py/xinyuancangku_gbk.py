import pathlib
import sqlite3
import os

# 库存警戒数量
inventoryAlertValue = 5

# 插入新元件
def insertInStorage(conn, data):
    cur = conn.cursor()
    insert = 'insert into electronicComponents ' \
             'values (?,?,?,?,?,?,?,?,?)'
    cur.execute(insert, data)
    conn.commit()
    cur.close()


# 初始化
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


# 跟新库存
def updateStorage(conn, data):
    cur = conn.cursor()
    update = 'update electronicComponents set quantity = quantity + ?  where no = ?'
    cur.execute(update, data)
    conn.commit()
    cur.close()


# 写入销售记录
def insertRecord(conn, data):
    cur = conn.cursor()
    insert = 'insert into record(cno,quantity,date) ' \
             'values (?,?,datetime("now"))'
    cur.execute(insert, data)
    conn.commit()
    cur.close()


# 检查库存是否充足
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


# 更新库存
def update(conn, data):
    updateStorage(conn, (data[1], data[0]))
    if (data[1] < 0):
        insertRecord(conn, (data[0], -data[1]))
    res = checkInventory(conn, (data[0],))
    return res


# 根据类型查询功能
def getByType(conn, data):
    cur = conn.cursor()
    select = 'select * ' \
             'from electronicComponents ' \
             'where type = ?'
    cur.execute(select, data)
    res = cur.fetchall()
    cur.close()
    return res


# 根据编号查询信息
def getByNo(conn, data):
    cur = conn.cursor()
    select = 'select * ' \
             'from electronicComponents ' \
             'where no = ? '
    cur.execute(select, data)
    res = cur.fetchall()
    cur.close()
    return res


# 获取库存总价值
def getInventoryValue(conn):
    cur = conn.cursor()
    select = 'select sum(quantity*price) ' \
             'from electronicComponents '
    cur.execute(select)
    res = cur.fetchall()
    cur.close()
    return res

def login():
    username = input("请输入管理员账号：")
    passwd = input("请输入管理员密码：")

    if username != "root" and passwd != "123":
        print("账户或密码错误")
        exit(-1)


login()
conn = init('xinyuancangku.db')
while (True):
    print('-' * 10 + '信院管理系统' + '-' * 10)
    print('1.入库')
    print('2.出库')
    print('3.添加新设备')
    print('4.按照类型查看功能')
    print('5.按照编号查看信息')
    print('6.仓库设备总价值')
    print('0.退出')
    print('请输入选择的功能编号：')
    idex = input()
    if idex == '1':
        os.system('cls')
        print('请依次输入设备编号和数量，使用空格隔开：')
        data = input().split()
        data[0] = int(data[0])
        data[1] = int(data[1])
        data = tuple(data)
        update(conn, data)
    elif idex == '2':
        os.system('cls')
        print('请依次输入设备件编号和数量，使用空格隔开：')
        data = input().split()
        data[0] = int(data[0])
        data[1] = -int(data[1])
        data = tuple(data)
        res = update(conn, data)
        if res == False:
            print('库存不足')
            print('按回车返回主界面')
            input()
    elif idex == '3':
        os.system('cls')
        print('请依次输入设备编号(数字)，名字，类型，电阻(数字)，额定电压(数字)，额定电流(数字)，价格(数字)，数量(数字)，说明，使用空格隔开：')
        data = input().split()
        for i in range(4, 8):
            data[i] = int(data[i])
        data = tuple(data)
        insertInStorage(conn, data)
    elif idex == '4':
        os.system('cls')
        print('请输入设备类型：')
        data = input()
        data = (data,)
        res = getByType(conn, data)
        print('编号' + '\t' + '功能')
        for row in res:
            print(row[1] + '\t' + row[-1])
        print('按回车返回主界面')
        input()
        os.system('cls')
    elif idex == '5':
        os.system('cls')
        print('请输入设备编号：')
        data = int(input())
        data = (data,)
        res = getByNo(conn, data)
        print(
            '编号' + '\t' + '名字' + '\t' + '类型' + '\t' + '电阻' + '\t' + '额定电压' + '\t' + '额定电流' + '\t' + '价格' + '\t' + '数量' + '\t' + '信息')
        for row in res:
            for item in row:
                print(item, end='')
                print('\t', end='')
            print()
        print('按回车返回主界面')
        input()
        os.system('cls')
    elif idex == '6':
        res = getInventoryValue(conn)
        print('总价值为：', end='')
        print(res[0][0])
        print('按回车返回主界面')
        input()
        os.system('cls')
    elif idex == '0':
        break

conn.close()
