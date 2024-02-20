# import libraries
from cs50 import get_float

# get user input
while True:
    change = get_float("Change owed: ") * 100
    if change > 0:
        break

# set intial number of coins needed to 0
coins = 0

# calculate number of quarters needed
numQuarters = (change / 25) - ((change % 25)/25)
change = change % 25

# calculate number of dimes needed
numDimes = (change / 10) - ((change % 10)/10)
change = change % 10

# calculate number of nickels needed
numNickels = (change / 5) - ((change % 5)/5)
change = change % 5

# calculate number of pennies needed
numPennies = change

# calculate total number of coins needed
coins = numQuarters + numDimes + numNickels + numPennies

# print number of coins needed
print(coins)