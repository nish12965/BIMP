/* 
Program Name : BIMP (Bitmap Image Manipulaton Program)
Project type : Group Project
Author(s) : Anand, Anjali, Arun, Aradhna, Alok,Bittu,Divyanshi,Gaurav,
            Nishant,Prashant,Vineet
Date : 28/09/2025
Last Modification Date : 09/11/2025
Version : 1.0.0

*/

#include <stdio.h>
#include "tools.h"
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_PATH_LENGTH 256

void tools(){

    int tool_choice;
    do {
        printf("\n\x1b[32m==> Entered Tool menu !!\x1b[0m\n\n");
        printf("\x1b[32m1. Grayscale \n");
        printf("2. Invert color\n");
        printf("3. Gamma_color_change\n");
        printf("4. Sepia\n");
        printf("5. Adjust brightness\n");
        printf("6. Adjust contrast\n");
        printf("7. Color channel\n");
        printf("8. Saturation\n");     
        printf("0. Back to main menu \x1b[0m\n");

        printf("Enter Your choice : ");
        scanf("%d",&tool_choice);

        switch (tool_choice){
            case 1: grayscale();
                    break;
            case 2: inversion();
                    break;
            case 3: gamma_correction();
                    break;
            case 4: sepia();
                    break;
            case 5: brightness();
                    break;
            case 6: contrast();
                    break;
            case 7: color_channel();
                    break;
            case 8: saturation();
                    break;
            case 0: 
                printf("\nReturning to Main menu ... \n");
                return;
        
            default:
                printf("\x1b[1;31mError !! Enter Valid Choice !!\x1b[0m\n");
                break;
        }
    } while ( tool_choice != 0);


}

void about(){
    FILE *file = fopen("about.md","r");
            if (file == NULL){
                printf("\x1b[31Error: File not opening\n\x1b[0m");
            }
            else{
                char line[1024];
                while(fgets(line,sizeof(line),file) != NULL){
                    printf("%s",line);
                }
            }
            fclose(file);
}

int main(){
    int choice;
    printf("\n\x1b[1;33m=== 🖼️  Bitmap Image Manipulation Progaram (BIMP) ===\x1b[0m\n\n");
    do {
      
        
        printf(" \x1b[1;35m<= Main Menu => \n");
        printf("1.Open_File \n2.Tools \n3.About \n4.Exit \n");
        printf("Enter Your choice (1-4) : \x1b[0m");
        scanf("%d",&choice);

        switch(choice){
            case 1: open_file(); 
            break;
            case 2: tools();
            break;
            case 3: printf("\n");
            about();
            break;
            case 4: printf("\x1b[32mProgram Terminated Successfully. Thankyou\x1b[0m\n");
            break;
            default : printf("\x1b[31Error !! Please enter valid choice !!\x1b[0\n");
            break;
        } 
    }
    while ( choice != 4 );
     

    return 0;
} 
