/*
Program Name : BIMP (Bitmap Image Manipulation Program)
Project type : Group Project
Author(s) : Anand, Anjali, Arun, Aradhna, Alok, Bittu, Divyanshi, Gaurav,
            Nishant, Santosh, Prashant, Vineet
Last Modification Date : 03/10/2025
Version : 1.0.1

Description:
------------
This program is a small photo editor for BMP images.
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
#include <sys/stat.h>
#include <sys/types.h>
#ifdef _WIN32
#include <direct.h> // for _mkdir on Windows
#endif
#include "tools.h" /* Contains functions for editing the BMP image */

#define MAX_PATH_LENGTH 256

/* Predefined input and output directories */
#define INPUT_DIR "C:\\Users\\NITRO\\OneDrive\\Desktop\\BIMP\\input"
#define OUTPUT_DIR "C:\\Users\\NITRO\\OneDrive\\Desktop\\BIMP\\output"

/* Tools menu for editing image */
void tools()
{
    int tool_choice;
    do
    {
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

        printf("Enter Your choice : ");
        scanf("%d", &tool_choice);

        switch (tool_choice)
        {
        case 1:
            grayscale();
            break;
        case 2:
            inversion();
            break;
        case 3:
            gamma_correction();
            break;
        case 4:
            sepia();
            break;
        case 5:
            brightness();
            break;
        case 6:
            contrast();
            break;
        case 7:
            color_channel();
            break;
        case 8:
            saturation();
            break;
        case 9:
        {
            char filename[MAX_PATH_LENGTH];
            printf("Enter output file name (e.g. result.bmp): ");
            scanf("%s", filename);

/* Ensure output directory exists */
#ifdef _WIN32
            _mkdir(OUTPUT_DIR);
#else
            mkdir("output", 0777);
#endif

            char fullpath[MAX_PATH_LENGTH];
            snprintf(fullpath, sizeof(fullpath), "%s\\%s", OUTPUT_DIR, filename);

            save_file(fullpath);
        }
        break;
        case 0:
            printf("\nReturning to Main menu ..... \n");
            return;
        default:
            printf("Error !! Enter Valid Choice !!\n");
            break;
        }
    } while (tool_choice != 0);
}

/* About function */
void about()
{
    FILE *file = fopen("about.md", "r");
    if (file == NULL)
    {
        printf("Error: File not opening\n");
    }
    else
    {
        char line[1024];
        while (fgets(line, sizeof(line), file) != NULL)
        {
            printf("%s", line);
        }
        fclose(file);
    }
}

/* Main function */
int main()
{
    int choice;

    printf("\n === Bitmap Image Manipulation Program (BIMP) === \n\n");

    do
    {
        printf(" <= Main Menu => \n");
        printf("1. Open File \n");
        printf("2. Tools \n");
        printf("3. About \n");
        printf("4. Exit \n");
        printf("Enter Your choice : ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
        {
            char filename[MAX_PATH_LENGTH];
            printf("Enter input BMP file name (from input folder, e.g., pic.bmp): ");
            scanf("%s", filename);

            char fullpath[MAX_PATH_LENGTH];
            snprintf(fullpath, sizeof(fullpath), "%s\\%s", INPUT_DIR, filename);

            load_file(fullpath); /* Load image using the full path directly */
        }
        break;

        case 2:
            tools();
            break;

        case 3:
            printf("\n");
            about();
            break;

        case 4:
            printf("Program Terminated Successfully. Thank you\n");
            break;

        default:
            printf("Error !! Please enter valid choice !!\n");
            break;
        }
    } while (choice != 4);

    return 0;
}