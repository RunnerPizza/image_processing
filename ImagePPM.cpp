//
// Created by morel on 20/02/2022.
//

#include "ImagePPM.h"

ImagePPM::ImagePPM(const std::string &path) : path(path) {}

ImagePPM::~ImagePPM() { delete[] data; }

void ImagePPM::read() {
    img.open(path);

    if (img.is_open()) {
        readHeader();
        data = new Pixel[width * height];
        readBody();

        img.close();
    }

}

void ImagePPM::save(const std::string &name) {
    newimg.open("../product_images/" + name + ".ppm");

    if (newimg.is_open()) {
        writeHeader();
        writeBody();

        newimg.close();
    }

}

void ImagePPM::readHeader() {
    img >> type;
    img >> width;
    img >> height;
    img >> depth;
}

void ImagePPM::writeHeader() {
    newimg << type << std::endl;
    newimg << width << " " << height << std::endl;
    newimg << depth << std::endl;
}

void ImagePPM::readBody() {
    for (int i = 0; i < height; i++) // y axis
        for (int j = 0; j < width; j++) // x axis
            readPixel(j, i);
}

void ImagePPM::writeBody() {
    for (int i = 0; i < height; i++) // y axis
        for (int j = 0; j < width; j++) // x axis
            writePixel(j, i);
}

void ImagePPM::readPixel(int x, int y) {
    img >> data[width * y + x].red;
    img >> data[width * y + x].green;
    img >> data[width * y + x].blue;
}

void ImagePPM::writePixel(int x, int y) {
    newimg << data[width * y + x].red << " ";
    newimg << data[width * y + x].green << " ";
    newimg << data[width * y + x].blue << std::endl;
}

void ImagePPM::printInfo() const {
    std::cout << "type: " << type << std::endl
              << "path: " << path << std::endl
              << "width: " << width << std::endl
              << "height: " << height << std::endl
              << "depth: " << depth << std::endl;
}