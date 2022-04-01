//
// Created by morel on 06/03/2022.
//

#ifndef IMAGE_PROCESSING_IMAGEFACTORY_H
#define IMAGE_PROCESSING_IMAGEFACTORY_H

#include "Image.h"
#include "ImagePGM.h"
#include "ImagePPM.h"
#include <exception>

class ImageFactory {
public:
    static std::unique_ptr<Image> createImage(const std::string &path);
};


#endif //IMAGE_PROCESSING_IMAGEFACTORY_H
