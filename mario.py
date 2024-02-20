# import libraries
from cs50 import get_int

# get user input
# only allow integers between 1-8 inclusive
while True:
    height = get_int("Height: ")
    if height >= 1 and height <= 8:
        break

# print pyramid of inputed height
j = 1
for i in range(height):
    for k in range(height - j):
        print(" ", end="")
    for n in range(j):
        print("#", end="")
    print("")
    j = j + 1
