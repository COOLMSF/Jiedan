import sys
# radare2 interface
import r2pipe


# this is a section, where data hide
def extract_ehframe(infile, outfile):
    # store needed (eh_frame) sessions
    ehframe_sessions = []

    # open file
    r2 = r2pipe.open(infile)
    # analyze program
    r2.cmd("aaa")
    # r2.cmd("iS") extract all sections
    allsessions = r2.cmd("iS").split('\n')

    for allsession in allsessions:
        if "eh_frame" in allsession:
            ehframe_sessions.append(allsession)

    # ehframe_sessions will contains .eh_frame_hdr and .eh_frame
    # we only need .eh_frame
    # data_size  = 10000000
    data_size = 0x4
    # print(ehframe_sessions)
    ehframe_session = ehframe_sessions[-1]
    ehframe_session_start_addr = ehframe_session.split(' ')[6]
    ehframe_session_size = ehframe_session.split(' ')[5]

    # 计算隐写数据的地址

    # aaaaaaaaaaAAAA
    # start addr 0, size 10,
    # start addr 0, size 14
    # size - 4
    # 内存对齐
    data_start_addr = hex(int(ehframe_session_start_addr, 16) + int(ehframe_session_size, 16) - data_size - 0x5)

    # print(ehframe_session_start_addr)
    # print(type(ehframe_session_start_addr))

    # print("ehframe_session_start_addr:" + hex(int(ehframe_session_start_addr, 16)))
    # print("ehframe_session_size:" + hex(int((ehframe_session_size), 16)))

    # print("[+] Seeking to start address")
    # seek to start address
    # s代表移动, s 0x1000，就代表移动0x1000这个位置
    r2.cmd("s " + hex(int(data_start_addr, 16)))
    # wtf
    print("[+] Write result to file")
    # write the file
    # wtf outfile 100
    r2.cmd("wtf " + outfile +  " " + str(data_size))

if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("usage: " + sys.argv[0] + "infile " + "outfile")
        exit()
    print(sys.argv[1] + sys.argv[2])
    extract_ehframe(sys.argv[1], sys.argv[2])
