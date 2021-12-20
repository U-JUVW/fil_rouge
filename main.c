#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "ex1.h"
#include "ex2.h"

int main(int argc, char const *argv[])
{
    int prog;
    if(argc < 3){
        printf("Missing arguments\n\targ1 : Program to be executed (1 to 3)\n\targ2 : Path to the file to be read\n\targ3 : Number of words to be read (not required for programs 2 and 3)\nEnd of program\n");
        return 1;
    }

    prog = atoi(argv[1]);
    switch(prog){
        case 1 :
            if(argc == 3){
                printf("Missing arguments\n\targ1 : Program to be executed (1 to 3)\n\targ2 : Path to the file to be read\n\targ3 : Number of words to be read (not required for programs 2 and 3)\nEnd of program\n");
                break;
            }
            program1(strdup(argv[2]), atoi(argv[3]));
            break;
        case 2:
            if(argc == 3){
                program2(strdup(argv[2]), 0);
                break;
            }
            program2(strdup(argv[2]), atoi(argv[3]));
            break;
        case 3:
            printf("Pas de programme 3 pour l'instant ! \n");
            break;
        default:
            if(argc == 3){
                printf("Missing arguments\n\targ1 : Program to be executed (1 to 3)\n\targ2 : Path to the file to be read\n\targ3 : Number of words to be read (not required for programs 2 and 3)\nEnd of program\n");
                break;
            }
            program1(strdup(argv[2]), atoi(argv[3]));
    }

    return 0;
}