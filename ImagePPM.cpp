//
// Created by morel on 06/03/2022.
//

#include "ImagePPM.h"

void ImagePPM::read(const std::string &path) {
    std::ifstream imgFile(path);

    if (imgFile.is_open()) {

        // read header
        imgFile >> format;
        imgFile >> width;
        imgFile >> height;
        imgFile >> depth;

        allocateData();

        // read body
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                imgFile >> data[j][i].red;
                imgFile >> data[j][i].green;
                imgFile >> data[j][i].blue;
            }
        }

        imgFile.close();
    } else
        throw std::runtime_error("Error opening file!");
}

void ImagePPM::save(const std::string &path) const {
    // set appropriate extension to prevent errors
    std::string newPath = replaceExt(path, ".ppm");

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
                imgFile << data[j][i].green << std::endl;
                imgFile << data[j][i].blue << std::endl;
            }
        }

        imgFile.close();
    } else
        throw std::runtime_error("Error saving file!");
}

ImagePPM *ImagePPM::Clone(bool withBody) {
    ImagePPM *imgCopy = new ImagePPM;
    imgCopy->copyHeaderFrom(*this);
    imgCopy->allocateData();
    if(data && withBody)
        imgCopy->copyDataFrom(*this);
    return imgCopy;
}
