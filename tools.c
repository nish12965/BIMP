
#include "tools.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>

// Global Definitons

BMPFILEHEADER g_f_header;
BMPINFOHEADER g_i_header;
int g_width; 
int g_height;
uint32_t g_image_size;
unsigned char *g_pixel_data;


//definiton of functionS :-

void grayscale (){
   if (g_pixel_data == NULL) {
        printf("❌ Error: No image loaded.\n");
        return;
    }

    // BMP rows are padded to multiples of 4 bytes
    int row_padded = (g_width * 3 + 3) & ~3;

    for (int y = 0; y < g_height; y++) {
        for (int x = 0; x < g_width; x++) {
            // Access the pixel (3 bytes: B, G, R)
            unsigned char *pixel = g_pixel_data + y * row_padded + x * 3;
           
            unsigned char gray = (pixel[0] + pixel[1] + pixel[2]) / 3;

            // Apply grayscale to all channels
            pixel[0] = gray; // Blue
            pixel[1] = gray; // Green
            pixel[2] = gray; // Red
        }
    }

    printf("✔️ Grayscale effect applied successfully.\n");
}


void inversion (){
    if (g_pixel_data == NULL) {
        printf("Error: No image data loaded!\n");
        return;
    }

    int unpadded_row_size = g_width * 3;
    int padded_row_size = (unpadded_row_size + 3) & ~3;

    for (int y = 0; y < g_height; y++) {
        unsigned char *row = g_pixel_data + (y * padded_row_size);

        for (int x = 0; x < g_width; x++) {
            unsigned char *pixel = row + (x * 3);

            // BMP stores pixels as BGR
            pixel[0] = 255 - pixel[0]; // Blue
            pixel[1] = 255 - pixel[1]; // Green
            pixel[2] = 255 - pixel[2]; // Red
        }
    }

    printf("Color inversion applied.\n");


}

void brightness(){
    int value ;
    printf("Level of brightness :"); // adjust this value
    scanf("%d",&value);
    for (int i = 0; i < g_image_size; i++) {
        int temp = g_pixel_data[i] + value;
        if (temp > 255) temp = 255;
        if (temp < 0) temp = 0;
        g_pixel_data[i] = (unsigned char)temp;
    }
   printf("Brightness Adjusted successfully.\n");
}

void gamma_correction(){
        if (g_pixel_data == NULL) {
        printf("❌ Error: No image loaded.\n");
        return;
    }

    float gamma;
    printf("Enter gamma value (> 0): ");
    if (scanf("%f", &gamma) != 1 || gamma <= 0.0f) {
        printf("❌ Invalid gamma value.\n");
        return;
    }

    int row_padded = (g_width * 3 + 3) & ~3;

    for (int y = 0; y < g_height; y++) {
        for (int x = 0; x < g_width; x++) {
            unsigned char *pixel = g_pixel_data + y * row_padded + x * 3;

            pixel[0] = (unsigned char)(powf(pixel[0] / 255.0f, gamma) * 255.0f); // Blue
            pixel[1] = (unsigned char)(powf(pixel[1] / 255.0f, gamma) * 255.0f); // Green
            pixel[2] = (unsigned char)(powf(pixel[2] / 255.0f, gamma) * 255.0f); // Red
        }
    }

    printf("✔️ Gamma correction applied with gamma = %.2f\n", gamma);
}


void contrast(){
    // Block of code to perform contrast effect on image
}

void sepia(){
    // Block of code to perform sepia effect on image

   if (g_pixel_data == NULL) {
        printf("Error: No image loaded!\n");
        return;
    }

    // Calculate padded row size
    int unpadded_row_size = g_width * 3; // Each pixel in BMP is stored as 3 bytes (B, G, R)

    // BMP rows are padded to multiples of 4 bytes for alignment
    int padded_row_size = (unpadded_row_size + 3) & ~3; 

    // Loop through each row of the image
    for (int y = 0; y < g_height; y++) {
        unsigned char *row = g_pixel_data + y * padded_row_size; // Pointer to the start of the current row
        for (int x = 0; x < g_width; x++) {  // Loop through each pixel in the current row

            // Pointer to the current pixel (3 bytes: Blue, Green, Red)
            unsigned char *pixel = row + x * 3;
            
            // Extract original color values
            unsigned char blue  = pixel[0];
            unsigned char green = pixel[1];
            unsigned char red   = pixel[2];

            // Apply sepia formula
            int newRed   = (int)(0.393 * red + 0.769 * green + 0.189 * blue);
            int newGreen = (int)(0.349 * red + 0.686 * green + 0.168 * blue);
            int newBlue  = (int)(0.272 * red + 0.534 * green + 0.131 * blue);

            // Clamp values to [0,255]
            pixel[2] = (newRed > 255) ? 255 : newRed;
            pixel[1] = (newGreen > 255) ? 255 : newGreen;
            pixel[0] = (newBlue > 255) ? 255 : newBlue;
        }
    }
     // Inform the user that the filter was applied successfully
    printf("[OK] Sepia filter applied.\n");
   
}


