from math import sin
from math import cos
from math import tan
import numbers
    

def main():
    flag_1 = 0
    arr = ['sin','cos','tan']#Storage function name
    sum = 0
    while(True):
        s = input("Enter a trigonometric function(sin,cos,tan)")#Enter the function name
        for i in arr:#Determine whether the function name is correct
            if(i == s):
                flag_1 = 1
                break
        if(flag_1):
            break
        else:
            print("Invalid input")            
    a = eval(input("Enter lower bound a:") )#Enter lower bound a
    b = eval(input("Enter upper bound b:") )#Enter lower bound b      
    n = eval(input("Enter the number of sub-intervals n:") )#Enter sub-intervals n

    if not isinstance(a, int):
        print("a is not a integer")
        return
    if not isinstance(b, int):
        print("b is not a integer")
        return
    if n == 0:
        print("n can't be 0")
        return

    for i in range(1,n+1):
        temp = ((b-a)/n)*eval(s+"(a+(b-a)/n*(i-1/2))")
        sum+=temp
    print(sum)
        
if __name__ == '__main__':
    main()

