#include <math.h>
#include "gaussian_blur.h"

void gaussian_blur(unsigned char **img, int width, int height, int channels){
    double matrix[5][5] = {{1/256., 4/256., 6/256., 4/256., 1/256.},
                           {4/256., 16/256., 24/256., 16/256., 4/256.},
                           {6/256., 24/256., 36/256., 24/256., 6/256.},
                           {4/256., 16/256., 24/256., 16/256., 4/256.},
                           {1/256., 4/256., 6/256., 4/256., 1/256.}};

    for(int i = 2; i < height-2; i++){
        for(int j = 2; j < width-2; j++){
            for(int k = 0; k < channels; k++){
                double new_px = 0;

                for(int m = 0; m < 5; m++){
                    for(int n = 0; n < 5; n++){
                        new_px += (*img)[(i-2+m)*width*channels+(j-2+n)*channels + k]*matrix[m][n];
                    }
                }

                (*img)[i*channels*width+j*channels+k] = (unsigned char)round(new_px);
            }
        }
    }
}