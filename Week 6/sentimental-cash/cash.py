from cs50 import get_float

money = -1
while money < 0:
    money = get_float("Change: ")
money = int(round(money * 100))
coin = 0
while money >= 25:
    money -= 25
    coin += 1
while money >= 10:
    money -= 10
    coin += 1
while money >= 5:
    money -= 5
    coin += 1
while money >= 1:
    money -= 1
    coin += 1
print(f"{coin}")
