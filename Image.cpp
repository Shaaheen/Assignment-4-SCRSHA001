//
// Created by Shaaheen on 4/17/2016.
//

#include <fstream>
#include <iostream>
#include <sstream>
#include "Image.h"
using namespace std;

namespace SCRSHA001{
    Image::iterator::iterator(const Image::iterator &rhs): ptr(rhs.ptr) { }

    Image::iterator::iterator(unsigned char *p): ptr(p) { }
    Image::iterator& Image::iterator::operator=(const Image::iterator &rhs) {
        ptr = (rhs.ptr);
        return *this;
    }
    Image::iterator& Image::iterator::operator=(const Image::iterator &&rhs) {
        ptr = (move(rhs.ptr));
    }


    Image::Image() {
        height =0;
        width =0;
    }

    Image::Image(std::string &fileName) {
        load(fileName);
    }

    Image::~Image() {
        cout<<"Destructore called"<<endl;
        width =0;
        height =0;
        data.release();
    }

    Image::Image(const Image &rhs) : width(rhs.width),height(rhs.height) {
        data.reset(rhs.data.get());
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

//    std::ostream &SCRSHA001::operator>>(std::ifstream &input, int wh) {
//        string line;
//        int count;
//        return <#initializer#>;
//    }

    bool Image::load(string inFileName) {
        //todo make << and >> ops to get the header info
        cout<<"Load function called"<<endl;
        ifstream input(inFileName,ios::binary | ios::in);
        string line;
        int width;
        int height;
        int count = 0;
        if (input.is_open()){
            while(getline(input,line)){
                //input.read(reinterpret_cast<char *>(&p), sizeof(int));
                if (line.at(0) != '#'){
                    cout<<line<<endl;
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

        cout<<"Height :"<<height<<endl;
        cout<<"Width : "<<width<<endl;

        (this->data).reset(mainData);

        cout<<"Load function call done"<<endl;
        input.close();
        return false;
    }


    //Save function to store pgm file
    bool Image::save(std::string outFileName) {
        cout<<"Save function call"<<endl;
        ofstream output(outFileName); //Open file
        if (output.is_open()){
            string header = "P5\n" + to_string(width) + " " + to_string(height) +"\n255\n"; //Header info
            const char* bytesInHeader = header.c_str();
            output.write(bytesInHeader,header.length()); //Write header info as chars
            output.write((const char *) data.get(), width * height); //Write all the unsigned char data to file
            output.close();
            cout<<"Save function call done"<<endl;
            return true;
        }
        else{
            cout<<"Save function call done"<<endl;
            return false;
        }


    }

    unsigned char *Image::getData() const {
        return data.get();
    }

    Image::iterator Image::begin(void) {
        return Image::iterator(data.get());
    }

    Image::iterator Image::end(void) {
        return Image::iterator((data.get()+(width*height))); //offset to end of array
    }
}
