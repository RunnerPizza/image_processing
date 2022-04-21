//
// Created by morel on 24/02/2022.
//

#ifndef IMAGE_PROCESSING_IMAGE_H
#define IMAGE_PROCESSING_IMAGE_H

#include <iostream>
#include <fstream>
#include "Pixel.h"

enum class ImageType {
    P2, P3
};

class Image {
public:

    Image();

    virtual ~Image();

    void printInfo() const;

    virtual void read(const std::string &path) = 0;

    virtual void save(const std::string &path) const = 0;

    virtual Image *Clone(bool withBody = true) = 0;

    void addZeroPadding();

    void addNonZeroPadding();

    bool operator==(const Image &img);

    const std::string &getFormat() const { return format; }

    int getWidth() const { return width; }

    int getHeight() const { return height; }

    int getDepth() const { return depth; }

    const Pixel &getPixel(int x, int y) const;

    void setPixel(int x, int y, const Pixel &p);

    void setPixel(int x, int y, int value);

    void setRedPixel(int x, int y, int value);

    void setGreenPixel(int x, int y, int value);

    void setBluePixel(int x, int y, int value);

    static ImageType getType(const std::string &path);

protected:

    void allocateData();

    void deallocateData(Pixel **data, int width);

    void deallocateData();

    void copyDataFrom(const Image &img);

    void copyHeaderFrom(const Image &img);

    std::string replaceExt(const std::string &path, const std::string &newExt) const;

private:

    int normalise(int value);

protected:
    std::string format;
    int width;
    int height;
    int depth;
    Pixel **data;
};


#endif //IMAGE_PROCESSING_IMAGE_H
