import csv
import sys


def main():
    # Check for command-line usage
    database_path, sequence_path = get_file_args()

    # Read database file into a variable
    people = read_people_from_database(database_path)

    # Read DNA sequence file into a variable
    sequence = read_sequence(sequence_path)

    # Find longest match of each STR in DNA sequence
    result, subsequences = find_str_match_dna(people, sequence)

    # Check database for matching profiles
    return find_person(people, result, subsequences)


def find_person(people, result, subsequences):
    for person in people:
        match = 0
        for i in subsequences:
            if int(person[i]) == result[i]:
                match += 1

        if match == len(subsequences):
            print(person["name"])
            return
    print("No match!")
    return


def find_str_match_dna(people, sequence):
    subsequences = list(people[0].keys())[1:]
    result = {}
    for i in subsequences:
        result[i] = longest_match(sequence, i)
    return result, subsequences


def read_sequence(sequence_path):
    with open(sequence_path) as sequence_file:
        return sequence_file.read()


def read_people_from_database(database_path):
    people = []
    with open(database_path) as csv_file:
        reader = csv.DictReader(csv_file)
        for person in reader:
            people.append(person)

    return people


def get_file_args():
    if len(sys.argv) != 3:
        print("Usage: python dna.py databses/***.txt sequences/***.txt")
        sys.exit(1)
    return sys.argv[1], sys.argv[2]


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

    # After checking for runs at each character in sequence, return longest run found
    return longest_run


main()
