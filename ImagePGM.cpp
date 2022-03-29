//
// Created by morel on 06/03/2022.
//

#include "ImagePGM.h"

ImagePGM::ImagePGM(const std::string &format, int width, int height, int depth) {
    this->format = format;
    this->width = width;
    this->height = height;
    this->depth = depth;

    allocateData();
}

void ImagePGM::read(const std::string &path) {
    std::ifstream imgFile(path);

    if (imgFile.is_open()) {

        // read header
        imgFile >> format;
        imgFile >> width;
        imgFile >> height;
        imgFile >> depth;

        allocateData();

        // read body
        int pixelValue;
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                imgFile >> pixelValue;
                data[j][i] = pixelValue;
            }
        }

        imgFile.close();
    } else
        throw std::runtime_error("Error opening file!");
}

void ImagePGM::save(const std::string &path) const {
    // set appropriate extension to prevent errors
    std::string newPath = replaceExt(path, ".pgm");

    std::ofstream imgFile(newPath);

    if (imgFile.is_open()) {
        // write header
        imgFile << format << std::endl;
        imgFile << width << " " << height << std::endl;
        imgFile << depth << std::endl;

        //write body
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                imgFile << data[j][i].red << std::endl;
            }
        }

        imgFile.close();
    } else
        throw std::runtime_error("Error saving file!");
}

ImagePGM *ImagePGM::Clone(bool withBody) {
    ImagePGM *imgCopy = new ImagePGM;
    imgCopy->copyHeaderFrom(*this);
    imgCopy->allocateData();
    if(data && withBody)
        imgCopy->copyDataFrom(*this);
    return imgCopy;
}
