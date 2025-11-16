// Header guard

#ifndef TOOLS_H // if TOOLS_H not defined
#define TOOLS_H // definign TOOLS_H header
#include <stdint.h>

// Bitmap File Header 14 bytes long

// saving struct alligment of bmp image as it so used pragma 
#pragma pack(push,1)
typedef struct {
    uint16_t bfType;
    uint32_t bfSize;
    uint16_t bfReserved1;
    uint16_t bfReserved2;
    uint32_t bfOffBits;
} BMPFILEHEADER;

typedef struct {
    uint32_t biSize;
    uint32_t biWidth;
    uint32_t biHeight;
    uint16_t biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression;
    uint32_t biSizeImage;
    int32_t  biXPelsPerMeter;
    int32_t  biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t biClrImportant;
} BMPINFOHEADER;
#pragma pack(pop)

extern BMPFILEHEADER g_f_header;
extern BMPINFOHEADER g_i_header;
extern int g_width;
extern int g_height;
extern uint32_t g_image_size;
extern unsigned char *g_pixel_data;


//Prototype of color inverson function
void grayscale(); 

// Prototype of grayscale function
void inversion();

//Prototype of brightness function
void brightness();

//Prototype of gamma_correction function
void gamma_correction();

//Prototype of contrast function
void contrast();

// Prototype of sepia filter function
void sepia();

//Prototype of color channel filter function
void color_channel();

//Prototype of saturation function
void saturation();

// File loading
void open_file();

// File Saving
void save_file();

//Image stats count
void image_stats();

#endif // End of header guard
