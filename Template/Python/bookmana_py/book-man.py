#!/usr/local/bin/python3.7
 #-*-coding:utf-8-*-

# user register
def logon():
    print("Welcome to book management")
    username = input("username：")
    if len(username)<6:
        print("username should not be less than 6 characters")
    else:
        email = input("mail:")
        password = input("password")
        if len(password)<8:
            print("password should not be less than 8 characters")
        else:
            rpassword = input("confirm password:")
            if password ==rpassword:
                print("register success!")
                preserve_data(path,[username,'   '+ email,'   '+ password + '\n'])
                login_tips = input('Are you loged in？(yes/no)')
                if login_tips =='yes':
                    login()
                else:
                    pass
                return True
            else:
                print("password doesn't match, try again!")
                logon()


path = r'user.txt'
def preserve_data(file_path,data):
    with open(file_path,'a') as wstream:
        if wstream.writable():
            wstream.writelines(data)
        else:
            print("no permission!")

def login():
    print("Welcome to bookmanagement")
    tips = input("Are you register?(yes/no)")
    if tips =='yes':
        while True:
            username = input("username:")
            password = input("password:")
            try:
                with open(path, 'rb') as stream:
                    result = stream.readlines()
                    uesr_list = [i.decode() for i in result]
                    for i in uesr_list:
                        info = i.split('   ')
                        if username == info[0] and password == info[2].rstrip('\r\n'):
                            print("login successful")
                            operate(book_path,username)
                            break
                    else:
                        raise Exception("username or password error!")

            except Exception as err:
                print(err)
            else:
                break
    else:
        print("register first!")
        logon()

def find_books(path):
    try:
        with open(path, 'r') as rstream:
            container = rstream.readlines()
            new_container = [books_name.rstrip('\n') for books_name in container]
            for b_name in new_container:
                print("《{}》".format(b_name))

    except Exception as err:
        print("error:",err)

def add_book(b_path,username):
    # check if adminstrator
    permission(b_path, username)
    with open(b_path, 'a') as wstream:
        if wstream.writable:
            msg = input("bookname:")
            try:
                with open(b_path) as rstream:
                    while True:
                        line = rstream.readline()
                        line = line.rstrip('\n')
                        if not line:
                            book = '\n' + msg
                            wstream.write(book)
                            print("add success")
                            break
                        else:
                            if line == msg:
                                print("{}duplicate".format(msg))
                                break
            except Exception as err:
                print("error:", err)
        else:
            print("no permission")

def update_book(b_path,username):
    permission(b_path, username)
    try:
        with open(b_path, 'r') as rstream:
            container = rstream.read()
            container = container.split('\n')
            find_books(book_path)
            book_name = input("book to modify:")
            for i in range(len(container)):
                if book_name == container[i]:
                    rbook_name = input("new name:")
                    container[i] = rbook_name + '\n'
                else:
                    container[i] = container[i] + '\n'
            with open(b_path, 'w') as wwstream:
                wwstream.writelines(container)
            print("modify succeed")
    except Exception as err:
        print("error:", err)

def del_book(b_path,username):
    permission(path, username)
    try:
        with open(b_path, 'r') as rstream:
            container = rstream.read()
            container = container.split('\n')
            find_books(book_path)
            book_name = input("bookname to delete:")
            for i in range(len(container) - 1):
                if book_name == container[i]:
                    container.remove(container[i])
                else:
                    container[i] = container[i] + '\n'
            with open(b_path, 'w') as wwstream:
                wwstream.writelines(container)
            print("delete succeed")
    except Exception as err:
        print("error:", err)

# borrow book
def borrow_book(username):
    while True:
        print("book list:")
        find_books(book_path)
        borrow_books = input("select book:")
        try:
            with open('user_books.txt') as rstream:
                lines = rstream.readline()
                lines = lines.rstrip('\n')
                lines = lines.split(' ')
                if borrow_books not in lines:
                    if username in lines:
                        with open('user_books.txt', 'a') as wstream:
                            if borrow_books not in lines:
                                wstream.write(' {}'.format(borrow_books))
                                print("borrow succeed")
                                break
                            else:
                                print("you have borrowed the book!")
                                break
                    else:
                        with open('user_books.txt', 'a') as wstream:
                            wstream.write('\n{} {}\n'.format(username, borrow_books))
                            print("borrow succeed")
                            break
                else:
                    print("<<{}>>has been borrowed by {}".format(borrow_books,lines[0]))
        except Exception as err:
            print("error:", err)

