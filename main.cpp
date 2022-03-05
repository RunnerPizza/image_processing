#include <iostream>
#include <memory>
#include "ImageProcessing.h"
#include "Image.h"

int main() {

    std::string image_reading_path;
    std::string image_saving_path;

    std::unique_ptr<Image> img;
    std::unique_ptr<Image> result;

    std::string quit = "no";
    do {
        std::cout << std::endl;
        std::cout << "What image you want to modify?" << std::endl;
        std::cout << "please insert the image path: ";
        std::cin >> image_reading_path;
        std::cout << std::endl;

        ImageType imgType = Image::getImageType(image_reading_path);

        try {
            if (imgType == ImageType::P2)
                img = std::unique_ptr<Image>(Image::readPGM(image_reading_path));
            else if (imgType == ImageType::P3)
                img = std::unique_ptr<Image>(Image::readPPM(image_reading_path));
            else if (imgType == ImageType::P) {
                std::cerr << "!!! the program cannot read this image format !!!" << std::endl;
                exit(0);
            }
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
                result = std::unique_ptr<Image>(ImageProcessing::identity(img.get()));
                break;
            case 2:
                result = std::unique_ptr<Image>(ImageProcessing::sharpen(img.get()));
                break;
            case 3:
                result = std::unique_ptr<Image>(ImageProcessing::ridge_detection1(img.get()));
                break;
            case 4:
                result = std::unique_ptr<Image>(ImageProcessing::ridge_detection2(img.get()));
                break;
            case 5:
                result = std::unique_ptr<Image>(ImageProcessing::box_blur(img.get()));
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

        ImageType resultType = Image::getImageType(image_saving_path);

        try {
            if (resultType == ImageType::P2) {
                Image::savePGM(image_saving_path, *result);
            } else if (resultType == ImageType::P3)
                Image::savePPM(image_saving_path, *result);
            else if (resultType == ImageType::P || resultType != imgType) {
                std::cerr << "!!! you cannot save the image with the current extension !!!" << std::endl;
                exit(0);
            }
        } catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
            exit(0);
        }

        std::cout << "Do you wanna quit? yes or no: ";
        std::cin >> quit;
        std::cout << std::endl;
    } while (quit == "no");

    return 0;
}
