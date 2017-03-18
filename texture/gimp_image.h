typedef struct {
    unsigned int width;
    unsigned int height;
    unsigned int bytes_per_pixel;
    unsigned char pixel_data[300*300*3+1];
} gimp_image;
