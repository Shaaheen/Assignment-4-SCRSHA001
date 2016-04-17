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

    Image::~Image() { }

    bool Image::load(string inFileName) {
        //todo make << and >> ops to get the header info
        cout<<"Load function called"<<endl;
        ifstream input(inFileName,ios::binary | ios::in);
        char p;
        char x;
        string line;
        int width;
        int height;
        int count = 0;
        if (input.is_open()){
            while(getline(input,line)){
                if (count ==3){
                    break;
                }
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
            }
        }else{
            cout<<"Unable to open file"<< endl;
        }
        cout<<"Height :"<<height<<endl;
        cout<<"Width : "<<width<<endl;

        cout<<"Load function call done"<<endl;
        input.close();
        return false;
    }
}
