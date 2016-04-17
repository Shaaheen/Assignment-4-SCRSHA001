//
// Created by Shaaheen on 4/17/2016.
//
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "Image.h"
#include "ImageTests.h"
using namespace SCRSHA001;

TEST_CASE("Image class loading and saving") {
    Image *img = new Image();
    (*img).load("donkey_mask.pgm");
    delete img;
}

TEST_CASE("Image class constructors") {

    SECTION("Testing letter frequency table") {

    }
}
TEST_CASE("Image class Iterator and its operators"){

}
TEST_CASE("Thresholding, inverting and masking operator overloads"){

}
TEST_CASE("Addition and subtraction of images"){

}
TEST_CASE("Filtering operator on Image"){

}