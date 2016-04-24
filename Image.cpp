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
    Image::iterator::iterator(const Image::iterator &rhs): ptr(rhs.ptr),index(rhs.index) { } //copy

    Image::iterator::iterator(unsigned char *p): ptr(p), index(0){ } //constructor
    Image::iterator& Image::iterator::operator=(const Image::iterator &rhs) { //copy assignment
        index = rhs.index;
        ptr = (rhs.ptr);
        return *this;
    }
    Image::iterator& Image::iterator::operator=(Image::iterator &&rhs) { //move assignmen
        index = rhs.index;
        ptr = (move(rhs.ptr));
        rhs.ptr = nullptr;
    }

    Image::iterator::iterator(unsigned char *ptrToData, int givenIndex) : ptr(ptrToData),index(givenIndex){ }

    Image::Image() { //default constructo
        height =0;
        width =0;
    }

    Image::Image(std::string &fileName) {//constructor with filename
        this->width =0;
        this->height =0;
        load(fileName);
    }
    Image::Image(unsigned char *dataInput,int width, int height) {
        this->width = width;
        this->height = height;
        data.reset(dataInput);
    }

    Image::~Image() { //destructor
        width =0;
        height =0;
        data.release();
    }

    //Copy constructor
    Image::Image(const Image &rhs) : width(rhs.width),height(rhs.height) {
        unsigned char copyData[width*height];
        strcpy((char *) copyData, (const char *) rhs.data.get());
        data.reset(copyData);
    }

    //Move consructor
    Image::Image(Image &&rhs): width(move(rhs.width)),height(move(rhs.height)){
        //data.reset(move(rhs.data).get());
        data.swap(rhs.data);
    }

    //Copy assignment
    Image &Image::operator=(const Image &rhs) {
        width = rhs.width;
        height = rhs.height;
        unsigned char copyData[width*height];
        strcpy((char *) copyData, (const char *) rhs.data.get());
        data.reset(copyData);
        return *this;
    }

    //Move assignment
    Image &Image::operator=(const Image &&rhs) {
        width = move(rhs.width);
        height = move(rhs.height);
        data.reset(move(rhs.data).get());
        //rhs.data.release();
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

    //Load function
    bool Image::load(string inFileName) {
        ifstream input(inFileName,ios::binary | ios::in); //get file in binary
        string line;
        int width;
        int height;
        int count = 0;
        if (input.is_open()){
            while(getline(input,line)){
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
            return false;
        }
        this->height = height;
        this->width = width;

        unsigned char *mainData = new unsigned char[width * height];
        input.read((char *) mainData, width * height); //read in all of main data at once
        this->data = unique_ptr<unsigned char[]>(mainData);
        //(this->data).reset(mainData); //store in unique pointer

        input.close();
        return true;
    }


    //Save function to store pgm file
    bool Image::save(std::string outFileName) {
        ofstream output(outFileName, ios::out | ios::binary); //Open file
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

    //Binary I/O operators
    void Image::operator>>(const string file){
        this->save(file);
    }
    void Image::operator<<(const string file){
        this->load(file);
    }

    unsigned char *Image::getData() const {
        return data.get();
    }

    Image::iterator Image::begin(void)const {
        return Image::iterator(data.get());
    }

    Image::iterator Image::end(void)const {
        return Image::iterator((data.get()),width*height); //offset to end of array
    }

    unsigned char &Image::iterator::operator*() { //return pointer to wherever it is currently pointing too
            return ptr[index];
    }

    //Increment op
    Image::iterator & Image::iterator::operator++() {
        ++index;
        //ptr = (ptr + 1); //Point to the next element in memory which should be the next element in the array
        return *this;
    }

    //Decrement op
    Image::iterator & Image::iterator::operator--() {
        //ptr = (ptr - 1);
        --index;
        return *this;
    }

    //Add images together
    Image Image::operator+(const Image & rhs) const {
        Image addedImage(*this); //make copy of original and modify it
        addedImage += rhs; //add rhs to copy
        return addedImage;
    }

    //Add and increments an image
    Image &Image::operator+=(const Image &rhs) {
        if (this->getWidth() != rhs.getWidth() || this->getHeight() != rhs.getHeight()){
            cout<<"Image parameters not equal!"<<endl;
            exit(0);
        }
        int counter = 0;
        Image::iterator image1 = this->begin(); //Iterator for second image
        //Would loop same amount of times for either image 1 or 2 iterator
        for (Image::iterator image2 = rhs.begin(); image2 != rhs.end(); ++image2) { //Iterator for 1st image
            unsigned char image1Pixel = *image1;
            unsigned char image2Pixel = (*image2);
            if ( (image1Pixel + image2Pixel) >255){ //cap pixels at 255
                (*image1) = 255;
            }
            else{
                (*image1) = (image1Pixel + image2Pixel); //add pixels
            }
            ++counter;
            ++image1;
        }
        return *this;
    }

    //Not equal to op for iterator
    bool Image::iterator::operator!=(const Image::iterator &rhs) {
        return (this->index != rhs.index);
    }

    //Subtract op for images
    Image Image::operator-(const Image & rhs) const {
        Image subtractedImage(*this);
        subtractedImage -= rhs;
        return subtractedImage;
    }

    //Subtracts pixels from one image  by another
    Image &Image::operator-=(const Image &rhs) {
        if (this->getWidth() != rhs.getWidth() || this->getHeight() != rhs.getHeight()){
            cout<<"Image parameters not equal!"<<endl;
            exit(0);
        }
        int counter = 0;
        Image::iterator image1 = this->begin(); //Iterator for second image
        //Would loop same amount of times for either image 1 or 2 iterator
        for (Image::iterator image2 = rhs.begin(); image2 != rhs.end(); ++image2) { //Iterator for 1st image
            unsigned char image1Pixel = (*image1);
            unsigned char image2Pixel = (*image2);
            if ( (image1Pixel - image2Pixel) <0){
                (*image1) = 0;
            }
            else{
                (*image1) = (image1Pixel - image2Pixel); //subtract pixels
            }
            ++counter;
            ++image1;
        }
        return *this;
    }

    //Inverse op
    Image Image::operator!() {
        Image inverse(*this);
        unsigned char * j = this->getData();
        unsigned char * x = inverse.getData();
        int counter = 0;
        for (Image::iterator i = inverse.begin(); i != inverse.end(); ++i) {
            (*i) = (unsigned char) (255 - (*i)); //inverse pixel
            //inverse.getData()[i.index] = (unsigned char) (255 - inverse.getData()[i.index]);
            counter++;
        }
        return inverse;
    }

    //Masking op
    Image Image::operator/(const Image &rhs) const {
        if (this->getWidth() == rhs.width && this->getHeight() ==rhs.height){ //Parameter check
            Image mask(*this);

            Image::iterator iteratorMask = mask.begin();
            for (Image::iterator iteratorImage2 = rhs.begin(); iteratorImage2 != rhs.end(); ++iteratorImage2) {
                if ( (*iteratorImage2) == 0){ //if img 2 255 then set to 0
                    (*iteratorMask) = 0;
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

    //Threshold op
    Image Image::operator*(const int threshold) {
        Image thresheldImage(*this);
        for (Image::iterator i = thresheldImage.begin(); i != thresheldImage.end(); ++i) {
            if ( (*i) > threshold){ //if pixel larger than threshold then set to cap at 255
                (*i) = 255;
            }
            else{
                (*i) = 0; //if not, set to 0
            }
        }
        return thresheldImage;
    }


}
