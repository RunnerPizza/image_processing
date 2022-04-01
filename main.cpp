#include <iostream>
#include <memory>
#include "ImageProcessing.h"
#include "Image.h"
#include "ImageFactory.h"

int main() {

    std::string image_reading_path;
    std::string image_saving_path;

    std::unique_ptr<Image> img;
    std::unique_ptr<Image> result;

    std::string quit = "no";
    do {
        std::cout << std::endl;
        std::cout << "What image you want to modify?" << std::endl;
        std::cout << "please insert the image path" << std::endl;
        std::cout << ": ";
        std::cin >> image_reading_path;
        std::cout << std::endl;

        try {
            img = ImageFactory::createImage(image_reading_path);
            img->read(image_reading_path);
        } catch (const std::exception &e) {
            std::cerr << e.what() << std::endl;
            exit(0);
        }

        std::cout << std::endl;
        std::cout << "--------- MENU ---------" << std::endl;
        std::cout << "0 - identity" << std::endl;
        std::cout << "1 - sharpen" << std::endl;
        std::cout << "2 - ridge detection 1" << std::endl;
        std::cout << "3 - ridge detection 2" << std::endl;
        std::cout << "4 - box blur" << std::endl;
        std::cout << "5 - convert to grayscale" << std::endl;
        std::cout << "6 - gaussian blur 3x3" << std::endl;
        std::cout << "7 - gaussian blur 5x5" << std::endl;
        std::cout << "8 - unsharp masking 5x5" << std::endl;
        std::cout << "------------------------" << std::endl;
        std::cout << std::endl;

        int choice;

        std::cout << "Which filter you want to apply?" << std::endl;
        std::cout << "please enter the filter's number" << std::endl;
        std::cout << ": ";
        std::cin >> choice;
        std::cout << std::endl;

        while (!(choice >= 0 && choice <= 8)) {
            std::cout << "Option not available" << std::endl;
            std::cout << "please enter a correct filter number or -1 to quit" << std::endl;
            std::cout << ": ";
            std::cin >> choice;
            std::cout << std::endl;

            if (choice == -1) {
                std::cout << "Have a nice day" << std::endl;
                exit(0);
            }
        }

        int kernelSize;

        if(choice >= 0 && choice <= 6)
            kernelSize = 3;
        else
            kernelSize = 5;

        ImageProcessing gimp(kernelSize);

        result = gimp.convolution(static_cast<Operation>(choice), img);

        std::cout << "What do you want to call the new image?" << std::endl;
        std::cout << "please enter path and name" << std::endl;
        std::cout << "e.g. /home/user/Desktop/new_image_name.ppm" << std::endl;
        std::cout << ": ";
        std::cin >> image_saving_path;
        std::cout << std::endl;

        try {
            result->save(image_saving_path);
        } catch (const std::exception &e) {
            std::cerr << e.what() << std::endl;
            exit(0);
        }

        std::cout << "Do you wanna quit? yes or no: ";
        std::cin >> quit;
        std::cout << std::endl;
    } while (quit == "no");

    return 0;
}
