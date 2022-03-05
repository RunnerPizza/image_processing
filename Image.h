//
// Created by morel on 24/02/2022.
//

#ifndef IMAGE_PROCESSING_IMAGE_H
#define IMAGE_PROCESSING_IMAGE_H

#include <iostream>
#include <fstream>
#include "Pixel.h"

enum class ImageType {P, P2, P3};

class Image {
public:

    Image();

    Image(const Image &img);

    Image(const std::string &format, int width, int height, int depth);

    ~Image();

    void printInfo() const;

    static Image *readPGM(const std::string &path);

    static Image *readPPM(const std::string &path);

    static void savePGM(const std::string &path, const Image &image);

    static void savePPM(const std::string &path, const Image &image);

    void addZeroPadding();

    void addNonZeroPadding();

    bool operator== (const Image& img);

    const Image &operator= (const Image& img);

    const std::string &getFormat() const { return format; }

    void setFormat(const std::string &format) { Image::format = format; }

    void setWidth(int width) { Image::width = width; }

    void setHeight(int height) { Image::height = height; }

    void setDepth(int depth) { Image::depth = depth; }

    int getWidth() const { return width; }

    int getHeight() const { return height; }

    int getDepth() const { return depth; }

    Pixel& getPixel(int x, int y) const { return data[x][y]; }

    static ImageType getImageType(const std::string &path);

protected:
    std::string format;
    int width;
    int height;
    int depth;
    Pixel **data;
};


#endif //IMAGE_PROCESSING_IMAGE_H
