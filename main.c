/* 
Program Name : BIMP (Bitmap Image Manipulaton Program)
Project type : Group Project
Author(s) : Anand, Anjali, Arun, Aradhna, Alok,Bittu,Divyanshi,Gaurav,
            Nishant,Santosh,Prashant,Vineet
Date : 28/05/2025
Version : 1.0.0

*/

#include <stdio.h>
//#include "tools.h"
#include <stdlib.h>

int main(){
    int choice;
    printf(" === Bitmap Image Manipulation Progaram (BIMP) === \n\n");
    printf(" <= Main Menu => \n");
    printf("1.File \n2.Tools \n3.About \n4.Exit \n");
    printf("Enter Your choice : ");
    scanf("%d",&choice);

    switch(choice){
        case 1: // Accessing file menu
                //break;
        case 2: //Accessing tools menu
                //break;
        case 3: {
            FILE *file = fopen("about.md","r");
            if (file == NULL){
                printf("Error: File not opening\n");
            }
            else{
                char line[1024];
                while(fgets(line,sizeof(line),file) != NULL){
                    printf("%s",line);
                }
            }
            fclose(file);
        }
        break;
        case 4: printf("Program Terminated Successfully. Thankyou\n");
        break;
        default : printf("Error !! Please enter valid choice !!\n");
    }
    return 0;
}