//
// Created by Shaaheen on 4/17/2016.
//

#include <fstream>
#include <iostream>
#include <sstream>
#include "Image.h"
using namespace std;

namespace SCRSHA001{
    Image::iterator::iterator(const Image::iterator &rhs): ptr(rhs.ptr) {

    }

    Image::iterator::iterator(unsigned char *p): ptr(p) {

    }

    Image::Image() { }

    Image::Image(std::string &fileName) {
        load(fileName);
    }

    Image::~Image() { }

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


    int Image::getWidth() {
        return width;
    }

    int Image::getHeight() {
        return height;
    }

    bool Image::save(std::string outFileName) {
        cout<<"Save function call"<<endl;
        ofstream output(outFileName);
        if (output.is_open()){
            string header = "P5\n" + to_string(width) + " " + to_string(height) +"\n255\n";
            const char* bytesInHeader = header.c_str();
            output.write(bytesInHeader,header.length());
            output.write((const char *) data.get(), width * height);
            output.close();
            cout<<"Save function call done"<<endl;
            return true;
        }
        else{
            cout<<"Save function call done"<<endl;
            return false;
        }


    }


}
