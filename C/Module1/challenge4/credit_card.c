#include <stdio.h>
#include <cs50.h>

countDigits(digits);

int main(void) {

   long card;

   do {

    card = get_long("Digite os números do cartão de crédito: ");

    if (card <= 0 ) {
        print("Tente novamente!\n");
    }
 
   } while (card <= 0);
  
   int digits = countDigits(card);

}

int countDigits(long digits) {

    int count = 0;

    while (digits != 0 ) {
        digits /= 10;
        count++;
    }

    return count;
}