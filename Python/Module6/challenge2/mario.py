height = 0

while True:

    height = int(input("Height(1 at 8): "))

    if height < 1 or height > 8:
        print("Try again!")
    elif height > 0 or height < 9:
        break

for i in range(height):
    print(" " * (height - i) + "#" * (i + 1) + "  " + "#" * (i + 1))
