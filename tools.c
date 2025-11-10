
#include "tools.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>
#include <time.h>

// Global Definitons

BMPFILEHEADER g_f_header;
BMPINFOHEADER g_i_header;
int g_width;
int g_height;
uint32_t g_image_size;
unsigned char *g_pixel_data;

// definiton of functionS :-

void grayscale() {
     // Check if image data exists before proceeding
    if (g_pixel_data == NULL) {
        printf("\x1b[31mError: No image loaded.\x1b[0m\n");
        return;
    }

    // BMP rows are padded to multiples of 4 bytes
    int row_padded = (g_width * 3 + 3) & ~3;
    
    // Loop through every pixel in the image (by row and column)
    for (int y = 0; y < g_height; y++)
    {
        for (int x = 0; x < g_width; x++)
        {
            // Access the pixel (3 bytes: B, G, R)
            unsigned char *pixel = g_pixel_data + y * row_padded + x * 3;
            
             // Convert to grayscale using a weighted average
            unsigned char gray = (pixel[0] + pixel[1] + pixel[2]) / 3;

            // Apply grayscale to all channels
            pixel[0] = gray; // Blue
            pixel[1] = gray; // Green
            pixel[2] = gray; // Red
        }
    }

    printf("✔️ Grayscale effect applied successfully.\n");
    save_file();
}

//Function to invert colours of the loaded image
void inversion() {
    if (g_pixel_data == NULL) {
        printf("\x1b[31mError: No image loaded.\x1b[0m\n");
        return;
    }
  
    //Calculate the size of each row(without padding)
    int unpadded_row_size = g_width * 3; //3 bytes per pixel(B,G,R)

    //Calculate the size of each row including padding(BMP rows are padded to multiples of 4 bytes)
    int padded_row_size = (unpadded_row_size + 3) & ~3;

    //Loop through each row of the image
    for (int y = 0; y < g_height; y++)
    {
         // Pointer to the start of the current row
        unsigned char *row = g_pixel_data + (y * padded_row_size);

        // Loop through each pixel in the row
        for (int x = 0; x < g_width; x++)
        {
            // Pointer to the current pixel (3 bytes: Blue, Green, Red)
            unsigned char *pixel = row + (x * 3);

             // Invert each color channel
            // BMP stores pixels in BGR format
            pixel[0] = 255 - pixel[0]; //Invert Blue
            pixel[1] = 255 - pixel[1]; //Invert Green
            pixel[2] = 255 - pixel[2]; //Invert Red
        }
    }

    printf("✔️ Color inversion applied Successfully.\n");
    save_file();
}

void brightness() {
    if (g_pixel_data == NULL) {
        printf("\x1b[31mError: No image loaded.\x1b[0m\n");
        return;
    }
    int value;
    printf("Level of brightness ( -100 to 100 ) :"); // adjust this value
    scanf("%d", &value);
    for (int i = 0; i < g_image_size; i++) {
        int temp = g_pixel_data[i] + value;
        if (temp > 255)
            temp = 255;
        if (temp < 0)
            temp = 0;
        g_pixel_data[i] = (unsigned char)temp;
    }
    printf("✔️ Brightness Adjusted successfully.\n");
    save_file();
}

void gamma_correction() {
    if (g_pixel_data == NULL) {
        printf("\x1b[31mError: No image loaded.\x1b[0m\n");
        return;
    }
    float gamma;
    printf("Enter gamma value (> 0): ");
    if (scanf("%f", &gamma) != 1 || gamma <= 0.0f)
    {
        printf("Invalid gamma value.\n");
        return;
    }

    int row_padded = (g_width * 3 + 3) & ~3;

    for (int y = 0; y < g_height; y++)
    {
        for (int x = 0; x < g_width; x++)
        {
            unsigned char *pixel = g_pixel_data + y * row_padded + x * 3;

            pixel[0] = (unsigned char)(powf(pixel[0] / 255.0f, gamma) * 255.0f); // Blue
            pixel[1] = (unsigned char)(powf(pixel[1] / 255.0f, gamma) * 255.0f); // Green
            pixel[2] = (unsigned char)(powf(pixel[2] / 255.0f, gamma) * 255.0f); // Red
        }
    }

    printf("✔️ Gamma correction applied with gamma = %.2f\n", gamma);
    save_file();
}

