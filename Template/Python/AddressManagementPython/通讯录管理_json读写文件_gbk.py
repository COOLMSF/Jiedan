import json

#存入已经含有的号码
dict={'小明':['001','广州','男', '10010'],
      }


#操作菜单模块
def show_menu():
    print("操作菜单："
          " 1：添加"
          " 2：删除"
          " 3：修改"
          " 4：搜索"
          " 5：保存到文件"
          " 6：从文件读取"
          " 7：退出")
    print("\n")


#添加操作模块
def add_user(dict):
    a=input("要添加名字：")    
    # 找到成员
    if a in dict:
        print("{}已经在电话簿中".format(a))               
    else:
       b=input("输入号码：")
       c=input("输入地址：")
       d=input("输入性别：")
       e=input("输入微信号：")
       dict1={a:[b,c,d,e]}
       dict.update(dict1)
       print("成功添加 {0:} ".format(a))
       print("\n")
      
       
def del_userect(dict):
        a=input("要删除名字：")
        # 找到成员
        if a in dict:
            del dict[a]
            print("成功删除 {0:}".format(a))
        else:
            print("该好友不在电话簿中")


def modify_user(dict):
        a=input("你要修改的姓名：")
        
        # 找到成员
        if a in dict:
                
                b=input("请输入修改后的号码：")
                c=input("请输入修改后的地址：")
                dict[a][0]=b
                dict[a][1]=c
                print("修改后的信息:\n\n"+a+"\t"+dict[a][0]+"\t"+dict[a][1]+"\n")
                                            
        else:
                print("该人不在电话簿中")


            
def search_user(dict):
    a=input("输入要查找的姓名：")
    # 遍历字典里面的所有成员
    if a in dict:
        print(a+"\t"+dict[a][0]+"\t"+dict[a][1]+"\t"+dict[a][2]+"\t"+dict[a][3]+"\t"+"\n")
    else:
        print("该人不在电话簿中")
              
#将电话簿打印
def save(dict):
    # 将字典里面的数据导出
    json.dump(dict, open("result.txt", "w"), ensure_ascii=False)
    print("保存成功")

def load():
    # 加载字典里面的数据到内存
    dict = json.load(open("result.txt"))
    print("加载成功")
      

    


dict = json.load(open("result.txt"))
print("加载数据成功")
#进行操作     
while True:
    print("姓名\t号码\t地址\t性别\t微信号\t")
    # 遍历所有成员
    for i in dict:
        # 输出所有信息
        print(i+" \t"+dict[i][0]+"\t"+dict[i][1]+"\t"+dict[i][2]+"\t"+dict[i][3]+'\n')
    print("\n")

    show_menu()    

    # 获取用户输入的选项
    a=eval(input("输入要进行的操作："))
    if a==1:
        add_user(dict)
    elif a==2:
        del_userect(dict)
    elif a==3:
        modify_user(dict)       
    elif a==4:
        search_user(dict)        
    elif a==5:
        save(dict)
    elif a==6:
        load()
    elif a==7:
        break        
         
