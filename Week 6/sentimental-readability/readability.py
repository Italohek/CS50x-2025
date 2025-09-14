# Input from the user
text = str(input("Text: "))

# Variables that we'll use later
letters = sentences = 0
words = 1

# For every letter inside text, see if we sum the words, letters or
# sentences
for i in range(0, len(text)):
    aux = text[i]
    if aux == " ":
        words += 1
    elif aux == '.' or text[i] == '!' or text[i] == '?':
        sentences += 1
    elif aux.isalpha():
        letters += 1

# Calculates the L and S from Coleman-Liau index
L = ((letters * 1.0) / (words)) * 100
S = ((sentences * 1.0) / (words)) * 100

cl_index = round((0.0588 * L) - (0.296 * S) - 15.8)

# Prints the right value
if (cl_index < 1):
    print(f"Before Grade 1")
elif (1 <= cl_index <= 15):
    print(f"Grade {cl_index}")
else:
    print(f"Grade 16+")
