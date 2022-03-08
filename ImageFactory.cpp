//
// Created by morel on 06/03/2022.
//

#include "ImageFactory.h"

Image *ImageFactory::createImage(const std::string &path) {
    ImageType type = Image::getType(path);

    if (type == ImageType::P2)
        return new ImagePGM;
    else if (type == ImageType::P3)
        return new ImagePPM;
    else
        throw std::runtime_error("Impossible to read this image format");
}
