
coins = {
        "25" : 0,
        "10" : 0,
        "5"  : 0,
        "1"  : 0
}

def main():

    value = get_value()
    calculate_coins(value)

    for i, j in coins.items():

        if j != 0:
            print(i + " cents: "+ str(j))

def get_value():

    while True:
        value = float(input("Change owned: "))
        if value > 0:
            return value
        else:
            print("Try again!")

def calculate_coins(value):

    while value > 0:
        if value >= 0.25:
            value -= 0.25
            coins["25"] += 1
        elif value < 0.25 and value >= 0.10:
            value -= 0.10
            coins["10"] += 1
        elif value < 0.10 and value >= 0.05:
            value -= 0.5
            coins["5"] += 1
        else:
            value -= 0.01
            coins["1"] += 1

main()