void contrast() {
    if (g_pixel_data == NULL) {
        printf("Error: No image loaded.\n");
        return;
    }
    float contrast_value;
    printf("Enter contrast level (-100 to 100): ");
    if (scanf("%f", &contrast_value) != 1 || contrast_value < -100.0f || contrast_value > 100.0f) {
        printf("Invalid contrast value. Please enter between -100 and 100.\n");
        return;
    }

    // Calculate contrast factor
    // Formula: factor = (259 * (contrast + 255)) / (255 * (259 - contrast))
    float factor = (259.0f * (contrast_value + 255.0f)) / (255.0f * (259.0f - contrast_value));

    // BMP row padding to multiple of 4 bytes
    int row_padded = (g_width * 3 + 3) & ~3;

    // Loop through all pixels (B, G, R order)
    for (int y = 0; y < g_height; y++)
    {
        for (int x = 0; x < g_width; x++)
        {
            unsigned char *pixel = g_pixel_data + y * row_padded + x * 3;

            for (int c = 0; c < 3; c++)
            {
                // Apply contrast adjustment
                float val = (float)pixel[c];
                val = factor * (val - 128.0f) + 128.0f;

                // Clamp between 0 and 255
                if (val < 0.0f)
                    val = 0.0f;
                if (val > 255.0f)
                    val = 255.0f;

                pixel[c] = (unsigned char)val;
            }
        }
    }

    printf("✔️ Contrast adjusted successfully (%.2f)\n", contrast_value);
    save_file();
}

void sepia() {
    if (g_pixel_data == NULL) {
        printf("\x1b[31mError: No image loaded.\x1b[0m\n");
        return;
    }

    // Calculate padded row size
    int unpadded_row_size = g_width * 3; // Each pixel in BMP is stored as 3 bytes (B, G, R)

    // BMP rows are padded to multiples of 4 bytes for alignment
    int padded_row_size = (unpadded_row_size + 3) & ~3;

    // Loop through each row of the image
    for (int y = 0; y < g_height; y++)
    {
        unsigned char *row = g_pixel_data + y * padded_row_size; // Pointer to the start of the current row
        for (int x = 0; x < g_width; x++)
        { // Loop through each pixel in the current row

            // Pointer to the current pixel (3 bytes: Blue, Green, Red)
            unsigned char *pixel = row + x * 3;

            // Extract original color values
            unsigned char blue = pixel[0];
            unsigned char green = pixel[1];
            unsigned char red = pixel[2];

            // Apply sepia formula
            int newRed = (int)(0.393 * red + 0.769 * green + 0.189 * blue);
            int newGreen = (int)(0.349 * red + 0.686 * green + 0.168 * blue);
            int newBlue = (int)(0.272 * red + 0.534 * green + 0.131 * blue);

            // Clamp values to [0,255]
            pixel[2] = (newRed > 255) ? 255 : newRed;
            pixel[1] = (newGreen > 255) ? 255 : newGreen;
            pixel[0] = (newBlue > 255) ? 255 : newBlue;
        }
    }
    // Inform the user that the filter was applied successfully
    printf("Sepia filter applied.\n");
    save_file();
}

