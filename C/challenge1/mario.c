#include <stdio.h>

int main (void) {

    int num = 0;

    do {

        printf("Enter the heigth, in intenger number, of the pyramid between 1 and 8: ");
        scanf("%d", &num);

    } while (num > 1 && num < 8 && num % 1 == 0 && num % 2 == 0
        && num % 3 == 0 && num % 5 == 0);


    for (int i = 0; i < num; i++) {

        switch (i) {

            case 0:
                printf("        #");
                break;
            case 1:
                printf("       ##");
                break;
            case 2:
                printf("      ###");
                break;
            case 3:
                printf("     ####");
                break;
            case 4:
                printf("    #####");
                break;
            case 5:
                printf("   ######");
                break;
            case 6:
                printf("  #######");
                break;
            case 7:
                printf("#########");
                break;
        }
        
        printf ("\n");
    }
}