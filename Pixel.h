//
// Created by morel on 24/02/2022.
//

#ifndef IMAGE_PROCESSING_PIXEL_H
#define IMAGE_PROCESSING_PIXEL_H


class Pixel {
public:

    Pixel() = default;

    Pixel(int r, int g, int b);

    Pixel(int value);

    const Pixel& operator=(int value);

    const Pixel& operator=(const Pixel& pixel);

    bool operator==(const Pixel &pixel);

    bool operator!=(const Pixel &pixel);

public:
    int red;
    int green;
    int blue;
};


#endif //IMAGE_PROCESSING_PIXEL_H
