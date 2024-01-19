#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void) {

    bool verify = false;

    do {

    // Get input words from both players
        string word1 = get_string("Player 1: ");
        string word2 = get_string("Player 2: ");

        // Score both words
        int score1 = compute_score(word1);
        int score2 = compute_score(word2);

        // TODO: Print the winner

        if (score1 > score2) {

            printf("Winner: Player 1\n");

        } else if (score1 < score2) {

            printf("Winner: Player 2\n");

        } else {

            printf("Tie\n");
        }

       string play_again = get_string("Play Again (Y/N)?: ");

       if (strcmp(play_again, "Y") || strcmp(play_again, "y")) {

            verify = true;
       }

    } while (verify == true);

    return 0;
}

int compute_score(string word){

    int points = 0;

    // TODO: Compute and return score for string
    for (int i = 0; i < strlen(word); i++) {

        if (word[i] >= 'A' && word[i] <= 'Z' ) {

            int position = word[i] - 65;
            points += POINTS[position];

        } else if (word[i] >= 'a' && word[i] <= 'z') {

            int position = word[i] - 97;
            points += POINTS[position];
        }
    }

    return points;
}
