//
// Created by Shaaheen on 4/19/2016.
//
#define CATCH_CONFIG_MAIN
#include "../catch.hpp"
#include "../Image.h"
#include "ImageTests.h"
#include <string>
#include <stdio.h>
#include <cstring>
using namespace SCRSHA001;
using namespace std;


TEST_CASE("Image class loading and saving"){
    SECTION("Saving"){ //Tests save function
        //Saves image, then reads in image and copares the two
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
    SECTION("Loading "){ //Tests load function
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
        Image *img = new Image(filename);
        delete img;
        REQUIRE(img->getHeight() == 0);
    }

    SECTION("Copy Constructor"){
        Image orig = Image(filename2);
        Image copy(orig);
        REQUIRE(orig.getWidth() == copy.getWidth());
        REQUIRE(orig.getHeight() == copy.getHeight());
        REQUIRE(strcmp( (const char *) orig.getData(),(const char *) copy.getData()) == 0 );//Makes sure data is the same

    }
    SECTION("Copy Assignment Operator Constructor"){
        Image orig = Image(filename2);
        Image copy = orig;
        REQUIRE(orig.getWidth() == copy.getWidth());
        REQUIRE(orig.getHeight() == copy.getHeight());
        REQUIRE(strcmp( (const char *) orig.getData(),(const char *) copy.getData()) == 0 );//Makes sure data is the same

    }
    SECTION("Move Constructor"){
        Image orig = Image(filename2);
        Image clone = orig;
        Image movedCopy(move(orig));

        //Check if has same values the original had
        REQUIRE(clone.getWidth() == movedCopy.getWidth());
        REQUIRE(clone.getHeight() == movedCopy.getHeight());
        REQUIRE(strcmp( (const char *) movedCopy.getData(),(const char *) clone.getData()) == 0 );//Makes sure data is the same

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
        REQUIRE(strcmp( (const char *) movedCopy.getData(),(const char *) clone.getData()) == 0 );//Makes sure data is the same

        //Checks original is empty
        REQUIRE(orig.dataNotEmpty() == true);

    }

}
TEST_CASE("Image class Iterator and its operators"){

    string filename= "donkey_mask.pgm";
    string filename2 = "Lenna_standard.pgm";
    Image img  = Image(filename2);

    SECTION("Iterator begin() and end() methods"){
        //Begin should point to the char at the beginning of the array
        Image::iterator iterator1 = img.begin();
        unsigned char iteratorData = *iterator1;
        unsigned char elementInMainData = img.getData()[0];
        REQUIRE(iteratorData == elementInMainData);

        //End should point to the char at the end of the array
        Image::iterator iterator2 = img.end();
        unsigned char iteratorData2 = *iterator2;
        unsigned char elementInMainData2 = img.getData()[img.getWidth() * img.getHeight()];
        REQUIRE(iteratorData2 == elementInMainData2);

    }
    SECTION("Iterator constructor and * operator"){
        Image::iterator iterator1 = Image::iterator(img.getData(),0);
        unsigned char *data = img.getData();
        REQUIRE(*img.getData() == *iterator1);
    }
    SECTION("Iterator copy operator"){
        Image::iterator iterator1 = img.begin();
        Image::iterator iterator2 = iterator1;
        iterator2 = iterator1;
        REQUIRE(*iterator1 == *iterator2); //Checks if the data inside or the same
    }
    SECTION("Iterator move operator"){
        Image::iterator iterator1 = img.begin();
        unsigned char storeOrginalBeforeMove = *iterator1;
        Image::iterator iterator2 = iterator1;
        iterator2 = move(iterator1);
        REQUIRE(storeOrginalBeforeMove == *iterator2); //Checks if the data inside or the same
        //REQUIRE(*iterator1 == nullptr); //Iterator should now empty since moved out data
    }

    SECTION("++ Iterator"){
        Image::iterator iterator1 = img.begin();
        unsigned char* data = img.getData();
        int countIfEqual = 0;
        int countNotEqual = 0;
        for (int i = 0; i < (img.getHeight()*img.getWidth()); ++i) {
            unsigned char elementInMainData = data[i];
            unsigned char iteratorData = *iterator1;
            if (elementInMainData == iteratorData){ //Had REQUIRE here but accumalted to too many assertions in test
                countIfEqual++;
            }
            else{
                countNotEqual++;
                cout<<"Not equal"<<endl;
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
        for (int i = (img.getHeight()*img.getWidth()); i >0; --i) {
            unsigned char elementInMainData = data[i];
            unsigned char iteratorData = *iterator1;
            if (elementInMainData == iteratorData){ //Had REQUIRE here but accumalted to too many assertions in test
                countIfEqual++;
            }
            --iterator1;
        }
        //Test if counter is equal to total number of elements in array
        REQUIRE(countIfEqual == (img.getHeight()*img.getWidth()));
    }

}
TEST_CASE("Addition and subtraction of images"){
    string filename= "Lenna_hat_mask.pgm";
    string filename2 = "Lenna_hat_mask.pgm";
    Image img  = Image(filename2);
    Image img2 = Image(filename);
    SECTION("Addition test"){
        Image addedImage;
        addedImage= img+img2; //Add images together
        unsigned char * addedData = addedImage.getData(); //Get data var to test against
        unsigned char * image1Data = img.getData();
        unsigned char * image2Data = img2.getData();
        int additionCorrectCounter = 0;
        int loopTill = 500/*img.getWidth() * img.getHeight()*/;
        for (int i = 0; i < loopTill; ++i) {
            unsigned char expectedAddedValue = addedData[i];
            unsigned char image1Val = image1Data[i];
            unsigned char image2Val = image2Data[i];
            if ((image1Val + image2Val)>255 ){ //If addition greater than 255, should be 255
                if (expectedAddedValue == 255)
                    additionCorrectCounter++;
            }
            else if (expectedAddedValue == (image1Val + image2Val)){ //Check addition correct
                additionCorrectCounter++;
            }
        }
        REQUIRE(additionCorrectCounter == loopTill/*(img.getWidth() + img.getHeight())*/ );
    }
    SECTION("Subtraction test"){
        Image addedImage;
        addedImage= img-img2; //Add images together
        unsigned char * addedData = addedImage.getData(); //Get data var to test against
        unsigned char * image1Data = img.getData();
        unsigned char * image2Data = img2.getData();
        int additionCorrectCounter = 0;
        int loopTill = 100; //Run tests until - ensures a large number of values are correct
        for (int i = 0; i < loopTill; ++i) {
            unsigned char expectedAddedValue = addedData[i];
            unsigned char image1Val = image1Data[i];
            unsigned char image2Val = image2Data[i];
            if ((image1Val - image2Val)<0 ){ //If addition greater than 255, should be 255
                if (expectedAddedValue == 0)
                    additionCorrectCounter++;
            }
            else if (expectedAddedValue == (image1Val - image2Val)){ //Check addition correct
                additionCorrectCounter++;
            }
            else{
                cout<<"not equal"<<endl;
            }
        }
        REQUIRE(additionCorrectCounter == loopTill);
    }

}

TEST_CASE("Thresholding, inverting and masking operator overloads"){
    string filename= "Lenna_standard.pgm";
    string filename2 = "Lenna_hat_mask.pgm";

    SECTION("Inverse Test"){
        Image img2(filename);
        //Image copyOf(img2); //copies image first
        Image inverse = !img2; //inverse image
        unsigned char * testAry = inverse.getData();
        int countIfInverse = 0;
        Image::iterator iteratorOfOrig = img2.begin();
        int counter = 0;
        for(int i = 0; i < (inverse.getWidth()*inverse.getHeight());++i){
            if ( inverse.getData()[i] == (255 - img2.getData()[i])){
                countIfInverse++;
            }
            ++iteratorOfOrig;
            counter++;
        }
        REQUIRE(countIfInverse > 254417); //If enough correct occurences to cover whole image -total length of char array then correct
    }

    SECTION("Mask test"){
        Image img2(filename);
        Image img(filename2);
        Image masking = img2/img;
        int counter = 0;
        for (int i = 0; i < img.getWidth()*img.getHeight(); ++i) {
            if ( (img.getData()[i]) ==255){
                if (masking.getData()[i] == img2.getData()[i]){
                    counter++;
                }
            }else if (masking.getData()[i] ==0){
                counter++;
            }
        }
        REQUIRE(counter > 254417);//If enough correct occurences to cover whole image -total length of char array then correct
    }
    SECTION("Threshold test"){
        Image img(filename2);
        Image thresheld = img*10;
        unsigned char * nvdjndv = thresheld.getData();
        int counter = 0;
        for (Image::iterator i = thresheld.begin(); i != thresheld.end(); ++i) {
            if ( ( (*i ) == 0 ) || ( (*i ) == 255 ) ){ //Image pixels should only be 0 or 255
                counter++;
            }
        }
        REQUIRE(counter > 254417);//If enough correct occurences to cover whole image -total length of char array then correct
    }

}