void color_channel() {
    if (g_pixel_data == NULL) {
        printf("\x1b[31mError: No image loaded.\x1b[0m\n");
        return;
    }

    int choice;
    printf("Select color channel to keep:\n");
    printf("1. Red\n2. Green\n3. Blue\n");
    printf("Enter your choice (1-3): ");
    if (scanf("%d", &choice) != 1)
    {
        printf("Invalid input.\n");
        return;
    }

    // Handle BMP row padding (rows are aligned to 4-byte boundaries)
    int row_padded = (g_width * 3 + 3) & ~3;

    for (int y = 0; y < g_height; y++)
    {
        for (int x = 0; x < g_width; x++)
        {
            unsigned char *pixel = g_pixel_data + y * row_padded + x * 3;
            unsigned char *blue = &pixel[0];
            unsigned char *green = &pixel[1];
            unsigned char *red = &pixel[2];

            switch (choice)
            {
            case 1: // Keep Red only
                *blue = 0;
                *green = 0;
                break;
            case 2: // Keep Green only
                *blue = 0;
                *red = 0;
                break;
            case 3: // Keep Blue only
                *green = 0;
                *red = 0;
                break;
            default:
                printf("Invalid choice! No change applied.\n");
                return;
            }
        }
    }

    printf("✔️ Color channel filter applied successfully.\n");
    save_file();
}

void saturation() {
     // Check if any image data is loaded before processing
    if (g_pixel_data == NULL) {
        printf("\x1b[31mError: No image loaded.\x1b[0m\n");
        return;
    }

    float sat_factor;  // user-defined factor to increase or decrease saturation
     // Ask user to input a saturation factor
    printf("Enter saturation factor (>0, 1 = original, >1 = increase, <1 = decrease): ");
    if (scanf("%f", &sat_factor) != 1 || sat_factor < 0.0f)
    {
        printf(" Invalid saturation value.\n");
        return;
    }
    
       // Each BMP row is padded to a multiple of 4 bytes
    int row_padded = (g_width * 3 + 3) & ~3;
 
        // Loop through all pixels (row by row)
    for (int y = 0; y < g_height; y++)
    {
        for (int x = 0; x < g_width; x++)
        {
               // Pointer to the start of this pixel (3 bytes: B, G, R)
            unsigned char *pixel = g_pixel_data + y * row_padded + x * 3;


            // Extract RGB values and normalize them to [0, 1] range
            float r = pixel[2] / 255.0f; // Red
            float g = pixel[1] / 255.0f; // Green
            float b = pixel[0] / 255.0f; // Blue

            // Convert RGB to HSV
            float max = fmaxf(fmaxf(r, g), b);
            float min = fminf(fminf(r, g), b);
            float delta = max - min;

            float h = 0.0f, s = 0.0f, v = max;

            if (delta != 0.0f)// if the color is not grayscale
            {
                s = delta / max; // compute saturation (relative color strength)

                // compute hue based on which color is the maximum
                if (max == r)
                    h = 60.0f * fmodf(((g - b) / delta), 6.0f);
                else if (max == g)
                    h = 60.0f * (((b - r) / delta) + 2.0f);
                else
                    h = 60.0f * (((r - g) / delta) + 4.0f);

                if (h < 0)
                    h += 360.0f;
            }

            // Modify saturation
            s *= sat_factor;
            if (s > 1.0f)
                s = 1.0f;

            // Convert HSV back to RGB
            float c = v * s;
            float x1 = c * (1 - fabsf(fmodf(h / 60.0f, 2) - 1));
            float m = v - c;

            float r1, g1, b1;

            if (h < 60)
            {
                r1 = c;
                g1 = x1;
                b1 = 0;
            }
            else if (h < 120)
            {
                r1 = x1;
                g1 = c;
                b1 = 0;
            }
            else if (h < 180)
            {
                r1 = 0;
                g1 = c;
                b1 = x1;
            }
            else if (h < 240)
            {
                r1 = 0;
                g1 = x1;
                b1 = c;
            }
            else if (h < 300)
            {
                r1 = x1;
                g1 = 0;
                b1 = c;
            }
            else
            {
                r1 = c;
                g1 = 0;
                b1 = x1;
            }

            pixel[2] = (unsigned char)((r1 + m) * 255.0f);
            pixel[1] = (unsigned char)((g1 + m) * 255.0f);
            pixel[0] = (unsigned char)((b1 + m) * 255.0f);
        }
    }

    printf("✔️ Saturation adjusted by factor %.2f\n", sat_factor);
    save_file();
}