def return_book(username):
    try:
        with open('user_books.txt') as rstream:
            lines = rstream.readlines()
            for i in range(len(lines)):
                # delete unneed character
                lines[i] = lines[i].rstrip('\n')
                lines[i] = lines[i].rstrip(' ')
                lines[i] = lines[i].split(' ')
                for ii in range(len(lines[i])-1):
                    if username == lines[i][0]:
                        print("{}list to return".format(username))
                        print(lines[i][ii+1])
                        msg = input("select book to return:")
                        with open('user_books.txt') as rstream:
                            lines = rstream.readlines()
                            for i in range(len(lines)):
                                if username in lines[i] and msg in lines[i]:
                                    lines[i] = lines[i].replace(msg, '')
                                    with open('user_books.txt', 'w') as wstream:
                                        wstream.writelines(lines)
                                        print("return book succeed!")
                                        break

                            with open('user_books.txt') as rstream:
                                lines = rstream.readlines()
                                for i in range(len(lines)):
                                    lines[i] = lines[i].rstrip('\n')
                                    lines[i] = lines[i].rstrip(' ')
                                    lines[i] = lines[i].split(' ')
                                    for ii in range(len(lines[i])):
                                        if username == lines[i][0] and len(lines[i]) == 1:
                                            lines[i][0] = lines[i][0].replace(lines[i][0], '')
                                            lines.append(lines[i][0])
                                str = ''
                                for i in range(len(lines)):
                                    for ii in range(len(lines[i])):
                                        str += lines[i][ii] + ' '
                                    str += '\n'
                                lines.clear()
                                lines.append(str)

                                with open('user_books.txt', 'w') as wstream:
                                    wstream.writelines(lines)
                    else:
                        print("no book borrowed")

    except Exception as err:
        print("error:", err)

def look_person_info(path,username):
    with open(path) as rstream:
        lines = rstream.readlines()
        # print(lines)
        for info in lines:
            # 分割成一个列表
            info = info.split('   ')
            # print(info)
            if username in info:
                print("----info----")
                print("name:", info[0])
                print("mail:", info[1])
                print("password:", info[2].rstrip(' '))
                       
def update_password(path,username):
    tips = input("operation：\n 1.change mail\n 2.change password\n")

    if tips =='1':
        new_email = ''
        line = []
        try:
            with open(path) as rstream:
                while True:
                    line = rstream.readline()
                    if not line:
                        break
                    line = line.split('   ')
                    line[2] = line[2].rstrip('\n')
                    if username == line[0]:
                        new_email = input("new mail:")
                        line[1] = new_email
                        break
        except Exception as err:
            print(err)

        else:
            with open(path, 'a') as wstream:
                for i in range(len(line)):
                    if i == 0:
                        line[i] = '\n' + line[i] + '   '
                    else:
                        line[i] = line[i] + '   '
                wstream.writelines(line)
                print("modify succed")
            with open(path) as rstream:
                lines = rstream.readlines()
                i = 0
                l = len(lines)
                while i < l:
                    if username in lines[i] and new_email not in lines[i]:
                        lines.remove(lines[i])
                    i += 1
                    l -= 1
                with open(path, 'w') as wstream:
                    wstream.writelines(lines)
    elif tips =='2':
        new_password = ''
        line = []
        try:
            with open(path) as rstream:
                while True:
                    line = rstream.readline()
                    if not line:
                        break
                    line = line.split('   ')
                    line[2] = line[2].rstrip('\n')
                    if username == line[0]:
                        new_password = input("new password:")
                        if new_password ==line[2]:
                            raise Exception("password should not be the same")
                        else:
                            line[2] =new_password
                            break
        except Exception as err:
            print(err)

        else:
            with open(path,'a') as wstream:
                for i in range(len(line)):
                    if i ==0:
                        line[i] = '\n'+line[i]+'   '
                    else:
                        line[i] = line[i] +'   '
                wstream.writelines(line)
                print("modify succeed")
            with open(path) as rstream:
                lines = rstream.readlines()
                i =0
                l = len(lines)
                while i < l:
                    if username in lines[i] and new_password not in lines[i]:
                        lines.remove(lines[i])
                    i+=1
                    l-=1
                with open(path,'w') as wstream:
                    wstream.writelines(lines)

def person_information(path,username):
    tips = input("operation：\n 1.check personal info\n 2.modify personal info\n")
    if tips =='1':
        look_person_info(path,username)
    elif tips =='2':
        update_password(path, username)

def permission(user_path,username):
    try:
        with open(user_path) as rstream:
            while True:
                line = rstream.readline()
                if not line:
                    break
                line = line.split('   ')
                for i in range(len(line)):
                    line[i] = line[i].rstrip('\n')
                if username == 'admin123':
                    pass
                else:
                    print("only admin123 can do this operation")
                    operate(path, username)
    except Exception as err:
        print("error:",err)

book_path = r'book.txt'
def operate(b_path,username):
    while True:
        msg = input("operation:\n 1.query book\n 2.add book\n 3.modify book\n 4.delete book\n 5.borrow book\n 6.return book\n 7.personal info\n 8.logout\n")
        # query book
        if msg =='1':
            find_books(book_path)
        # add book
        elif msg =='2':
            add_book(b_path, username)
        # modify book
        elif msg =='3':
            update_book(b_path, username)
        # del book
        elif msg =='4':
            del_book(b_path, username)
        # borrow book
        elif msg =='5':
            borrow_book(username)
        # return book
        elif msg =='6':
            return_book(username)
        # personal info
        elif msg =='7':
            person_information(path, username)
        # exit
        elif msg =='8':
            msg = input("are you sure to eixt？(yes/no)")
            if msg == 'yes':
                break

if __name__ == "__main__":
    login()
