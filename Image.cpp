//
// Created by morel on 24/02/2022.
//

#include "Image.h"
#include <exception>

Image::Image() : format(""), width(0), height(0), depth(0), data(nullptr) {}

Image::Image(const Image &img) : format(img.format) { // copy constructor
    // copy header
    width = img.width;
    height = img.height;
    depth = img.depth;

    // memory allocation for data
    data = new Pixel *[width];
    for (int i = 0; i < width; ++i)
        data[i] = new Pixel[height];

    // copy body
    if (img.data)
        for (int i = 0; i < height; ++i)
            for (int j = 0; j < width; ++j)
                data[j][i] = img.data[j][i];
}

Image::Image(const std::string &format, int width, int height, int depth) {
    this->format = format;
    this->width = width;
    this->height = height;
    this->depth = depth;

    // memory allocation for data
    data = new Pixel *[width];
    for (int i = 0; i < width; ++i)
        data[i] = new Pixel[height];
}

Image::~Image() {
    for (int i = 0; i < width; ++i)
        delete[] data[i];
    delete[] data;
}

Image *Image::readPGM(const std::string &path) {
    Image *img = nullptr;
    std::ifstream imgFile(path);

    if (imgFile.is_open()) {
        img = new Image;

        // read header
        imgFile >> img->format;
        imgFile >> img->width;
        imgFile >> img->height;
        imgFile >> img->depth;

        // memory allocation for data
        img->data = new Pixel *[img->width];
        for (int i = 0; i < img->width; ++i)
            img->data[i] = new Pixel[img->height];

        // read body
        int pixelValue;
        for (int i = 0; i < img->height; i++) {
            for (int j = 0; j < img->width; j++) { // imgFile << data[j][i];
                imgFile >> pixelValue;
                img->data[j][i] = pixelValue;
            }
        }

        imgFile.close();
    } else
        throw std::runtime_error("Error opening file!");

    return img;
}

Image *Image::readPPM(const std::string &path) {
    Image *img = nullptr;
    std::ifstream imgFile(path);

    if (imgFile.is_open()) {
        img = new Image;

        // read header
        imgFile >> img->format;
        imgFile >> img->width;
        imgFile >> img->height;
        imgFile >> img->depth;

        // memory allocation for data
        img->data = new Pixel *[img->width];
        for (int i = 0; i < img->width; ++i)
            img->data[i] = new Pixel[img->height];

        // read body
        for (int i = 0; i < img->height; i++) {
            for (int j = 0; j < img->width; j++) {
                imgFile >> img->data[j][i].red;
                imgFile >> img->data[j][i].green;
                imgFile >> img->data[j][i].blue;
            }
        }

        imgFile.close();
    } else
        throw std::runtime_error("Error opening file!");

    return img;
}

void Image::savePGM(const std::string &path, const Image &img) {
    std::ofstream imgFile(path);

    if (imgFile.is_open()) {
        // write header
        imgFile << img.format << std::endl;
        imgFile << img.width << " " << img.height << std::endl;
        imgFile << img.depth << std::endl;

        //write body
        for (int i = 0; i < img.height; i++) {
            for (int j = 0; j < img.width; j++) {
                imgFile << img.data[j][i].red << std::endl;
            }
        }

        imgFile.close();
    }else
        throw std::runtime_error("Error saving file!");
}

void Image::savePPM(const std::string &path, const Image &img) {
    std::ofstream imgFile(path);

    if (imgFile.is_open()) {
        // write header
        imgFile << img.format << std::endl;
        imgFile << img.width << " " << img.height << std::endl;
        imgFile << img.depth << std::endl;

        //write body
        for (int i = 0; i < img.height; i++) {
            for (int j = 0; j < img.width; j++) {
                imgFile << img.data[j][i].red << std::endl;
                imgFile << img.data[j][i].green << std::endl;
                imgFile << img.data[j][i].blue << std::endl;
            }
        }

        imgFile.close();
    } else
        throw std::runtime_error("Error saving file!");
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
    // memory allocation for data
    data = new Pixel *[width];
    for (int i = 0; i < width; ++i)
        data[i] = new Pixel[height];
    // set matrix to 0
    for (int i = 0; i < height; ++i)
        for (int j = 0; j < width; ++j)
            data[j][i] = 0;
    // copy old values at the center
    for (int i = 0; i < oldHeight; ++i)
        for (int j = 0; j < oldWidth; ++j)
            data[j + 1][i + 1] = oldData[j][i];
    // memory deallocation for old data
    for (int i = 0; i < oldWidth; ++i)
        delete[] oldData[i];
    delete[] oldData;
}

void Image::addNonZeroPadding() {
    int oldWidth, oldHeight;
    oldWidth = width;
    oldHeight = height;
    width += 2;
    height += 2;
    Pixel **oldData = data;
    // memory allocation for data
    data = new Pixel *[width];
    for (int i = 0; i < width; ++i)
        data[i] = new Pixel[height];
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
    // memory deallocation for old data
    for (int i = 0; i < oldWidth; ++i)
        delete[] oldData[i];
    delete[] oldData;
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

const Image &Image::operator=(const Image &img) {
    if (this != &img) {
        // memory deallocation for data
        if (data) {
            for (int i = 0; i < width; ++i)
                delete[] data[i];
            delete[] data;
        }

        // copy header
        format = img.format;
        width = img.width;
        height = img.height;
        depth = img.depth;

        if (img.data) {
            // memory allocation for data
            data = new Pixel *[width];
            for (int i = 0; i < width; ++i)
                data[i] = new Pixel[height];

            // copy body
            if (img.data)
                for (int i = 0; i < height; ++i)
                    for (int j = 0; j < width; ++j)
                        data[j][i] = img.data[j][i];
        }

    }
    return *this;
}

ImageType Image::getImageType(const std::string &path) {
    std::string extension = path.substr(path.find_last_of(".") + 1);

    if (extension == "pgm")
        return ImageType::P2;
    if (extension == "ppm")
        return ImageType::P3;
    return ImageType::P;
}