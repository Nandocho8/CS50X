import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py data.csv sequence.txt")

    # TODO: Read database file into a variable
    dna_data = []
    filecsv = sys.argv[1]
    # open file and read keys
    with open(filecsv) as f:
        row = csv.DictReader(f)
        for data in row:
            # changes str to values to int
            for key, value in data.items():
                if key != 'name':
                    data[key] = int(data[key])
            dna_data.append(data)

    # TODO: Read DNA sequence file into a variable
    filetxt = sys.argv[2]
    with open(filetxt, 'r') as f:
        text = f.read()

    # TODO: Find longest match of each STR in DNA sequence
    matches = []
    # assing to keys a list with names to keys
    keys = dna_data[0].keys()
    # loop for each header find matches and append to list matches
    for key in keys:
        if key != 'name':

            data = longest_match(text, key)
            matches.append(data)

    # TODO: Check database for matching profiles
    # find lend to general list
    len_find = len(dna_data)
    # looping a list
    for i in range(len_find):
        # assign in values all data form i position to list except name
        values = list(dna_data[i].values())[1:]
        # assign a list with only name of i position
        name_match = list(dna_data[i].values())[:1]
        # assign a len column from this person
        len_column = len(values)
        # initial count column
        i = 0
        # loop values (list) one at one
        for value in values:
            # if no match with value from loop and value save en matches[pos]break loop
            if value != matches[i]:
                break
            # else add count
            i += 1
        # confirm complete match with counter and len column and print name save in name_match
        if i == len_column:
            print(name_match[0])
            return

    print('No match')
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