void open_file() {
    char path[256];
    printf("Enter path of bmp file ( 255 char long ): ");
    if (scanf("%255s", path) != 1)
    {
        return;
    }

    FILE *fp = fopen(path, "rb");
    if (fp == NULL)
    {
        printf("\x1b[31mError !! File not loaded\x1b[0m\n");
        return;
    }

    if (fread(&g_f_header, sizeof(BMPFILEHEADER), 1, fp) != 1 ||
        fread(&g_i_header, sizeof(BMPINFOHEADER), 1, fp) != 1)
    {
        printf("\x1b[31mError in reading file header !!\x1b[0m\n");
        fclose(fp);
        return;
    }

    if (g_f_header.bfType != 0X4d42 || g_i_header.biBitCount != 24 || g_i_header.biCompression != 0)
    {
        printf("\x1b[31mOnly 24 bit uncmpressed BMP file is supported\x1b[0m\n");
        fclose(fp);
        return;
    }

    // Calculating image size
    g_width = g_i_header.biWidth;
    g_height = g_i_header.biHeight;
    int unpadded_row_size = g_width * 3;
    int padded_row_size = (unpadded_row_size + 3) & ~3;
    g_image_size = (uint32_t)(padded_row_size * g_height);

    // Allocating memory
    if (g_pixel_data != NULL)
    {
        free(g_pixel_data);
    }

    g_pixel_data = (unsigned char *)malloc(g_image_size);
    if (g_pixel_data == NULL)
    {
        printf("\x1b[31mMemory Allocation Failed !!\x1b[0m\n");
        fclose(fp);
        return;
    }

    
    fseek(fp, g_f_header.bfOffBits, SEEK_SET);
    if (fread(g_pixel_data, 1, g_image_size, fp) != g_image_size)
    {
        printf("Error in reading pixel data !!\n");
        free(g_pixel_data);
        g_pixel_data = NULL;
        fclose(fp);
        return;
    }

    fclose(fp);
    printf("\n\x1b[34mFile has been loaded ✔️\x1b[0m\n");
    printf("\n\x1b[36mPixels  : %d * %d\x1b[0m\n", g_width, g_height);
    printf("\n\x1b[32m👉 Visit tools section to perform operation.\x1b[0m \n");
}

void save_file() {
    if (g_pixel_data == NULL)
    {
        printf("\x1b[31mError: No image data to save.\x1b[0m\n");
        return;
    }
    char output_path[256];
    //Clearing  leftover newline from previous scanf
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
    printf("Enter output file path (Max 255 char long with .bmp or Just Press Enter for Autosave): ");
      fgets(output_path, sizeof(output_path), stdin);

    // remove newline if present
    output_path[strcspn(output_path, "\n")] = '\0';

    // check if user left empty OR forgot .bmp
    if (strlen(output_path) == 0 || strstr(output_path, ".bmp") == NULL) {

        time_t now = time(NULL);
        struct tm *t = localtime(&now);

        snprintf(output_path, sizeof(output_path),
                 "output_%04d%02d%02d_%02d%02d%02d.bmp",
                 t->tm_year + 1900,
                 t->tm_mon + 1,
                 t->tm_mday,
                 t->tm_hour,
                 t->tm_min,
                 t->tm_sec);

        printf("Auto filename used: %s\n", output_path);
    }

    FILE *fp = fopen(output_path, "wb");
    if (fp == NULL)
    {
        perror("\x1b[31mError opening  output file.\x1b[0m\n");
        return;
    }
    // writing file header
    fwrite(&g_f_header, sizeof(BMPFILEHEADER), 1, fp);

    // Writing info header
    fwrite(&g_i_header, sizeof(BMPINFOHEADER), 1, fp);

    // writing pixel data
    fseek(fp, g_f_header.bfOffBits, SEEK_SET);
    fwrite(g_pixel_data, 1, g_image_size, fp);

    fclose(fp);
    printf("Image saved : %s\n", output_path);
}
