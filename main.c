/* 
Program Name : BIMP (Bitmap Image Manipulaton Program)
Project type : Group Project
Author(s) : Anand, Anjali, Arun, Aradhna, Alok,Bittu,Divyanshi,Gaurav,
            Nishant,Santosh,Prashant,Vineet
Date : 28/09/2025
Last Modification Date : 29/09/2025
Version : 1.0.0

*/

#include <stdio.h>
#include "tools.h"
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_PATH_LENGTH 256

void file(){
    printf("Enter path of file : ");
    // File will be taken here as input globally so accessed from everywhere

}
void tools(){

    // Validate image loaded or not also first
    int tool_choice;
    do {
        printf("\n==> Entered Tool menu !!\n\n");
        printf("1. Grayscale \n");
        printf("2. Invert color\n");
        printf("3. Gamma_color_change\n");
        printf("4. Sepia\n");
        printf("5. Adjust brightness\n");
        printf("6. Adjust contrast\n");
        printf("7. Color chaneel\n");
        printf("8. Saturation\n");     
        printf("9. Save File\n");
        printf("0. Back to main menu \n");

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
            case 9: save_file("output.bmp");
                    break;
            case 0: 
                printf("\nReturning to Main menu ..... \n");
                return;
        
            default:
                printf("Error !! Enter Valid Choice !!\n");
                break;
        }
    } while ( tool_choice != 0);


}

void about(){
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

int main(){
    int choice;
    printf("\n === Bitmap Image Manipulation Progaram (BIMP) === \n\n");
    do {
      
        
        printf(" <= Main Menu => \n");
        printf("1.Opne_File \n2.Tools \n3.About \n4.Exit \n");
        printf("Enter Your choice : ");
        scanf("%d",&choice);

        switch(choice){
            case 1: load_file(); 
            break;
            case 2: tools();
            break;
            case 3: printf("\n");
            about();
            break;
            case 4: printf("Program Terminated Successfully. Thankyou\n");
            break;
            default : printf("Error !! Please enter valid choice !!\n");
            break;
        } 
    }
    while ( choice != 4 );
     

    return 0;
} 
