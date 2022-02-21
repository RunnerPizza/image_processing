//
// Created by morel on 20/02/2022.
//

#ifndef IMAGE_PROCESSING_IMAGEPPM_H
#define IMAGE_PROCESSING_IMAGEPPM_H

#include <iostream>
#include <fstream>

struct Pixel {
    int red;
    int green;
    int blue;
};

class ImagePPM {
public:
    explicit ImagePPM(const std::string &path);

    ~ImagePPM();

    void read();

    void save(const std::string &name);

    void printInfo() const;

    void applyBlueFilter(int intensity);

private:
    void readHeader();

    void writeHeader();

    void readBody();

    void writeBody();

    void readPixel(int x, int y);

    void writePixel(int x, int y);

private:
    std::string path, type;
    int width, height, depth;
    std::ifstream img;
    std::ofstream newimg;
    Pixel *data;
};


#endif //IMAGE_PROCESSING_IMAGEPPM_H
