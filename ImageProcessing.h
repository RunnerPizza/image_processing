//
// Created by tommaso on 22/02/22.
//

#ifndef IMAGE_PROCESSING_IMAGEPROCESSING_H
#define IMAGE_PROCESSING_IMAGEPROCESSING_H

#include "Image.h"
#include "ImagePPM.h"
#include <cmath>

enum class Operation {
    identity, sharpen, ridgeDetection1, ridgeDetection2, boxBlur, toGrayscale, gaussianBlur3x3, gaussianBlur5x5, unsharpMasking5x5
};

class ImageProcessing {
public:

    explicit ImageProcessing(int kS);

    ImageProcessing(const ImageProcessing &imp);

    ~ImageProcessing();

    const ImageProcessing &operator=(const ImageProcessing &imp);

    std::unique_ptr<Image> convolution(Operation op, std::unique_ptr<Image> &img);

private:
    std::unique_ptr<Image> convolution(const std::unique_ptr<Image> &img) const;

    std::unique_ptr<Image> toGrayscale(const std::unique_ptr<Image> &img) const;

    void initKernel(const float *values);

    void initKernel(float value);

    float **kernel;
    int kernelSize;
};


#endif //IMAGE_PROCESSING_IMAGEPROCESSING_H
