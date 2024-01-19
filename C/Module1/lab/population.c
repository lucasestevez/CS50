#include <cs50.h>
#include <stdio.h>

int main (void) {

    int i = 0, start_size = 0, end_size = 0;

    do {

        start_size = get_int("Start Size: ");

        if (start_size < 9) {

            printf("Informe um número Inteiro maior que 9\n");
        }

    } while (start_size < 9);

    do {

        end_size = get_int("End Size: ");

        if (end_size < start_size) {

            printf("Informe um número Inteiro maior que a População Inicial\n");
        }

    } while (end_size < start_size);

    while (end_size > start_size) {

        start_size = start_size + (start_size / 3) - (start_size / 4);
        i++;
    }

    printf("Years: %i\n", i);
}
