total_num = 0

for i in range(1, 64):
    total_num += 2 ** i

print("total_num:" + str(total_num))
total_ton = total_num * 50 / 1000000000
print("total_ton:" + str(total_ton))
