//
// Created by tommaso on 01/03/22.
//

#include "gtest/gtest.h"
#include "../Image.h"
#include "../ImageProcessing.h"

class ImageProcessingSuite : public ::testing::Test {
protected:
    virtual void SetUp() {
        img = Image::readPPM("../../sample_images/test.ppm");
    }

    virtual void TearDown() {
        delete img;
    }

    Image *img;
};

TEST_F(ImageProcessingSuite, TestIdentity) {
    std::unique_ptr<Image> resultImg(ImageProcessing::identity(img));
    std::unique_ptr<Image> targetImg(Image::readPPM("../../sample_images/unit_testing/identity.ppm"));
    EXPECT_EQ(*resultImg == *targetImg, true);
}

TEST_F(ImageProcessingSuite, TestSharpen) {
    std::unique_ptr<Image> resultImg(ImageProcessing::sharpen(img));
    std::unique_ptr<Image> targetImg(Image::readPPM("../../sample_images/unit_testing/sharpen.ppm"));
    EXPECT_EQ(*resultImg == *targetImg, true);
}

TEST_F(ImageProcessingSuite, TestRidgeDetection1) {
    std::unique_ptr<Image> resultImg(ImageProcessing::ridge_detection1(img));
    std::unique_ptr<Image> targetImg(Image::readPPM("../../sample_images/unit_testing/ridge_detection1.ppm"));
    EXPECT_EQ(*resultImg == *targetImg, true);
}

TEST_F(ImageProcessingSuite, TestRidgeDetection2) {
    std::unique_ptr<Image> resultImg(ImageProcessing::ridge_detection2(img));
    std::unique_ptr<Image> targetImg(Image::readPPM("../../sample_images/unit_testing/ridge_detection2.ppm"));
    EXPECT_EQ(*resultImg == *targetImg, true);
}

TEST_F(ImageProcessingSuite, TestBoxBlur) {
    std::unique_ptr<Image> resultImg(ImageProcessing::box_blur(img));
    std::unique_ptr<Image> targetImg(Image::readPPM("../../sample_images/unit_testing/box_blur.ppm"));
    EXPECT_EQ(*resultImg == *targetImg, true);
}

TEST_F(ImageProcessingSuite, TestToGrayscale) {
    std::unique_ptr<Image> resultImg(ImageProcessing::toGrayscale(*img));
    std::unique_ptr<Image> targetImg(Image::readPGM("../../sample_images/unit_testing/grayscale.pgm"));
    EXPECT_EQ(*resultImg == *targetImg, true);
}

TEST_F(ImageProcessingSuite, TestZeroPadding) {
    std::unique_ptr<Image> resultImg(new Image(*img));
    resultImg->addZeroPadding();
    std::unique_ptr<Image> targetImg(Image::readPPM("../../sample_images/unit_testing/zero_padding.ppm"));
    EXPECT_EQ(*resultImg == *targetImg, true);
}

TEST_F(ImageProcessingSuite, TestNonZeroPadding) {
    std::unique_ptr<Image> resultImg(new Image(*img));
    resultImg->addNonZeroPadding();
    std::unique_ptr<Image> targetImg(Image::readPPM("../../sample_images/unit_testing/non_zero_padding.ppm"));
    EXPECT_EQ(*resultImg == *targetImg, true);
}