#include <stdio.h>
#include "gaussian_blur.h"
#include "time.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"

typedef struct timespec Time

int main(int argc, char * argv[]) {
    char *input, *output;
    Time t, t1, t2;
    if(argc != 3){
        printf("Usage: %s [input] [output]\n", argv[0]);
        printf("\n");
        printf("- input : extension must be [.bmp].\n");
        printf("- output: extension must be [.bmp].\n");
        exit(1);
    } else {
        input = argv[1]; output = argv[2];
        int f1 = strcmp(input+strlen(input)-5, ".bmp");
        int f2 = strcmp(output+strlen(output)-5, ".bmp");
        if(f1 != 0 || f2 != 0){
            printf("Usage: %s [input] [output]\n", argv[0]);
            printf("\n");
            printf("- input : extension must be [.bmp].\n");
            printf("- output: extension must be [.bmp].\n");
            exit(1);
        }
    }

    int width, height, channels;
    unsigned char *img1 = stbi_load(input, &width, &height, &channels, 0);
    if(img1 == NULL) {
        printf("ERROR: Input file doesn't exist!\n");
        exit(1);
    }
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &t1);
    gaussian_blur(&img1, width, height, channels);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &t2);
    t.tv_sec = t2.tv_sec-t1.tv_sec;
    if((t.tv_nsec=t2.tv_nsec-t1.tv_nsec) < 0){
        t.tv_sec--;
        t.tv_nsec+=1000000000;
    }
    printf("gaussian_blur    : %lld.%09ld\n", t.tv_sec, t.tv_nsec);

    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &t1);
    gaussian_blur_asm(&img1, width, height, channels);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &t2);
    t.tv_sec = t2.tv_sec-t1.tv_sec;
    if((t.tv_nsec=t2.tv_nsec-t1.tv_nsec) < 0){
        t.tv_sec--;
        t.tv_nsec+=1000000000;
    }
    printf("gaussian_blur_asm: %lld.%09ld\n", t.tv_sec, t.tv_nsec);

    stbi_write_bmp(output, width, height, channels, img1);
    return 0;
}
