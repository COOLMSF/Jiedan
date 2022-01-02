finalAccountValue = int(input("Enter the final account value:"))
annuakInterestRate = float(input("Enter the anual interest rate:"))

# Rate should be devided by 100
annuakInterestRate /= 100
year = int(input("Enter the years:"))

initialValue = finalAccountValue / ((1 + annuakInterestRate) ** year)

print("The initial value is:" + str(initialValue))
