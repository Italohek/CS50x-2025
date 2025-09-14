def isValid(x):
    if not x.isdigit():
        return "INVALID"
    lenght = len(x)
    prefix = x[:2]
    if (lenght == 16 and "51" <= prefix <= "55"):
        return "MASTERCARD"
    elif (lenght == 15 and (prefix == "34" or prefix == "37")):
        return "AMEX"
    elif (x[0] == '4' and (lenght == 16 or lenght == 13)):
        return "VISA"
    else:
        return "INVALID"


def cardVerifier(number):
    even_numbers = odds_numbers = temp_even = 0
    # First, check if the card's length and prefix are valid
    card_type = isValid(number)
    if (card_type == "INVALID"):
        return "INVALID"
    # Get every second digit from the second-to-last
    for even in (number[-2::-2]):
        temp_even = int(even) * 2
        even_numbers += (temp_even // 10) + (temp_even % 10)

    # Get the remaining digits from the end
    for odds in (number[::-2]):
        odds_numbers += int(odds)

    # Combine the sums
    final_value = odds_numbers + even_numbers

    # Check if the final sum is divisible by 10
    if (final_value % 10 == 0):
        return card_type
    else:
        return "INVALID"


# Get user input.
number_input = input("Number: ")
# Call the function and print the result.
print(cardVerifier(number_input))
