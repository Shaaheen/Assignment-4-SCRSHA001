//
// Created by Shaaheen on 4/19/2016.
//
#define CATCH_CONFIG_MAIN
//#include "catch.hpp"
#include "Image.h"
#include "ImageTests.h"
#include <string>
#include <stdio.h>
using namespace SCRSHA001;
using namespace std;
//
//TEST_CASE("Image class loading and saving"){
//    SECTION("Loading"){
//        Image *img = new Image();
//
//        (*img).load("donkey_mask.pgm");
//        REQUIRE((*img).getWidth() == 1280);
//        REQUIRE((*img).getHeight() == 1207);
//
//        (*img).load("Lenna_hat_mask.pgm");
//        REQUIRE((*img).getWidth() == 512);
//        REQUIRE((*img).getHeight() == 512);
//
//        (*img).load("Lenna_standard.pgm");
//        REQUIRE((*img).getWidth() == 512);
//        REQUIRE((*img).getHeight() == 512);
//
//        (*img).load("shrek_rectangular.pgm");
//        REQUIRE((*img).getWidth() == 1280);
//        REQUIRE((*img).getHeight() == 1207);
//
//        delete img;
//
//    }
//    SECTION("Saving"){
//        std::string filename= "donkey_mask.pgm";
//        Image img2 = Image(filename);
//        (img2).save("Clone2.pgm");
//        unsigned char *data = img2.getData();
//        //delete img2;
//        ifstream ifs(filename, ios::binary|ios::ate);
//        ifstream::pos_type pos = ifs.tellg();
//        int length = pos;
//        char *pChars = new char[length];
//        ifs.read(pChars, length);
//        ifs.close();
//
//        ifstream ifs2("Clone2.pgm", ios::binary|ios::ate);
//        ifstream::pos_type pos2 = ifs2.tellg();
//        int length2 = pos;
//        char *pChars2 = new char[length2];
//        ifs2.read(pChars2, length2);
//        ifs2.close();
//        REQUIRE(length == length2);
//        int n = memcmp(pChars,pChars2,length); //Compares two blocks of memory, if n ==0 then identical
//        REQUIRE(n ==0);
//
//    }
//
//
//}
//
//TEST_CASE("Image class constructors") {
//    string filename= "donkey_mask.pgm";
//    string filename2 = "Lenna_hat_mask.pgm";
//
//    SECTION("Default Constructor"){
//        //First constructor - param filename
//        Image img = Image(filename);
//        REQUIRE((img).getWidth() == 1280);
//        REQUIRE((img).getHeight() == 1207);
//
//        //Default constructor - no params
//        Image defImg = Image();
//        REQUIRE((defImg).getWidth() == 0);
//        REQUIRE((defImg).getHeight() == 0);
//    }
//    SECTION("Destructor"){
//        cout<<"Begin destructor test"<<endl;
//        Image *img = new Image(filename);
//        delete img;
////            REQUIRE(img->getHeight() == 0);
////            REQUIRE(img->getWidth() == 0);
//        //todo  fix this - destructor test
//    }
//
//    SECTION("Copy Constructor"){
//        Image orig = Image(filename2);
//        Image copy(orig);
//        REQUIRE(orig.getWidth() == copy.getWidth());
//        REQUIRE(orig.getHeight() == copy.getHeight());
//        REQUIRE(strcmp( (const char *) orig.getData(),(const char *) copy.getData()) == 0 );//Makes sure data is the same
//
//    }
//    SECTION("Copy Assignment Operator Constructor"){
//        Image orig = Image(filename2);
//        Image copy = orig;
//        REQUIRE(orig.getWidth() == copy.getWidth());
//        REQUIRE(orig.getHeight() == copy.getHeight());
//        REQUIRE(strcmp( (const char *) orig.getData(),(const char *) copy.getData()) == 0 );//Makes sure data is the same
//
//    }
//    SECTION("Move Constructor"){
//        Image orig = Image(filename2);
//        Image clone = orig;
//        Image movedCopy(move(orig));
//
//        //Check if has same values the original had
//        REQUIRE(clone.getWidth() == movedCopy.getWidth());
//        REQUIRE(clone.getHeight() == movedCopy.getHeight());
//        REQUIRE(strcmp( (const char *) movedCopy.getData(),(const char *) clone.getData()) == 0 );//Makes sure data is the same
//
//        //Checks original is empty
//        REQUIRE(orig.dataNotEmpty() == false);
//
//    }
//
//    SECTION("Move Assignment Operator Constructor"){
//        Image orig = Image(filename2);
//        Image clone = orig;
//        Image movedCopy;
//        movedCopy.operator=(move(orig));
//
//        //Check if has same values the original had
//        REQUIRE(clone.getWidth() == movedCopy.getWidth());
//        REQUIRE(clone.getHeight() == movedCopy.getHeight());
//        REQUIRE(strcmp( (const char *) movedCopy.getData(),(const char *) clone.getData()) == 0 );//Makes sure data is the same
//
//        //Checks original is empty
//        REQUIRE(orig.dataNotEmpty() == true); //todo fix this should be false
//
//    }
//
//}
//TEST_CASE("Image class Iterator and its operators"){
//    string filename= "donkey_mask.pgm";
//    string filename2 = "Lenna_standard.pgm";
//    Image img  = Image(filename2);
//
//    SECTION("Iterator begin() and end() methods"){
//        //Begin should point to the char at the beginning of the array
//        Image::iterator iterator1 = img.begin();
//        unsigned char* iteratorDataP = *iterator1;
//        unsigned char iteratorData = iteratorDataP[0];
//        unsigned char elementInMainData = img.getData()[0];
//        REQUIRE(iteratorData == elementInMainData);
//
//        //End should point to the char at the end of the array
//        Image::iterator iterator2 = img.end();
//        unsigned char* iteratorDataP2 = *iterator2;
//        unsigned char iteratorData2 = iteratorDataP2[0];
//        unsigned char elementInMainData2 = img.getData()[img.getWidth() * img.getHeight()-1];
//        REQUIRE(iteratorData2 == elementInMainData2);
//
//    }
//    SECTION("Iterator constructor and * operator"){
//        Image::iterator iterator1 = img.begin();
//        int n = memcmp(img.getData(),*iterator1,img.getWidth()*img.getHeight());
//        unsigned char *data = img.getData();
//        REQUIRE(n == 0 );//Makes sure data is the same
//        REQUIRE(img.getData() == *iterator1);
//    }
//    SECTION("Iterator copy operator"){
//        Image::iterator iterator1 = img.begin();
//        Image::iterator iterator2 = iterator1;
//        iterator2 = iterator1;
//        REQUIRE(*iterator1 == *iterator2); //Checks if the data inside or the same
//    }
//    SECTION("Iterator move operator"){
//        Image::iterator iterator1 = img.begin();
//        unsigned char * storeOrginalBeforeMove = *iterator1;
//        Image::iterator iterator2 = iterator1;
//        iterator2 = move(iterator1);
//        REQUIRE(storeOrginalBeforeMove == *iterator2); //Checks if the data inside or the same
//        REQUIRE(*iterator1 == nullptr); //Iterator should now empty since moved out data
//    }
//
//    SECTION("++ Iterator"){
//        Image::iterator iterator1 = img.begin();
//        unsigned char* data = img.getData();
//        int countIfEqual = 0;
//        int countNotEqual = 0;
//        for (int i = 0; i < (img.getHeight()*img.getWidth()); ++i) {
//            unsigned char elementInMainData = data[i];
//            unsigned char* iteratorDataP = *iterator1;
//            unsigned char iteratorData = iteratorDataP[0];
//            if (elementInMainData == iteratorData){ //Had REQUIRE here but accumalted to too many assertions in test
//                countIfEqual++;
//            }
//            else{
//                countNotEqual++;
//                cout<<"Not equal"<<endl;
//            }
//            ++iterator1;
//        }
//        cout<<"Not equal this many times: "<<countNotEqual<<endl;
//        //Test if counter is equal to total number of elements in array
//        REQUIRE(countIfEqual == (img.getHeight()*img.getWidth()));
//    }
//    SECTION("-- Iterator"){
//        Image::iterator iterator1 = img.end();
//        unsigned char* data = img.getData();
//        int countIfEqual = 0;
//        for (int i = (img.getHeight()*img.getWidth()); i >0; --i) {
//            unsigned char elementInMainData = data[i-1];
//            unsigned char* iteratorDataP = *iterator1;
//            unsigned char iteratorData = iteratorDataP[0];
//            if (elementInMainData == iteratorData){ //Had REQUIRE here but accumalted to too many assertions in test
//                countIfEqual++;
//            }
//            --iterator1;
//        }
//        //Test if counter is equal to total number of elements in array
//        REQUIRE(countIfEqual == (img.getHeight()*img.getWidth()));
//    }
//
//}
//TEST_CASE("Addition and subtraction of images"){
//    string filename= "Lenna_standard.pgm";
//    string filename2 = "Lenna_hat_mask.pgm";
//    Image img  = Image(filename2);
//    Image img2 = Image(filename);
//    SECTION("Addition test"){
//        Image addedImage = Image();
//        addedImage= img+img2; //Add images together
//        unsigned char * addedData = addedImage.getData(); //Get data var to test against
//        unsigned char * image1Data = img.getData();
//        unsigned char * image2Data = img2.getData();
//        int additionCorrectCounter = 0;
//        int loopTill = 100/*img.getWidth() * img.getHeight()*/;
//        for (int i = 0; i < loopTill; ++i) {
//            unsigned char expectedAddedValue = addedData[i];
//            unsigned char image1Val = image1Data[i];
//            unsigned char image2Val = image2Data[i];
//            if ((image1Val + image2Val)>255 ){ //If addition greater than 255, should be 255
//                if (expectedAddedValue == 255)
//                    additionCorrectCounter++;
//            }
//            else if (expectedAddedValue == (image1Val + image2Val)){ //Check addition correct
//                additionCorrectCounter++;
//            }
//        }
//        REQUIRE(additionCorrectCounter == loopTill/*(img.getWidth() + img.getHeight())*/ );
//    }
//    SECTION("Subtraction test"){
//        Image addedImage = Image();
//        addedImage= img-img2; //Add images together
//        unsigned char * addedData = addedImage.getData(); //Get data var to test against
//        unsigned char * image1Data = img.getData();
//        unsigned char * image2Data = img2.getData();
//        int additionCorrectCounter = 0;
//        int loopTill = 100; //Run tests until - ensures a large number of values are correct
//        for (int i = 0; i < loopTill; ++i) {
//            unsigned char expectedAddedValue = addedData[i];
//            unsigned char image1Val = image1Data[i];
//            unsigned char image2Val = image2Data[i];
//            if ((image1Val - image2Val)<0 ){ //If addition greater than 255, should be 255
//                if (expectedAddedValue == 0)
//                    additionCorrectCounter++;
//            }
//            else if (expectedAddedValue == (image1Val - image2Val)){ //Check addition correct
//                additionCorrectCounter++;
//            }
//            else{
//                cout<<"not equal"<<endl;
//            }
//        }
//        REQUIRE(additionCorrectCounter == loopTill/*(img.getWidth() + img.getHeight())*/ );
//    }
//
//}
//
//TEST_CASE("Thresholding, inverting and masking operator overloads"){
//    string filename= "Lenna_standard.pgm";
//    string filename2 = "Lenna_hat_mask.pgm";
//    Image img  = Image(filename2);
//    Image img2 = Image(filename);
//
//    SECTION("Inverse Test"){
//        Image copyOfOrig(img2);
//        Image inverse = !copyOfOrig;
//        unsigned char * testAry = inverse.getData();
//        int countIfInverse = 0;
//        Image::iterator iteratorOfOrig = img2.begin();
//        for (Image::iterator i = inverse.begin(); i != inverse.end(); ++i) {
//            if (*(*i) == (255 - *(*iteratorOfOrig))){
//                countIfInverse++;
//            }
//            ++iteratorOfOrig;
//        }
//        REQUIRE(countIfInverse == 262000); //If equal to total length of char array then correct
//    }
//
//    SECTION("Mask test"){
//        Image masking = img2/img;
//        unsigned char * nvdjndv = masking.getData();
//        bool maskValid = true;
//        for (int i = 0; i < img.getWidth()*img.getHeight(); ++i) {
//            if ( (img2.getData()[i]) ==255){
//                if (masking.getData()[i] != img2.getData()[i]){
//                    maskValid = false;
//                }
//            }else if (masking.getData()[i] !=0){
//                maskValid = false;
//            }
//        }
//        REQUIRE(maskValid == true);
//    }
//    SECTION("Threshold test"){
//        Image thresheld = img*10;
//        unsigned char * nvdjndv = thresheld.getData();
//        bool thresholdValid = true;
//        for (Image::iterator i = thresheld.begin(); i != thresheld.end(); ++i) {
//            if ( ( *(*i ) != 0 ) && ( *(*i ) != 255 ) ){ //Image pixels should only be 0 or 255
//                thresholdValid = false;
//            }
//        }
//        REQUIRE(thresholdValid == true);
//    }
//
//}
//
//TEST_CASE("Filtering operator on Image"){
//
//}
