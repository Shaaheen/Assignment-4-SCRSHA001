//
// Created by Shaaheen on 4/17/2016.
//

#ifndef ASSIGNMENT_4_SCRSHA001_IMAGE_H
#define ASSIGNMENT_4_SCRSHA001_IMAGE_H


#include <memory>
#include "ImageTests.h"

namespace SCRSHA001 {
    class Image{
    private:
        friend class iterator;
        //friend class ImageTests;
        friend class ::ImageTests;


        int width, height;
        std::unique_ptr<unsigned char[]> data;
    public:

        Image();
        Image(std::string &fileName);
        Image(const Image & rhs); //copy
        Image(Image &&rhs);//move

        Image &operator=(const Image & rhs); //copy assignment
        Image &operator=(const Image && rhs);//move assignmen
        virtual ~Image();

        bool load(std::string inFileName);


        friend std::ostream& operator>>(std::ifstream& os, int wh);

        int getWidth() const;

        int getHeight() const;

        bool save(std::string outFileName);

        unsigned char* getData() const;

        class iterator {
        private:
            friend class Image;

            unsigned char *ptr;
            // construct only via Image class (begin/end)

            iterator(unsigned char *p);// : ptr(p) {}

        public:
            //copy construct is public
            iterator(const iterator &rhs);

            // define overloaded ops: *, ++, --, =
            iterator &operator=(const iterator &rhs);
            iterator &operator=(const iterator &&rhs);

            unsigned char* &operator*();
            iterator operator++();



        };

        // define begin()/end() to get iterator to start and
        // "one-past" end.
        iterator begin(void);// { return iterator(data.get());} // etc

        iterator end(void);

        bool dataNotEmpty() const;
    };
}



#endif //ASSIGNMENT_4_SCRSHA001_IMAGE_H
