
#include "tools.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>


// Global Definitons

BMPFILEHEADER g_f_header;
BMPINFOHEADER g_i_header;
int g_width; 
int g_height;
uint32_t g_image_size;
unsigned char *g_pixel_data;


//definiton of functionS :-

void grayscale (){
   // Block of code to perform grayscale effect on image 
}



void inversion (){
    // Block of code to perfrom inversion effect on image
}

void brightness(){
    // Block of code to perform brightness effect on image
}

void gamma_correction(){
    // Block of code to perform gamma_correction effect on image
}

void contrast(){
    // Block of code to perform contrast effect on image
}

void sepia(){
    // Block of code to perform sepia effect on image
}


void color_channel(){
    // Block of code to perform color_channel effect on image
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






 



