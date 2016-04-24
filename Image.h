//
// Created by Shaaheen on 4/17/2016.
//

#ifndef ASSIGNMENT_4_SCRSHA001_IMAGE_H
#define ASSIGNMENT_4_SCRSHA001_IMAGE_H


#include <memory>

namespace SCRSHA001 {
    class Image{
    private:
        friend class iterator;
        //friend class ImageTests;


        int width, height;
        std::unique_ptr<unsigned char[]> data;
    public:

        Image();
        Image(std::string &fileName);
        Image(unsigned char * data,int width, int height);
        Image(const Image & rhs); //copy
        Image(Image &&rhs);//move

        Image &operator=(const Image & rhs); //copy assignment
        Image &operator=(const Image && rhs);//move assignmen

        Image operator+(const Image & rhs ) const; //addition operator
        Image &operator+=(const Image & rhs);
        Image operator-(const Image & rhs ) const; //subtraction operator
        Image &operator-=(const Image & rhs);
        Image operator!() ; //Inverse operator
        Image operator/(const Image & rhs ) const; //Mask operator
        Image operator*(const int threshold); //Threshold operator



        virtual ~Image();

        bool load(std::string inFileName);


        void operator>>(const std::string file);
        void operator<<(const std::string file);

        int getWidth() const;

        int getHeight() const;

        bool save(std::string outFileName);

        unsigned char* getData() const;

        class iterator {
        private:

            friend class Image;

            unsigned char *ptr;
            int index;
            // construct only via Image class (begin/end)

            iterator(unsigned char *p);// : ptr(p) {}

        public:
            //copy construct is public
            iterator(const iterator &rhs);

            // define overloaded ops: *, ++, --, =
            iterator &operator=(const iterator &rhs);
            iterator& operator=(iterator &&rhs);

            unsigned char &operator*();
            iterator& operator++();
            iterator& operator--();
            bool operator!=(const iterator &rhs);


            iterator(unsigned char *ptrToData, int givenIndex);
        };

        // define begin()/end() to get iterator to start and
        // "one-past" end.
        iterator begin(void)const;// { return iterator(data.get());} // etc

        iterator end(void)const;

        bool dataNotEmpty() const;

    };
}



#endif //ASSIGNMENT_4_SCRSHA001_IMAGE_H
