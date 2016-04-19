//
// Created by Shaaheen on 4/17/2016.
//
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "Image.h"
#include "ImageTests.h"
#include <string>
#include <stdio.h>
using namespace SCRSHA001;
using namespace std;

TEST_CASE("Image class loading and saving"){
    SECTION("Loading"){
        Image *img = new Image();

        (*img).load("donkey_mask.pgm");
        REQUIRE((*img).getWidth() == 1280);
        REQUIRE((*img).getHeight() == 1207);

        (*img).load("Lenna_hat_mask.pgm");
        REQUIRE((*img).getWidth() == 512);
        REQUIRE((*img).getHeight() == 512);

        (*img).load("Lenna_standard.pgm");
        REQUIRE((*img).getWidth() == 512);
        REQUIRE((*img).getHeight() == 512);

        (*img).load("shrek_rectangular.pgm");
        REQUIRE((*img).getWidth() == 1280);
        REQUIRE((*img).getHeight() == 1207);

        delete img;

    }
    SECTION("Saving"){
        std::string filename= "donkey_mask.pgm";
        Image *img2 = new Image(filename);
        (*img2).save("Clone.pgm");
        delete img2;
        ifstream ifs(filename, ios::binary|ios::ate);
        ifstream::pos_type pos = ifs.tellg();
        int length = pos;
        char *pChars = new char[length];
        ifs.read(pChars, length);
        ifs.close();

        ifstream ifs2("Clone.pgm", ios::binary|ios::ate);
        ifstream::pos_type pos2 = ifs2.tellg();
        int length2 = pos;
        char *pChars2 = new char[length2];
        ifs2.read(pChars2, length2);
        ifs2.close();
        REQUIRE(length == length2);
        int n = memcmp(pChars,pChars2,length); //Compares two blocks of memory, if n ==0 then identical
        REQUIRE(n ==0);


    }


}

TEST_CASE("Image class constructors") {

}
TEST_CASE("Image class Iterator and its operators"){

}
TEST_CASE("Thresholding, inverting and masking operator overloads"){

}
TEST_CASE("Addition and subtraction of images"){

}
TEST_CASE("Filtering operator on Image"){

}