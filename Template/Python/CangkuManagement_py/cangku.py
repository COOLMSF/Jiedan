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


# 载入初始数据
def loadData(conn):
    data = [(1, '电动机1', '电动机', 1, 2, 1, 100, 10, '这是第一种电动机'), (2, '电动机2', '电动机', 2, 4, 1, 100, 10, '这是第二种电动机'),
            (3, '电阻1', '电阻', 1, 1, 1, 10, 100, '这是第一种电阻'), (4, '电阻2', '电阻', 2, 2, 1, 10, 100, '这是第二种电阻')]
    cur = conn.cursor()
    insert = 'insert into electronicComponents ' \
             'values (?,?,?,?,?,?,?,?,?)'
    cur.executemany(insert, data)
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


# 获取每月消耗量
def monthlyConsumption(conn):
    cur = conn.cursor()
    select = 'select cno, sum(record.quantity), strftime("%Y-%m",date) ' \
             'from (select * from record where quantity>0) as record ' \
             'group by cno, strftime("%Y-%m",date)'
    cur.execute(select)
    res = cur.fetchall()
    cur.close()
    return res


# 获取每周消耗量
def weekConsumption(conn):
    cur = conn.cursor()
    select = 'select cno, sum(record.quantity), strftime("%Y-%W",date) ' \
             'from (select * from record where quantity>0) as record ' \
             'group by cno, strftime("%Y-%W",date)'
    cur.execute(select)
    res = cur.fetchall()
    cur.close()
    return res


# 获取每月销售总价值
def getOutboundComponentsValuePerMonth(conn):
    cur = conn.cursor()
    select = 'select sum(record.quantity*electronicComponents.price), strftime("%Y-%m",date) ' \
             'from (select * from record where quantity>0) as record left join electronicComponents ' \
             'on record.cno  = electronicComponents.no ' \
             'group by strftime("%Y-%m-%w",date) '
    cur.execute(select)
    res = cur.fetchall()
    cur.close()
    return res


# ui界面
def ui():
    conn = init('electronicComponents.db')
    while (True):
        print('*电子元件管理系统')
        print('*请选择功能')
        print('1.入库')
        print('2.出库')
        print('3.添加新器件')
        print('4.按照类型查看功能')
        print('5.按照编号查看信息')
        print('6.在库元器件总价值')
        print('7.每月出库元器件总价值')
        print('8.各类元器件周消耗')
        print('9.各类元器件月消耗')
        print('0.退出')
        print('请输入选择的功能编号：')
        idex = input()
        if idex == '1':
            os.system('cls')
            print('请依次输入元器件编号和数量，使用空格隔开：')
            data = input().split()
            data[0] = int(data[0])
            data[1] = int(data[1])
            data = tuple(data)
            update(conn, data)
        elif idex == '2':
            os.system('cls')
            print('请依次输入元器件编号和数量，使用空格隔开：')
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
            print('请依次输入元器件编号，名字，类型，电阻，额定电压，额定电流，价格，数量，说明，使用空格隔开：')
            data = input().split()
            for i in range(4, 8):
                data[i] = int(data[i])
            data = tuple(data)
            insertInStorage(conn, data)
        elif idex == '4':
            os.system('cls')
            print('请输入元器件类型：')
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
            print('请输入元器件编号：')
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
        elif idex == '7':
            res = getOutboundComponentsValuePerMonth(conn)
            print('月份\t价值')
            for row in res:
                print('{}\t{}'.format(row[0], row[1]))
            print('按回车返回主界面')
            input()
            os.system('cls')
        elif idex == '8':
            res = monthlyConsumption(conn)
            print('编号\t消耗量\t时间')
            for row in res:
                print('{}\t{}\t{}'.format(row[0], row[1], row[2]))
            print('按回车返回主界面')
            input()
            os.system('cls')
        elif idex == '9':
            res = weekConsumption(conn)
            print('编号\t消耗量\t时间')
            for row in res:
                print('{}\t{}\t{}'.format(row[0], row[1], row[2]))
            print('按回车返回主界面')
            input()
            os.system('cls')
        elif idex == '0':
            break

    conn.close()


if __name__ == '__main__':
    ui()