import json

#�����Ѿ����еĺ���
dict={'С��':['001','����','��', '10010'],
      }


#�����˵�ģ��
def show_menu():
    print("�����˵���"
          " 1�����"
          " 2��ɾ��"
          " 3���޸�"
          " 4������"
          " 5�����浽�ļ�"
          " 6�����ļ���ȡ"
          " 7���˳�")
    print("\n")


#��Ӳ���ģ��
def add_user(dict):
    a=input("Ҫ������֣�")    
    # �ҵ���Ա
    if a in dict:
        print("{}�Ѿ��ڵ绰����".format(a))               
    else:
       b=input("������룺")
       c=input("�����ַ��")
       d=input("�����Ա�")
       e=input("����΢�źţ�")
       dict1={a:[b,c,d,e]}
       dict.update(dict1)
       print("�ɹ���� {0:} ".format(a))
       print("\n")
      
       
def del_userect(dict):
        a=input("Ҫɾ�����֣�")
        # �ҵ���Ա
        if a in dict:
            del dict[a]
            print("�ɹ�ɾ�� {0:}".format(a))
        else:
            print("�ú��Ѳ��ڵ绰����")


def modify_user(dict):
        a=input("��Ҫ�޸ĵ�������")
        
        # �ҵ���Ա
        if a in dict:
                
                b=input("�������޸ĺ�ĺ��룺")
                c=input("�������޸ĺ�ĵ�ַ��")
                dict[a][0]=b
                dict[a][1]=c
                print("�޸ĺ����Ϣ:\n\n"+a+"\t"+dict[a][0]+"\t"+dict[a][1]+"\n")
                                            
        else:
                print("���˲��ڵ绰����")


            
def search_user(dict):
    a=input("����Ҫ���ҵ�������")
    # �����ֵ���������г�Ա
    if a in dict:
        print(a+"\t"+dict[a][0]+"\t"+dict[a][1]+"\t"+dict[a][2]+"\t"+dict[a][3]+"\t"+"\n")
    else:
        print("���˲��ڵ绰����")
              
#���绰����ӡ
def save(dict):
    # ���ֵ���������ݵ���
    json.dump(dict, open("result.txt", "w"), ensure_ascii=False)
    print("����ɹ�")

def load():
    # �����ֵ���������ݵ��ڴ�
    dict = json.load(open("result.txt"))
    print("���سɹ�")
      

    


dict = json.load(open("result.txt"))
print("�������ݳɹ�")
#���в���     
while True:
    print("����\t����\t��ַ\t�Ա�\t΢�ź�\t")
    # �������г�Ա
    for i in dict:
        # ���������Ϣ
        print(i+" \t"+dict[i][0]+"\t"+dict[i][1]+"\t"+dict[i][2]+"\t"+dict[i][3]+'\n')
    print("\n")

    show_menu()    

    # ��ȡ�û������ѡ��
    a=eval(input("����Ҫ���еĲ�����"))
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
         
