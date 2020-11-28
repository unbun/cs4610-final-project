
/**
Test file displaying the general concept of reading keyboard input
from the terminal
**/
#include <stdio.h>
#include <stdlib.h>


int input_loop() {
   
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