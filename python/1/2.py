def is_odd(num):
    if (num % 2 == 0):
        return 0
    else:
        return 1


if __name__ == '__main__':
    odd_sum = 0

    for i in range(100, 1000 + 1):
        if (is_odd(i)):
            odd_sum = odd_sum + i

    print("Sum:" + str(odd_sum))
