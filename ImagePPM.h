//
// Created by morel on 06/03/2022.
//

#ifndef IMAGE_PROCESSING_IMAGEPPM_H
#define IMAGE_PROCESSING_IMAGEPPM_H

#include "Image.h"

class ImagePPM : public Image{
public:
    ImagePPM() = default;
    virtual ~ImagePPM() = default;
    void read(const std::string &path) override;
    void save(const std::string &path) const override;
    ImagePPM* Clone(bool withBody = true) override;
};


#endif //IMAGE_PROCESSING_IMAGEPPM_H
