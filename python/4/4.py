n = int(input("Please enter a positive integer:"))

print("m\tm+1\tm**(m+1)")
for i in range(1, n + 1):
    print(str(i) + "\t" + str(i + 1) + "\t" + str(i**(i+1)))
