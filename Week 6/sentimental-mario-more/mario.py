height = input("Height: ")

# Garants that the user inputs a number between 8 and 1
while (not (height.isdigit()) or int(height) < 1 or int(height) > 8):
    height = input("Height: ")

# Checks if the height are between 1 and 8
height = int(height)
if (1 <= height <= 8):
    for i in range(height):
        print(" " * (height - (i + 1)) + "#" * (i + 1) + "  " + "#" * (i + 1))