void color_channel(){
    // Block of code to perform color_channel effect on image
}

void saturation(){
    if (g_pixel_data == NULL) {
printf("Error: No image loaded.\n");
return;
}

float sat_factor;
printf("Enter saturation factor (>0, 1 = original, >1 = increase, <1 = decrease): ");
if (scanf("%f", &sat_factor) != 1 || sat_factor < 0.0f) {
printf(" Invalid saturation value.\n");
return;
}

int row_padded = (g_width * 3 + 3) & ~3;

for (int y = 0; y < g_height; y++) {
for (int x = 0; x < g_width; x++) {
unsigned char *pixel = g_pixel_data + y * row_padded + x * 3;

float r = pixel[2] / 255.0f; // Red
float g = pixel[1] / 255.0f; // Green
float b = pixel[0] / 255.0f; // Blue

// Convert RGB to HSV
float max = fmaxf(fmaxf(r, g), b);
float min = fminf(fminf(r, g), b);
float delta = max - min;

float h = 0.0f, s = 0.0f, v = max;

if (delta != 0.0f) {
s = delta / max;

if (max == r)
h = 60.0f * fmodf(((g - b) / delta), 6.0f);
else if (max == g)
h = 60.0f * (((b - r) / delta) + 2.0f);
else
h = 60.0f * (((r - g) / delta) + 4.0f);

if (h < 0) h += 360.0f;
}

// Modify saturation
s *= sat_factor;
if (s > 1.0f) s = 1.0f;

// Convert HSV back to RGB
float c = v * s;
float x1 = c * (1 - fabsf(fmodf(h / 60.0f, 2) - 1));
float m = v - c;

float r1, g1, b1;

if (h < 60) { r1 = c; g1 = x1; b1 = 0; }
else if (h < 120) { r1 = x1; g1 = c; b1 = 0; }
else if (h < 180) { r1 = 0; g1 = c; b1 = x1; }
else if (h < 240) { r1 = 0; g1 = x1; b1 = c; }
else if (h < 300) { r1 = x1; g1 = 0; b1 = c; }
else { r1 = c; g1 = 0; b1 = x1; }

pixel[2] = (unsigned char)((r1 + m) * 255.0f);
pixel[1] = (unsigned char)((g1 + m) * 255.0f);
pixel[0] = (unsigned char)((b1 + m) * 255.0f);
}
}

printf("Saturation adjusted by factor %.2f\n", sat_factor);

}


void load_file(){
    char path[256];
    printf("Enter path of bmp file : ");
    if (scanf ("%255s",path) != 1){
        return;
    }

    FILE *fp = fopen(path,"rb");
    if (fp == NULL){
        printf("Error !! File not loaded");
        return;
    }

    if (fread(&g_f_header,sizeof(BMPFILEHEADER),1,fp) != 1 || 
        fread(&g_i_header,sizeof(BMPINFOHEADER),1,fp) != 1 ){
            printf("Error in reading file header !!");
            fclose(fp);
            return;
    }  

    if (g_f_header.bfType != 0X4d42 || g_i_header.biBitCount != 24 || g_i_header.biCompression != 0){
        printf("Only 24 bit uncmpressed BMP file is supported");
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
    if (g_pixel_data != NULL){
        free(g_pixel_data);
    }

    g_pixel_data = (unsigned char *)malloc(g_image_size);
    if (g_pixel_data == NULL){
        printf("Memory Allocation Failed !!");
        fclose(fp);
        return;
    }

    //
    fseek(fp,g_f_header.bfOffBits,SEEK_SET);
    if(fread(g_pixel_data,1,g_image_size, fp) != g_image_size) {
        printf("Error in reading pixel data !!\n");
        free(g_pixel_data);
        g_pixel_data = NULL;
        fclose(fp);
        return;
    }

    fclose(fp);
    printf("File has been loaded ✔️\n");
    printf("Pixels  : %d * %d\n",g_width,g_height);
    printf("👉 Visit tools section for operatin ");
}


void save_file(const char *output_path) {
    if (g_pixel_data == NULL) {
        printf("Error: No image data to save.\n");
        return;
    }

    FILE *fp = fopen(output_path, "wb");
    if (fp == NULL) {
        perror("Error creating output file");
        return;
    }
    // writing file header
    fwrite(&g_f_header, sizeof(BMPFILEHEADER), 1, fp);
    
    //Writing info header
    fwrite(&g_i_header, sizeof(BMPINFOHEADER), 1, fp);
    
    // writing pixel data
    fseek(fp, g_f_header.bfOffBits, SEEK_SET);
    fwrite(g_pixel_data, 1, g_image_size, fp);

    fclose(fp);
    printf("Image saved : %s\n", output_path);
}






 



