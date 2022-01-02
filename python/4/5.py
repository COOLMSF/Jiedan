L = []
while 1:  # if there's no abnormality,jump out of the dead cycle,otherwise re-enter
    try:
        num = int(input("Please enter a postive integer:"))
        break
    except Exception:
        print("Input Error,Please re-enter!")
print("The prime numbers smaller than %d include:" % num)

for x in range(num):  # 0 to 6,excluding 6
    if x < 2:  # if less than,continue the iteration
        continue
    for i in range(2, x):  # 2 to x,excluding x
        if x % i == 0:  # if x mod i = 0,it's not prime
            break
    else:  # it's a prime ,add to list
        L.append(x)
for i in range(len(L)):
    if i % 8 == 0 and i != 0:
        print("")  # print "\n"
    print("%d\t" % L[i], end="")  # print L[i]
