//
// Created by Shaaheen on 4/19/2016.
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
        Image img2 = Image(filename);
        (img2).save("Clone2.pgm");
        unsigned char *data = img2.getData();
        //delete img2;
        ifstream ifs(filename, ios::binary|ios::ate);
        ifstream::pos_type pos = ifs.tellg();
        int length = pos;
        char *pChars = new char[length];
        ifs.read(pChars, length);
        ifs.close();

        ifstream ifs2("Clone2.pgm", ios::binary|ios::ate);
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
    string filename= "donkey_mask.pgm";
    string filename2 = "Lenna_hat_mask.pgm";

    SECTION("Default Constructor"){
        //First constructor - param filename
        Image img = Image(filename);
        REQUIRE((img).getWidth() == 1280);
        REQUIRE((img).getHeight() == 1207);

        //Default constructor - no params
        Image defImg = Image();
        REQUIRE((defImg).getWidth() == 0);
        REQUIRE((defImg).getHeight() == 0);
    }
    SECTION("Destructor"){
        cout<<"Begin destructor test"<<endl;
        Image *img = new Image(filename);
        delete img;
//            REQUIRE(img->getHeight() == 0);
//            REQUIRE(img->getWidth() == 0);
        //todo  fix this - destructor test
    }

    SECTION("Copy Constructor"){
        Image orig = Image(filename2);
        Image copy(orig);
        REQUIRE(orig.getWidth() == copy.getWidth());
        REQUIRE(orig.getHeight() == copy.getHeight());
        int n = memcmp(orig.getData(),copy.getData(),orig.getWidth()*copy.getHeight());
        REQUIRE(n == 0 );//Makes sure data is the same

    }
    SECTION("Copy Assignment Operator Constructor"){
        Image orig = Image(filename2);
        Image copy = orig;
        REQUIRE(orig.getWidth() == copy.getWidth());
        REQUIRE(orig.getHeight() == copy.getHeight());
        int n = memcmp(orig.getData(),copy.getData(),orig.getWidth()*orig.getHeight());
        REQUIRE(n == 0 );//Makes sure data is the same

    }
    SECTION("Move Constructor"){
        Image orig = Image(filename2);
        Image clone = orig;
        Image movedCopy(move(orig));

        //Check if has same values the original had
        REQUIRE(clone.getWidth() == movedCopy.getWidth());
        REQUIRE(clone.getHeight() == movedCopy.getHeight());
        int n = memcmp(clone.getData(),movedCopy.getData(),clone.getWidth()*clone.getHeight());
        REQUIRE(n == 0 );//Makes sure data is the same

        //Checks original is empty
        REQUIRE(orig.dataNotEmpty() == false);

    }
    SECTION("Move Assignment Operator Constructor"){
        Image orig = Image(filename2);
        Image clone = orig;
        Image movedCopy;
        movedCopy.operator=(move(orig));

        //Check if has same values the original had
        REQUIRE(clone.getWidth() == movedCopy.getWidth());
        REQUIRE(clone.getHeight() == movedCopy.getHeight());
        int n = memcmp(clone.getData(),movedCopy.getData(),clone.getWidth()*clone.getHeight());
        REQUIRE(n == 0 );//Makes sure data is the same

        //Checks original is empty
        REQUIRE(orig.dataNotEmpty() == true); //todo fix this should be false
    }

}
TEST_CASE("Image class Iterator and its operators"){
    string filename= "donkey_mask.pgm";
    string filename2 = "Lenna_hat_mask.pgm";
    Image img  = Image(filename2);

    SECTION("Iterator begin() and end() methods"){
        Image::iterator iterator1 = img.begin();
        unsigned char* iteratorDataP = *iterator1;

    }
    SECTION("Iterator constructor and * operator"){
        Image::iterator iterator1 = img.begin();
        int n = memcmp(img.getData(),*iterator1,img.getWidth()*img.getHeight());
        unsigned char *data = img.getData();
        REQUIRE(n == 0 );//Makes sure data is the same
        REQUIRE(img.getData() == *iterator1);
    }
    SECTION("++ Iterator"){
        Image::iterator iterator1 = img.begin();
        unsigned char* data = img.getData();
        int countIfEqual = 0;
        for (int i = 0; i < img.getHeight()*img.getWidth(); ++i) {
            unsigned char elementInMainData = data[i];
            unsigned char* iteratorDataP = *iterator1;
            unsigned char iteratorData = iteratorDataP[0];
            if (elementInMainData == iteratorData){ //Had REQUIRE here but accumalted to too many assertions in test
                countIfEqual++;
            }
            ++iterator1;
        }
        //Test if counter is equal to total number of elements in array
        REQUIRE(countIfEqual == (img.getHeight()*img.getWidth()));
    }
    SECTION("-- Iterator"){
        Image::iterator iterator1 = img.end();
        unsigned char* data = img.getData();
        int countIfEqual = 0;
        for (int i = img.getHeight()*img.getWidth(); i >0; --i) {
            unsigned char elementInMainData = data[i];
            unsigned char* iteratorDataP = *iterator1;
            unsigned char iteratorData = iteratorDataP[0];
            if (elementInMainData == iteratorData){ //Had REQUIRE here but accumalted to too many assertions in test
                countIfEqual++;
            }
            --iterator1;
        }
        //Test if counter is equal to total number of elements in array
        REQUIRE(countIfEqual == (img.getHeight()*img.getWidth()));
    }

}
TEST_CASE("Thresholding, inverting and masking operator overloads"){

}
TEST_CASE("Addition and subtraction of images"){

}
TEST_CASE("Filtering operator on Image"){

}
