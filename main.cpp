#include <iostream>
#include <sstream>
#include "Image.h"

using namespace std;

int main(int argc,char* argv[]) {
    //Check if right amount of arguments
    if (argc > 5 ||argc < 3){
        cout << "Incorrect arguments passed (Not enough or too little found) " <<endl;
    }
    else{
        cout<<"Image manipulation program"<<endl;
        //Get file names
        string operation = string(argv[1]);
        if (operation == "-a" || operation == "-s" ||operation == "-l" ){ //Binary operations
            if (argc !=5){
                cout<<"Not enough params"<<endl;
                exit(0);
            }
            string inputImage1 = string(argv[2]);
            string inputImage2 = string(argv[3]);
            string outputFileName = string(argv[4]);
            SCRSHA001::Image img1(inputImage1);
            SCRSHA001::Image img2(inputImage2);
            SCRSHA001::Image imageResult; //Empty constructor
            if (operation == "-a" ){
                cout<<"Addition Op chosen"<<endl;
                 imageResult = img1 + img2; //add
            }
            else if (operation == "-s" ){
                cout<<"Subtract Op chosen"<<endl;
                imageResult = img1 - img2;//subtract
            }
            else{
                cout<<"Mask Op chosen"<<endl;
                imageResult = img1 / img2; //mask
            }

            imageResult >> outputFileName; //print to file
        }
        else if (operation == "-i"){ //inverse op
            if (argc !=4){
                cout<<"Not enough params"<<endl;
                exit(0);
            }
            cout<<"Inverse Op chosen"<<endl;
            string inputImage1 = string(argv[2]);
            string outputFileName = string(argv[3]);
            SCRSHA001::Image img1(inputImage1);
            SCRSHA001::Image inverse = !img1;
            inverse >>outputFileName;
        }
        else if (operation == "-t"){ //threshold op
            if (argc !=5){
                cout<<"Not enough params"<<endl;
                exit(0);
            }
            cout<<"Threshold Op chosen"<<endl;
            string inputImage1 = string(argv[2]);
            stringstream threshString(argv[3]);
            int threshold;
            threshString >>threshold;
            string outputFileName = string(argv[4]);
            SCRSHA001::Image img1(inputImage1);
            SCRSHA001::Image thresheldImg = img1*threshold;
            thresheldImg >>outputFileName;
        }
        else{
            cout<<"Invalid op";
        }
        cout<<"Op complete."<<endl;
        cout<<"Exiting.."<<endl;

    }
    return 0;
}

