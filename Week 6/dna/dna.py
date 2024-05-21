import csv
from sys import argv


def main():

    # TODO: Check for command-line usage
    if len(argv) != 3:
        print("not a valid argument")
        return 1
    # TODO: Read database file into a variable
    rows = []
    with open(argv[1], 'r') as file:
        reader = csv.DictReader(file)
        for row in reader:
            rows.append(row)

    # TODO: Read DNA sequence file into a variable
    with open(argv[2], 'r') as file:
        dna_sequence = file.read()

    # TODO: Find longest match of each STR in DNA sequence
    subs = list(rows[0].keys())[1:]

    result = {}

    for subsequence in subs:
        result[subsequence] = longest_match(dna_sequence, subsequence)
    # TODO: Check database for matching profiles
    for person in rows:
        match = 0
        for subsequence in subs:
            if int(person[subsequence]) == result[subsequence]:
                match += 1
        if match == len(subs):
            print(person["name"])
            return
    print("No match")

    return


def longest_match(sequence, subsequence):

    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    for i in range(sequence_length):
        count = 0

        while True:

            start = i + count * subsequence_length
            end = start + subsequence_length

            if sequence[start:end] == subsequence:
                count += 1

            else:
                break

        longest_run = max(longest_run, count)

    return longest_run


if __name__ == "__main__":
    main()
