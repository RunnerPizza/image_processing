//
// Created by morel on 06/03/2022.
//

#ifndef IMAGE_PROCESSING_IMAGEPGM_H
#define IMAGE_PROCESSING_IMAGEPGM_H

#include "Image.h"

class ImagePGM : public Image {
public:
    ImagePGM() = default;
    virtual ~ImagePGM() = default;
    ImagePGM(const std::string &format, int width, int height, int depth);
    void read(const std::string &path) override;
    void save(const std::string &path) override;
    ImagePGM* Clone(bool withBody = true) override;
};


#endif //IMAGE_PROCESSING_IMAGEPGM_H
