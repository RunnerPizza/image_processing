//
// Created by tommaso on 01/03/22.
//

#include "gtest/gtest.h"
#include "../Image.h"
#include "../ImageFactory.h"
#include "../ImageProcessing.h"

class ImageProcessingSuite : public ::testing::Test {
protected:
    virtual void SetUp() {
        img = ImageFactory::createImage("sample_images/test.ppm");
        img->read("sample_images/test.ppm");
    }

    virtual void TearDown() {
        delete img;
    }

    Image *img;
};

TEST_F(ImageProcessingSuite, TestIdentity) {
    std::string target_image_path = "sample_images/unit_testing/identity.ppm";
    std::unique_ptr<Image> resultImg(ImageProcessing::identity(img));
    std::unique_ptr<Image> targetImg(ImageFactory::createImage(target_image_path));
    targetImg->read(target_image_path);
    EXPECT_TRUE(*resultImg == *targetImg);
}

TEST_F(ImageProcessingSuite, TestSharpen) {
    std::string target_image_path = "sample_images/unit_testing/sharpen.ppm";
    std::unique_ptr<Image> resultImg(ImageProcessing::sharpen(img));
    std::unique_ptr<Image> targetImg(ImageFactory::createImage(target_image_path));
    targetImg->read(target_image_path);
    EXPECT_TRUE(*resultImg == *targetImg);
}

TEST_F(ImageProcessingSuite, TestRidgeDetection1) {
    std::string target_image_path = "sample_images/unit_testing/ridge_detection1.pgm";
    std::unique_ptr<Image> resultImg(ImageProcessing::ridge_detection1(img));
    std::unique_ptr<Image> targetImg(ImageFactory::createImage(target_image_path));
    targetImg->read(target_image_path);
    EXPECT_TRUE(*resultImg == *targetImg);
}

TEST_F(ImageProcessingSuite, TestRidgeDetection2) {
    std::string target_image_path = "sample_images/unit_testing/ridge_detection2.pgm";
    std::unique_ptr<Image> resultImg(ImageProcessing::ridge_detection2(img));
    std::unique_ptr<Image> targetImg(ImageFactory::createImage(target_image_path));
    targetImg->read(target_image_path);
    EXPECT_TRUE(*resultImg == *targetImg);
}

TEST_F(ImageProcessingSuite, TestBoxBlur) {
    std::string target_image_path = "sample_images/unit_testing/box_blur.ppm";
    std::unique_ptr<Image> resultImg(ImageProcessing::box_blur(img));
    std::unique_ptr<Image> targetImg(ImageFactory::createImage(target_image_path));
    targetImg->read(target_image_path);
    EXPECT_TRUE(*resultImg == *targetImg);
}


TEST_F(ImageProcessingSuite, TestZeroPadding) {
    std::string target_image_path = "sample_images/unit_testing/zero_padding.ppm";
    std::unique_ptr<Image> resultImg(img->Clone(true));
    resultImg->addZeroPadding();
    std::unique_ptr<Image> targetImg(ImageFactory::createImage(target_image_path));
    targetImg->read(target_image_path);
    EXPECT_TRUE(*resultImg == *targetImg);
}

TEST_F(ImageProcessingSuite, TestNonZeroPadding) {
    std::string target_image_path = "sample_images/unit_testing/non_zero_padding.ppm";
    std::unique_ptr<Image> resultImg(img->Clone(true));
    resultImg->addNonZeroPadding();
    std::unique_ptr<Image> targetImg(ImageFactory::createImage(target_image_path));
    targetImg->read(target_image_path);
    EXPECT_TRUE(*resultImg == *targetImg);
}

TEST_F(ImageProcessingSuite, TestToGrayscale) {
    std::string target_image_path = "sample_images/unit_testing/grayscale.pgm";
    std::unique_ptr<Image> resultImg(ImageProcessing::toGrayscale(img));
    std::unique_ptr<Image> targetImg(ImageFactory::createImage(target_image_path));
    targetImg->read(target_image_path);
    EXPECT_TRUE(*resultImg == *targetImg);
}

TEST_F(ImageProcessingSuite, TestFileReading) {
    std::unique_ptr<Image> imgFile(ImageFactory::createImage("/wrong/image/path/image.ppm"));
    EXPECT_THROW({
                     try {
                         imgFile->read("/wrong/image/path/image.ppm");
                     }
                     catch (const std::runtime_error &e) {
                         EXPECT_STREQ("Error opening file!", e.what());
                         throw;
                     }
                 }, std::runtime_error);
}

TEST_F(ImageProcessingSuite, TestFileSaving) {
    std::unique_ptr<Image> imgFile(ImageFactory::createImage("sample_images/test.ppm"));
    imgFile->read("sample_images/test.ppm");
    EXPECT_THROW({
                     try {
                         imgFile->save("/wrong/image/path/image.ppm");
                     }
                     catch (const std::runtime_error &e) {
                         EXPECT_STREQ("Error saving file!", e.what());
                         throw;
                     }
                 }, std::runtime_error);
}

TEST_F(ImageProcessingSuite, TestGetPixel) {
    Pixel expectedPixel, currentPixel;
    // wrong coordinates value
    img->getPixel(-4, 1);
    // correct coordinates value
    expectedPixel = 255;
    currentPixel = img->getPixel(1, 1);
    EXPECT_TRUE(currentPixel == expectedPixel);
}

TEST_F(ImageProcessingSuite, TestSetPixel) {
    Pixel expectedPixel(153, 0, 76);
    Pixel currentPixel;
    // wrong coordinates value
    img->setPixel(-5,20, 0);
    // correct coordinates value
    img->setRedPixel(0,0, 153);
    img->setGreenPixel(0,0, 0);
    img->setBluePixel(0,0, 76);
    currentPixel = img->getPixel(0, 0);
    EXPECT_TRUE(currentPixel == expectedPixel);
}