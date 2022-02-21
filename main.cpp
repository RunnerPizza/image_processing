#include <iostream>
#include "ImagePPM.h"

int main() {
    std::string landscape_path = "../sample_images/landscape.ppm";

    ImagePPM landscape(landscape_path);

    landscape.read();
    landscape.printInfo();
    landscape.save("landscape_copy");

    return 0;
}
