//
// Created by tommaso on 22/02/22.
//

#include <memory>
#include "ImageProcessing.h"
#include "ImagePGM.h"

ImageProcessing::ImageProcessing(int kS) : kernelSize(kS) {
    kernel = new float *[kernelSize];
    for (int i = 0; i < kernelSize; ++i)
        kernel[i] = new float[kernelSize];
}

ImageProcessing::~ImageProcessing() {
    if (kernel) {
        for (int i = 0; i < kernelSize; ++i)
            delete[] kernel[i];
        delete[] kernel;
    }
}

std::unique_ptr<Image> ImageProcessing::convolution(const std::unique_ptr<Image> &img) const {
    float redSum, greenSum, blueSum;
    std::unique_ptr<Image> result(img->Clone(false));
    std::unique_ptr<Image> imgCopy(img->Clone(true));
    imgCopy->addNonZeroPadding();
    if (kernelSize == 5)
        imgCopy->addNonZeroPadding();
    for (int k = 0; k < result->getHeight(); ++k) {
        for (int z = 0; z < result->getWidth(); ++z) {
            redSum = greenSum = blueSum = 0;
            for (int i = 0; i < kernelSize; ++i) {
                for (int j = 0; j < kernelSize; ++j) {
                    redSum += kernel[j][i] * imgCopy->getPixel(j + z, i + k).red;
                    greenSum += kernel[j][i] * imgCopy->getPixel(j + z, i + k).green;
                    blueSum += kernel[j][i] * imgCopy->getPixel(j + z, i + k).blue;
                }
            }

            result->setPixel(z, k, {redSum, greenSum, blueSum});
        }
    }
    return result;
}

std::unique_ptr<Image> ImageProcessing::toGrayscale(const std::unique_ptr<Image> &img) const {
    float rWeight = 0.2989;
    float gWeight = 0.5870;
    float bWeight = 0.1140;
    float weightedSum, Wr, Wg, Wb;
    auto grayImg = std::unique_ptr<Image>(new ImagePGM("P2", img->getWidth(), img->getHeight(), img->getDepth()));
    for (int i = 0; i < img->getHeight(); ++i) {
        for (int j = 0; j < img->getWidth(); ++j) {
            Wr = rWeight * img->getPixel(j, i).red;
            Wg = gWeight * img->getPixel(j, i).green;
            Wb = bWeight * img->getPixel(j, i).blue;
            weightedSum = Wr + Wg + Wb;
            grayImg->setPixel(j, i, roundf(weightedSum));
        }
    }
    return grayImg;
}

std::unique_ptr<Image> ImageProcessing::convolution(Operation op, std::unique_ptr<Image> &img) {
    switch (op) {
        case Operation::identity: {
            float values[] = {0, 0, 0, 0, 1, 0, 0, 0, 0};
            initKernel(values);
            break;
        }
        case Operation::sharpen: {
            float values[] = {0, -1, 0, -1, 5, -1, 0, -1, 0};
            initKernel(values);
            break;
        }
        case Operation::ridgeDetection1: {
            float values[] = {0, 1, 0, 1, -4, 1, 0, 1, 0};
            initKernel(values);
            if (img->getFormat() == "P3")
                img = toGrayscale(img);
            break;
        }
        case Operation::ridgeDetection2: {
            float values[] = {-1, -1, -1, -1, 8, -1, -1, -1, -1};
            initKernel(values);
            if (img->getFormat() == "P3")
                img = toGrayscale(img);
            break;
        }
        case Operation::boxBlur: {
            initKernel((float) 1 / 9);
            break;
        }
        case Operation::toGrayscale: {
            return toGrayscale(img);
        }
        case Operation::gaussianBlur3x3: {
            float values[] = {1, 2, 1, 2, 4, 2, 1, 2, 1};
            for (int i = 0; i < kernelSize * kernelSize; ++i)
                values[i] *= (float) 1/16;
            initKernel(values);
            break;
        }
        case Operation::gaussianBlur5x5: {
            float values[] = {1, 4, 6, 4, 1, 4, 16, 24, 16, 4, 6, 24, 36, 24, 6, 4, 16, 24, 16, 4, 1, 4, 6, 4, 1};
            for (int i = 0; i < kernelSize * kernelSize; ++i)
                values[i] *= (float) 1/256;
            initKernel(values);
            break;
        }
        case Operation::unsharpMasking5x5: {
            float values[] = {1, 4, 6, 4, 1, 4, 16, 24, 16, 4, 6, 24, -476, 24, 6, 4, 16, 24, 16, 4, 1, 4, 6, 4, 1};
            for (int i = 0; i < kernelSize * kernelSize; ++i)
                values[i] *= (float) -1/256;
            initKernel(values);
            break;
        }
    }
    return convolution(img);
}

void ImageProcessing::initKernel(const float *values) {
    for (int i = 0; i < kernelSize; ++i) {
        for (int j = 0; j < kernelSize; ++j) {
            kernel[j][i] = values[kernelSize * i + j];
        }
    }
}

void ImageProcessing::initKernel(float value) {
    for (int i = 0; i < kernelSize; ++i) {
        for (int j = 0; j < kernelSize; ++j) {
            kernel[j][i] = value;
        }
    }
}

ImageProcessing::ImageProcessing(const ImageProcessing &imp) : ImageProcessing(imp.kernelSize) {
    for (int i = 0; i < kernelSize; ++i) {
        for (int j = 0; j < kernelSize; ++j) {
            kernel[j][i] = imp.kernel[j][i];
        }
    }
}

const ImageProcessing &ImageProcessing::operator=(const ImageProcessing &imp) {
    if (this != &imp) {
        if (kernel) {
            for (int i = 0; i < kernelSize; ++i)
                delete[] kernel[i];
            delete[] kernel;
        }

        kernelSize = imp.kernelSize;

        for (int i = 0; i < kernelSize; ++i) {
            for (int j = 0; j < kernelSize; ++j) {
                kernel[j][i] = imp.kernel[j][i];
            }
        }
    }
    return *this;
}