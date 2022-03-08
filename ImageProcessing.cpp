//
// Created by tommaso on 22/02/22.
//

#include "ImageProcessing.h"
#include "ImagePGM.h"

Image *ImageProcessing::convolution(float kernel[3][3], Image *img) {
    float redSum, greenSum, blueSum;
    Image *result = img->Clone(false);
    Image *imgCopy = img->Clone(true);
    img->addNonZeroPadding();
    for (int k = 0; k < result->getHeight(); ++k) {
        for (int z = 0; z < result->getWidth(); ++z) {
            redSum = greenSum = blueSum = 0;
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    redSum += kernel[j][i] * img->getPixel(j + z, i + k).red;
                    greenSum += kernel[j][i] * img->getPixel(j + z, i + k).green;
                    blueSum += kernel[j][i] * img->getPixel(j + z, i + k).blue;
                }
            }
            redSum = round(redSum);
            greenSum = round(greenSum);
            blueSum = round(blueSum);

            result->getPixel(z, k).red = normalise(redSum);
            result->getPixel(z, k).green = normalise(greenSum);
            result->getPixel(z, k).blue = normalise(blueSum);
        }
    }

    delete imgCopy;

    return result;
}

int ImageProcessing::normalise(int value) {
    if (value > 255)
        value = 255;
    else if (value < 0)
        value = 0;
    return value;
}

Image *ImageProcessing::toGrayscale(Image *img) {
    float rWeight = 0.299;
    float gWeight = 0.587;
    float bWeight = 0.144;
    float weightedSum, Wr, Wg, Wb;
    Image *grayImg = new ImagePGM("P2", img->getWidth(), img->getHeight(), img->getDepth());
    for (int i = 0; i < img->getHeight(); ++i) {
        for (int j = 0; j < img->getWidth(); ++j) {
            Wr = rWeight * img->getPixel(j, i).red;
            Wg = gWeight * img->getPixel(j, i).green;
            Wb = bWeight * img->getPixel(j, i).blue;
            weightedSum = Wr + Wg + Wb;
            grayImg->getPixel(j, i) = roundf(weightedSum);
        }
    }
    return grayImg;
}

Image *ImageProcessing::box_blur(Image *img) {
    float box_blur[3][3];
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            box_blur[j][i] = (float) 1 / 9;
    return convolution(box_blur, img);
}

Image *ImageProcessing::identity(Image *img) {
    float identity[3][3]{{0, 0, 0},
                         {0, 1, 0},
                         {0, 0, 0}};
    return convolution(identity, img);
}

Image *ImageProcessing::sharpen(Image *img) {
    float sharpen[3][3]{{0,  -1, 0},
                        {-1, 5,  -1},
                        {0,  -1, 0}};
    return convolution(sharpen, img);
}

Image *ImageProcessing::ridge_detection1(Image *img) {
    float ridge_detection1[3][3]{{0, 1,  0},
                                 {1, -4, 1},
                                 {0, 1,  0}};
    if (img->getFormat() == "P3")
        img = toGrayscale(img);
    return convolution(ridge_detection1, img);
}

Image *ImageProcessing::ridge_detection2(Image *img) {
    float ridge_detection2[3][3]{{-1, -1, -1},
                                 {-1, 8,  -1},
                                 {-1, -1, -1}};
    if (img->getFormat() == "P3")
        img = toGrayscale(img);
    return convolution(ridge_detection2, img);
}