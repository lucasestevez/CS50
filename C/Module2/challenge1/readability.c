#include <stdio.h>
#include <string.h>
#include <math.h>

int main(void) {

    char text[1000];
    printf("Digite o texto: ");
    scanf("%s", text);

    for (int i = 0, letters = 0, space = 0, textLength = strlen(text) , phrases = 0; i < textLength; i++) {

        if ((text[i] >= 'a' && text[i] <= 'z' ) || (text[i] >= 'A' && text[i] <= 'Z')) {

            letters++;
           
        } else if (text[i] == ' ') {
            
            space++;

        } else if (text[i] == '?' || text[i] == '!' || text[i] == '.') {
           
            phrases++;

        }
        
        if (i == textLength - 1) {

            float l = (float) letters * 100 / (space + 1);
            float s = (float) phrases * 100 / (space + 1);
            float grade = 0.0588 * l - 0.296 * s - 15.8;

            if (grade > 16){

                printf("Grade 16+ \n");

            } else if (grade < 1) {

                printf("Grade over 1 \n");

            } else {

                printf("Garde %i \n", round(grade));

            }
        }  
    }
}




