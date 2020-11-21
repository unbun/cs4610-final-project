/*
Based of a solution from:
https://stackoverflow.com/questions/421860/capture-characters-from-standard-input-without-waiting-for-enter-to-be-pressed
*/

#include<stdio.h>
#include <stdlib.h>

int main() {
   
    char ch;
    system("stty raw");
    while(1) { 
        ch = getchar();
        // kill on '~'
        if(ch=='~'){
            system("stty cooked");
            exit(0);
        }
        printf("you pressed %c\n ",ch);
    }

}