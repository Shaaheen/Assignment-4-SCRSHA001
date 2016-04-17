//
// Created by Shaaheen on 4/17/2016.
//

#ifndef ASSIGNMENT_4_SCRSHA001_IMAGE_H
#define ASSIGNMENT_4_SCRSHA001_IMAGE_H


#include <bits/unique_ptr.h>

class Image
{
    private:
        int width, height;
        friend class iterator;
        std::unique_ptr<unsigned char[]> data;
    public:
        class iterator
        {
            private:
                friend class Image;
                unsigned char *ptr;
                // construct only via Image class (begin/end)

                iterator(unsigned char *p) : ptr(p) {}

            public:
                //copy construct is public
                iterator( const iterator & rhs) : ptr(rhs.ptr) {}
                // define overloaded ops: *, ++, --, =
                iterator & operator=(const iterator & rhs)
                {}
                // other methods for iterator
        };
        // define begin()/end() to get iterator to start and
        // "one-past" end.
        iterator begin(void) { return iterator(data.get());} // etc
};



#endif //ASSIGNMENT_4_SCRSHA001_IMAGE_H
