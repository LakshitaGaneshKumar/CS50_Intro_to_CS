import csv
import sys


def main():

    # Check for command-line usage
    if len(sys.argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        exit()

    # Read database file into a variable
    with open(sys.argv[1]) as data_file:
        # read data into data_reader
        data_reader = csv.reader(data_file)
        data = list(data_reader)

    # Read DNA sequence file into a variable
    with open(sys.argv[2]) as sequence_file:
        # read sequence into sequence_reader
        sequenceF = sequence_file.read()

    # Find longest match of each STR in DNA sequence
    match_list = []
    for i in range(1, len(data[0])):
        match = longest_match(sequenceF, data[0][i])
        match_list.append(match)

    # Check database for matching profiles
    suspect = "No match"
    matchCount = 0

    for i in range(1, len(data)):
        for j in range(len(match_list)):
            if int(data[i][j + 1]) == match_list[j]:
                matchCount += 1
        if matchCount == len(match_list):
            suspect = data[i][0]
            break
        else:
            matchCount = 0

    print(suspect)

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
