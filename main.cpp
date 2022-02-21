#include <iostream>
#include "ImagePPM.h"

int main() {
    std::string landscape_path = "../sample_images/landscape.ppm";

    ImagePPM landscape(landscape_path);

    landscape.read();
    landscape.printInfo();
    landscape.applyBlueFilter(50);
    landscape.save("landscape_copy");

    return 0;
}
