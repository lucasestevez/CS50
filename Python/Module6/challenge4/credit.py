def main():
    cc_number = input("Number: ")
    card_brand = verify_card_brand(cc_number)
    print(card_brand)


def verify_card_brand(cc_number):
    digits = len(cc_number)
    brand = ""

    if digits in [13, 16] and cc_number.startswith("4"):
        brand = "VISA"
    elif digits == 15 and cc_number.startswith(("34", "37")):
        brand = "AMEX"
    elif digits == 16 and cc_number.startswith(("51", "52", "53", "54", "55")):
        brand = "MASTERCARD"

    if brand != "" and check_luhn(cc_number):
        return brand
    else:
        return "INVALID"


def check_luhn(cc_number):
    digits_sum = 0

    for i, digit in enumerate(cc_number[::-1]):
        if i % 2 == 1:
            multiplied_digit = int(digit) * 2
            if multiplied_digit > 9:
                digits_sum += 1 + multiplied_digit % 10
            else:
                digits_sum += multiplied_digit
        else:
            digits_sum += int(digit)

    return digits_sum % 10 == 0


main()
