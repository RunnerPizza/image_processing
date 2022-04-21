//
// Created by morel on 24/02/2022.
//

#include <cmath>
#include "Pixel.h"

Pixel::Pixel(int r, int g, int b) : red(r), green(g), blue(b) {}

Pixel::Pixel(int value) : red(value), green(value), blue(value) {}

Pixel::Pixel(float r, float g, float b) : red(roundf(r)), green(roundf(g)), blue(roundf(b)) {}

const Pixel &Pixel::operator=(int value) {
    red = value;
    green = value;
    blue = value;
    return *this;
}

bool Pixel::operator==(const Pixel &pixel) {
    if (red == pixel.red && green == pixel.green && blue == pixel.blue)
        return true;
    return false;
}

bool Pixel::operator!=(const Pixel &pixel) {
    if (red != pixel.red || green != pixel.green || blue != pixel.blue)
        return true;
    return false;
}
