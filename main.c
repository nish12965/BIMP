


/* 
Program Name : BIMP (Bitmap Image Manipulation Program)
Project type : Group Project
Author(s) : Anand, Anjali, Arun, Aradhna, Alok, Bittu, Divyanshi, Gaurav,
            Nishant, Santosh, Prashant, Vineet
Date : 28/09/2025
Last Modification Date : 02/10/2025 19:30
Version : 1.0.0

Description:
------------
This program is like a small photo editor for BMP images.
It allows the user to:
 - Open a BMP file
 - Apply different effects (grayscale, invert colors, sepia, brightness, etc.)
 - Save the modified file as a new picture
 - Read project details from "about.md"
The program works through a simple text menu.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "tools.h"  /* Contains functions for editing the BMP image */

/* 
Maximum length allowed for file path strings
--------------------------------------------
We often need to store the full path of a file (like "C:\Images\pic.bmp") in a variable.
This macro defines the maximum number of characters we can store for a file path.
Using a macro instead of a raw number (like 256) makes the code easier to read and maintain.
If we ever want to allow longer file paths, we just change this value here once.
*/
#define MAX_PATH_LENGTH 256

/* 
file()
-------
This function is just a placeholder.
It was meant to ask the user for a file name,
but right now the real file loading happens in load_file() (tools.c).
*/
void file(){
    printf("Enter path of file : ");
}

/* 
tools()
-------
This function shows the "Tools Menu" where the user can apply
different effects on the loaded picture.

The user can keep applying effects until they choose 0 (to return back).
Each option calls a function defined in tools.c that actually
changes the pixels of the image.
*/
void tools(){
    int tool_choice;
    do {
        /* Show available editing options */
        printf("\n==> Entered Tool menu !!\n\n");
        printf("1. Grayscale (black & white)\n");
        printf("2. Invert color\n");
        printf("3. Gamma color change\n");
        printf("4. Sepia look\n");
        printf("5. Make brighter\n");
        printf("6. Change contrast\n");
        printf("7. Change color channel\n");
        printf("8. Change saturation\n");     
        printf("9. Save File\n");
        printf("0. Back to main menu \n");

        /* Ask the user what they want to do */
        printf("Enter Your choice : ");
        scanf("%d",&tool_choice);

        /* Call the function that matches the user's choice */
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
            case 9: save_file("output.bmp"); /* Save the edited image */
                    break;
            case 0: 
                /* Go back to the main menu */
                printf("\nReturning to Main menu ..... \n");
                return;
            default:
                /* If user enters an invalid number */
                printf("Error !! Enter Valid Choice !!\n");
                break;
        }
    } while ( tool_choice != 0); /* keep running until user chooses 0 */
}

/* 
about()
-------
This function shows information about the project.
It opens a file named "about.md" and prints everything
written inside it line by line.

If the file does not exist or cannot be opened,
it shows an error message.
*/
void about(){
    FILE *file = fopen("about.md","r");
    if (file == NULL){
        printf("Error: File not opening\n");
    }
    else{
        char line[1024];
        /* Print each line from the file until it ends */
        while(fgets(line,sizeof(line),file) != NULL){
            printf("%s",line);
        }
    }
    fclose(file);
}

/* 
main()
-------
This is where the program starts running.
It shows the main menu and lets the user choose:
  1 → Open a BMP picture file
  2 → Go to the tools menu (apply effects)
  3 → Read about the project
  4 → Exit the program

The menu keeps showing again and again until the user chooses Exit.
*/
int main(){
    int choice;
    printf("\n === Bitmap Image Manipulation Program (BIMP) === \n\n");

    do {
        /* Show the main menu */
        printf(" <= Main Menu => \n");
        printf("1. Open File \n");
        printf("2. Tools \n");
        printf("3. About \n");
        printf("4. Exit \n");
        printf("Enter Your choice : ");
        scanf("%d",&choice);

        /* Run the option the user picked */
        switch(choice){
            case 1: 
                /* 
                 load_file();
                 ------------
                 When this function is called, the following happens:
                 - The user is asked to type the name/path of a BMP file
                 - The program tries to open the file in binary mode
                 - It checks if the file is a valid 24-bit uncompressed BMP
                 - It reads the image width, height, and other details
                 - It loads all the pixel data into memory
                 - It shows a message that the file was successfully loaded

                 In short:
                 This step is like “opening a picture” so that
                 later we can apply filters or effects on it.
                */
                load_file();        
                break;

            case 2: 
                tools(); /* Show tools menu for editing the loaded picture */
                break;

            case 3: 
                printf("\n");  /* Print project details */
                about();
                break;

            case 4: 
                printf("Program Terminated Successfully. Thank you\n");
                break;

            default: 
                printf("Error !! Please enter valid choice !!\n");
                break;
        } 
    }
    while ( choice != 4); /* Repeat until user chooses Exit */

    return 0;
}
