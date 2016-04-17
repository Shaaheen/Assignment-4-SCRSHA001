//
// Created by Shaaheen on 4/17/2016.
//

#include "Image.h"

Image::iterator::iterator(const Image::iterator &rhs): ptr(rhs.ptr) {

}

Image::iterator::iterator(unsigned char *p): ptr(p) {

}

Image::Image() { }

Image::~Image() { delete data;}
