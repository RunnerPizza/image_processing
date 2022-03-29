//
// Created by morel on 24/02/2022.
//

#include "Image.h"
#include <exception>

void Image::allocateData() {
    data = new Pixel *[width];
    for (int i = 0; i < width; ++i)
        data[i] = new Pixel[height];
}

Image::~Image() {
    deallocateData();
}

void Image::printInfo() const {
    std::cout << "format: " << format << std::endl
              << "width: " << width << std::endl
              << "height: " << height << std::endl
              << "depth: " << depth << std::endl;
}

void Image::addZeroPadding() {
    int oldWidth, oldHeight;
    oldWidth = width;
    oldHeight = height;
    width += 2;
    height += 2;
    Pixel **oldData = data;
    allocateData();
    // set matrix to 0
    for (int i = 0; i < height; ++i)
        for (int j = 0; j < width; ++j)
            data[j][i] = 0;
    // copy old values at the center
    for (int i = 0; i < oldHeight; ++i)
        for (int j = 0; j < oldWidth; ++j)
            data[j + 1][i + 1] = oldData[j][i];

    deallocateData(oldData, oldWidth);
}

void Image::addNonZeroPadding() {
    int oldWidth, oldHeight;
    oldWidth = width;
    oldHeight = height;
    width += 2;
    height += 2;
    Pixel **oldData = data;
    allocateData();
    // set top left corner
    data[0][0] = oldData[0][0];
    // set top right corner
    data[width - 1][0] = oldData[oldWidth - 1][0];
    // set bottom left corner
    data[0][height - 1] = oldData[0][oldHeight - 1];
    // set bottom right corner
    data[width - 1][height - 1] = oldData[oldWidth - 1][oldHeight - 1];
    // set top margin
    for (int i = 0; i < oldWidth; ++i)
        data[i + 1][0] = oldData[i][0];
    // set left margin
    for (int i = 0; i < oldHeight; ++i)
        data[0][i + 1] = oldData[0][i];
    // set right margin
    for (int i = 0; i < oldHeight; ++i)
        data[width - 1][i + 1] = oldData[oldWidth - 1][i];
    // set bottom margin
    for (int i = 0; i < oldWidth; ++i)
        data[i + 1][height - 1] = oldData[i][oldHeight - 1];
    // copy old values at the center
    for (int i = 0; i < oldHeight; ++i)
        for (int j = 0; j < oldWidth; ++j)
            data[j + 1][i + 1] = oldData[j][i];

    deallocateData(oldData, oldWidth);
}

bool Image::operator==(const Image &img) {
    if (format != img.format || width != img.width || height != img.height || depth != img.depth)
        return false;
    for (int i = 0; i < height; ++i)
        for (int j = 0; j < width; ++j)
            if (data[j][i] != img.data[j][i])
                return false;
    return true;
}

void Image::copyHeaderFrom(const Image &img) {
    format = img.format;
    width = img.width;
    height = img.height;
    depth = img.depth;
}

void Image::copyDataFrom(const Image &img) {
    for (int i = 0; i < height; ++i)
        for (int j = 0; j < width; ++j)
            data[j][i] = img.data[j][i];
}

void Image::deallocateData(Pixel **data, int width) {
    if (data) {
        for (int i = 0; i < width; ++i)
            delete[] data[i];
        delete[] data;
    }
}

void Image::deallocateData() {
    deallocateData(data, width);
}

ImageType Image::getType(const std::string &path) {
    std::string extension = path.substr(path.find_last_of(".") + 1);

    if (extension == "pgm")
        return ImageType::P2;
    if (extension == "ppm")
        return ImageType::P3;
}

std::string Image::replaceExt(const std::string &path, const std::string &newExt) const {
    std::string newPath;
    for (int i = 0; path[i] != '.'; ++i) {
        newPath += path[i];
    }
    newPath += newExt;
    return newPath;
}