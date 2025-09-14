import csv
from sys import argv, exit


def main():
    if (len(argv) != 3):
        print(f"Missing command-line argument")
        exit(1)  # 1 = Missing command line argument

    # read the database
    rows_database = []
    with open(f"{argv[1]}", "r") as file:
        file_reader = csv.reader(file)
        for line in file_reader:
            rows_database.append(line)

    # read the dna sequence
    with open(f"{argv[2]}", "r") as file:
        rows_dna_sequence = file.read()

    # ser strs as the first column+ row 0
    strs = rows_database[0][1:]

    # calculates the longest match using the function already made
    values = []
    for subsequence in strs:
        longest = longest_match(rows_dna_sequence, subsequence)
        values.append(longest)

    # compares each person inside the database
    for i in range(1, len(rows_database)):
        person = rows_database[i]
        name = person[0]
        matches = True

        for j in range(len(strs)):
            if int(person[j + 1]) != values[j]:
                matches = False
                break

        if matches:
            print(name)
            return

    print("No match")
    exit(2)  # no match code
    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
