#include <stdio.h>

int main (void) {

    float money = 0;
    int n100 = 0, n50 = 0, n20 = 0, n10 = 0, n5 = 0, n2 = 0, n1 = 0;
    do {

        printf("Money: ");
        scanf("%f", &money);

} while (money < 0);

    do {

        if (money >= 100) {
            money = money - 100;
            n100++;
        } else if (money < 100 && money >= 50) {
            money = money - 50;
            n50++;
        } else if (money < 50 && money >= 20) {
            money = money - 20;
            n20++;
        } else if (money < 20 && money >= 10) {
            money = money - 10;
            n10++;
        } else if (money < 10 && money >= 5) {
            money = money - 5;
            n5++;
        } else if (money < 5 && money >= 2) {
            money = money - 2;
            n2++;
        } else if (money < 2 && money >= 1) {
            money = money - 1;
            n1++;
        }

    } while (money > 0);

    printf("Quantidade de Notas: \n100 = %i \n50 = %i \n20 = %i \n10 = %i \n5 = %i \n2 = %i \n1 = %i\n"
            , n100, n50, n20, n10, n5, n2, n1);
}