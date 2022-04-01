//
// Created by morel on 06/03/2022.
//

#include <memory>
#include "ImageFactory.h"

std::unique_ptr<Image> ImageFactory::createImage(const std::string &path) {
    ImageType type = Image::getType(path);

    if (type == ImageType::P2)
        return std::unique_ptr<Image>(new ImagePGM);
    else if (type == ImageType::P3)
        return std::unique_ptr<Image>(new ImagePPM);
    else
        throw std::runtime_error("Impossible to read this image format");
}
