#include <iostream>
#include "ImageProcessing.h"
#include "Image.h"
#include "ImageFactory.h"

int main() {

    std::string image_reading_path;
    std::string image_saving_path;

    Image *img = nullptr;
    Image *result = nullptr;

    std::string quit = "no";
    do {
        std::cout << std::endl;
        std::cout << "What image you want to modify?" << std::endl;
        std::cout << "please insert the image path: ";
        std::cin >> image_reading_path;
        std::cout << std::endl;

        try {
            img = ImageFactory::createImage(image_reading_path);
            img->read(image_reading_path);
        } catch (const std::exception &e) {
            std::cerr << e.what() << std::endl;
            exit(0);
        }

        std::cout << "--------- MENU ---------" << std::endl;
        std::cout << "1 - identity" << std::endl;
        std::cout << "2 - sharpen" << std::endl;
        std::cout << "3 - ridge detection 1" << std::endl;
        std::cout << "4 - ridge detection 2" << std::endl;
        std::cout << "5 - box blur" << std::endl;
        std::cout << "------------------------" << std::endl;
        std::cout << std::endl;

        int choice;
        std::cout << "Which filter you want to apply?" << std::endl;
        std::cout << "please enter the filter's number: ";
        std::cin >> choice;
        std::cout << std::endl;

        switch (choice) {
            case 1:
                result = ImageProcessing::identity(img);
                break;
            case 2:
                result = ImageProcessing::sharpen(img);
                break;
            case 3:
                result = ImageProcessing::ridge_detection1(img);
                break;
            case 4:
                result = ImageProcessing::ridge_detection2(img);
                break;
            case 5:
                result = ImageProcessing::box_blur(img);
                break;
            default:
                std::cout << "option not available" << std::endl;
                exit(0);
        }

        std::cout << "What do you want to call the new image?" << std::endl;
        std::cout << "e.g. /home/user/Desktop/new_image.ppm" << std::endl;
        std::cout << "please insert the name: ";
        std::cin >> image_saving_path;
        std::cout << std::endl;

        try {
            result->save(image_saving_path);
        } catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
            exit(0);
        }

        std::cout << "Do you wanna quit? yes or no: ";
        std::cin >> quit;
        std::cout << std::endl;
    } while (quit == "no");

    delete img;
    delete result;

    return 0;
}
