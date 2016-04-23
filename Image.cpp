//
// Created by Shaaheen on 4/17/2016.
//

#include <fstream>
#include <iostream>
#include <sstream>
#include <string.h>
#include "Image.h"
using namespace std;

namespace SCRSHA001{
    Image::iterator::iterator(const Image::iterator &rhs): ptr(rhs.ptr) { }

    Image::iterator::iterator(unsigned char *p): ptr(p) { }
    Image::iterator& Image::iterator::operator=(const Image::iterator &rhs) {
        ptr = (rhs.ptr);
        return *this;
    }
    Image::iterator& Image::iterator::operator=(Image::iterator &&rhs) {
        ptr = (move(rhs.ptr));
        rhs.ptr = nullptr;
    }


    Image::Image() {
        height =0;
        width =0;
    }

    Image::Image(std::string &fileName) {
        load(fileName);
    }
    Image::Image(unsigned char *dataInput,int width, int height) {
        this->width = width;
        this->height = height;
        data.reset(dataInput);
    }

    Image::~Image() {
        width =0;
        height =0;
        data.release();
    }

    Image::Image(const Image &rhs) : width(rhs.width),height(rhs.height) {
        unsigned char copyData[width*height];
        strcpy((char *) copyData, (const char *) rhs.data.get());
        data.reset(copyData);
    }

    Image::Image(Image &&rhs): width(move(rhs.width)),height(move(rhs.height)){
        //data.reset(move(rhs.data).get());
        data.swap(rhs.data);
    }

    Image &Image::operator=(const Image &rhs) {
        width = rhs.width;
        height = rhs.height;
        data.reset(rhs.data.get());
        return *this;
    }

    Image &Image::operator=(const Image &&rhs) {
        //cout<<"Move op called"<<endl;
        width = move(rhs.width);
        height = move(rhs.height);
        data.reset(move(rhs.data).get());
        return *this;
    }

    int Image::getWidth() const {
        return this->width;
    }

    int Image::getHeight() const{
        return this->height;
    }
    bool Image::dataNotEmpty() const{
        if (data){
            return true;
        }else{
            return false;
        }
    }

    bool Image::load(string inFileName) {
        //todo make << and >> ops to get the header info
        ifstream input(inFileName,ios::binary | ios::in);
        string line;
        int width;
        int height;
        int count = 0;
        if (input.is_open()){
            while(getline(input,line)){
                //input.read(reinterpret_cast<char *>(&p), sizeof(int));
                if (line.at(0) != '#'){
                    count++;
                    if (count ==2){ //rows and columns in this line
                        stringstream ss;
                        ss<<line;
                        ss>>width;
                        ss>>height;
                    }
                }
                if (count ==3){
                    break;
                }
            }
        }else{
            cout<<"Unable to open file"<< endl;
        }
        this->height = height;
        this->width = width;

        unsigned char* mainData= new unsigned char[width*height];
        input.read((char *) mainData, width * height);

        (this->data).reset(mainData);

        input.close();
        return false;
    }


    //Save function to store pgm file
    bool Image::save(std::string outFileName) {
        ofstream output(outFileName); //Open file
        if (output.is_open()){
            string header = "P5\n" + to_string(width) + " " + to_string(height) +"\n255\n"; //Header info
            const char* bytesInHeader = header.c_str();
            output.write(bytesInHeader,header.length()); //Write header info as chars
            output.write((const char *) data.get(), width * height); //Write all the unsigned char data to file
            output.close();
            return true;
        }
        else{
            return false;
        }


    }

    unsigned char *Image::getData() const {
        return data.get();
    }

    Image::iterator Image::begin(void)const {
        return Image::iterator(data.get());
    }

    Image::iterator Image::end(void)const {
        return Image::iterator((data.get()+(width*height)-1)); //offset to end of array
    }

    unsigned char *&Image::iterator::operator*() {
            return ptr;
    }

    Image::iterator & Image::iterator::operator++() {
        ptr = (ptr + 1); //todo check if working
        return *this;
    }

    Image::iterator & Image::iterator::operator--() {
        ptr = (ptr - 1);
        return *this;
    }

    Image Image::operator+(const Image & rhs) const {
        Image addedImage(*this);
        addedImage += rhs;
        return addedImage;
    }

    Image &Image::operator+=(const Image &rhs) {
        if (this->getWidth() != rhs.getWidth() || this->getHeight() != rhs.getHeight()){
            cout<<"Image parameters not equal!"<<endl;
            exit(0);
        }
        int counter = 0;
        Image::iterator image1 = this->begin(); //Iterator for second image
        //Would loop same amount of times for either image 1 or 2 iterator
        for (Image::iterator image2 = rhs.begin(); image2 != rhs.end(); ++image2) { //Iterator for 1st image
            unsigned char image1Pixel = (*image1)[0];
            unsigned char image2Pixel = (*image2)[0];
            if ( (image1Pixel + image2Pixel) >255){
                //addedImage[counter] =  255;
                *(*image1) = 255;
            }
            else{
                *(*image1) = (image1Pixel + image2Pixel);
                //addedImage[counter] = (image1Pixel + image2Pixel);
            }
            ++counter;
            ++image1;
        }
        return *this;
    }

    bool Image::iterator::operator!=(const Image::iterator &rhs) {
        return (this->ptr != rhs.ptr);
    }

    Image Image::operator-(const Image & rhs) const {
        Image subtractedImage(*this);
        subtractedImage -= rhs;
        return subtractedImage;
    }

    Image &Image::operator-=(const Image &rhs) {
        if (this->getWidth() != rhs.getWidth() || this->getHeight() != rhs.getHeight()){
            cout<<"Image parameters not equal!"<<endl;
            exit(0);
        }
        int counter = 0;
        Image::iterator image1 = this->begin(); //Iterator for second image
        //Would loop same amount of times for either image 1 or 2 iterator
        for (Image::iterator image2 = rhs.begin(); image2 != rhs.end(); ++image2) { //Iterator for 1st image
            unsigned char image1Pixel = (*image1)[0];
            unsigned char image2Pixel = (*image2)[0];
            if ( (image1Pixel - image2Pixel) <0){
                //addedImage[counter] =  255;
                *(*image1) = 0;
            }
            else{
                *(*image1) = (image1Pixel - image2Pixel);
                //addedImage[counter] = (image1Pixel + image2Pixel);
            }
            ++counter;
            ++image1;
        }
        return *this;
    }


    Image Image::operator!() {
        Image inverse(*this);
        for (Image::iterator i = inverse.begin(); i != inverse.end(); ++i) {
            *(*i) = (unsigned char) (255 - (*(*i)));
        }
        unsigned char * nd = inverse.getData();
        return inverse;
    }

    Image Image::operator/(const Image &rhs) const {
        if (this->getWidth() == rhs.width && this->getHeight() ==rhs.width){
            Image mask(*this);

            Image::iterator iteratorMask = mask.begin();
            for (Image::iterator iteratorImage2 = rhs.begin(); iteratorImage2 != rhs.end(); ++iteratorImage2) {
                if ( *(*iteratorImage2) == 0){
                    *(*iteratorMask) = 0;
                }
                ++iteratorMask;
            }
            return mask;
        }
        else{
            cout<<"Mask images not the same size!"<<endl;
            exit(0);
        }
    }

    Image &Image::operator*(const int threshold) {
        return <#initializer#>;
    }
}
