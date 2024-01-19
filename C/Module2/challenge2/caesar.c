#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char *args[]) {

    char text[1000] = 0;

    if (argc != 2) {

        printf("Usage: ./caesar key\n");
        return 1;
       
    } else {

        for (int i = 0; i < strlen(args[1]); i++) {
            
            if (isdigit(args[1][i]) < 1) {
                
                printf("Usage: ./caesar key\n");
                return 1;

            }
        }
        
        int converted = atoi(args[1]);

        if (converted > 0) {
            
            printf("plaintext: ");
            scanf("%s", text);""
            printf("ciphertext: ");
            cipher(text, converted);
            return 0;

        } else {

            printf("Usage: ./caesar key\n");
            return 1;
        }

    }
    
    void cipher (char *text[], int converted) {
        
        for (int i = 0, length = strlen(text); i < length; i++) {
          
            if (islower(text[i])) {

                printf("%c", (((text[i] - 97) + converted % 26) + 97)); 

            } else if (isupper(s[i])) {
                
                printf("%c", (((text[i] - 65) + converted) % 26) + 65); 

            } else {

                printf("%c", text[i]);

            }
        }
        printf("\n");
    }

}