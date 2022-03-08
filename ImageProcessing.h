//
// Created by tommaso on 22/02/22.
//

#ifndef IMAGE_PROCESSING_IMAGEPROCESSING_H
#define IMAGE_PROCESSING_IMAGEPROCESSING_H

#include "Image.h"
#include "ImagePPM.h"
#include <cmath>

class ImageProcessing {
public:
    static Image *identity(Image *img);

    static Image *sharpen(Image *img);

    static Image *ridge_detection1(Image *img);

    static Image *ridge_detection2(Image *img);

    static Image *box_blur(Image *img);

    static Image *toGrayscale(Image *img);

private:
    static Image *convolution(float kernel[3][3], Image *img);

    static int normalise(int value);
};


#endif //IMAGE_PROCESSING_IMAGEPROCESSING_H
