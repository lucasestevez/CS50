// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node {

    char word[LENGTH + 1];
    struct node *next;

} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 5381;

// Hash table
node *table[N];

unsigned int dictionary_size = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word) {

    node *list = table[hash(word)];

    for (node *tmp = list; tmp != NULL; tmp = tmp->next) {

        if (strcasecmp(tmp->word, word) == 0) {

            return true;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word) {

    int hash_run = 5381;

    for (int i = 0; word[i] != '\0'; i++) {

        hash_run = ((hash_run << 5) + hash_run) + tolower(word[i]);
    }

   return hash_run % N;

}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary) {

    FILE *file = fopen(dictionary, "r");

    if (file == NULL) {

        printf("Could not load %s.\n", dictionary);
        return false;
    }

    if (ferror(file)) {

        fclose(file);
        printf("Error reading %s.\n", dictionary);
        return false;
    }

    char word[LENGTH + 1];

    while (fscanf(file, "%s", word) != EOF) {

        node *n = malloc(sizeof(node));

        if (n == NULL) {

            printf("Could not allocate memory.\n");
            return false;
        }

        strcpy(n->word, word);

        unsigned int position = hash(word);
        n->next = table[position];
        table[position] = n;
        dictionary_size++;
    }

    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void) {

    return dictionary_size;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void) {

    for (int i = 0; i < N; i++) {

        while (table[i] != NULL) {

            node *tmp = table[i]->next;
            free(table[i]);
            table[i] = tmp;
        }
    }


    return true;
}
