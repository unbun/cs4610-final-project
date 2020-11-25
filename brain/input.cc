/*
Based of a solution from:
https://stackoverflow.com/questions/421860/capture-characters-from-standard-input-without-waiting-for-enter-to-be-pressed
*/

#include <stdio.h>
#include <stdlib.h>


int main() {
   
    char ch;
    system("stty raw");
    int i = 0;
    while(i < 100) {

        system("stty raw");
        printf("input-> ");

        ch = getchar();

        if(ch=='~') {         // kill on '~'
            system("stty cooked");
            exit(0);
        }

        system("stty cooked");
        printf("\nyou pressed %c\n",ch);
        i++;
    }


    system("stty cooked"); 
    exit(0);

}