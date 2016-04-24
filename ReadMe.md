Hey :)

To run: 
    1) Go into directory from terminal
    2) Run "make" command in terminal to compile the program
    3) run ./imageOps [-a image1 image2 output_file_name] OR
						[-s image1 image2 output_file_name] OR
						[-i image1 output_file_name] OR
						[-l image1 image2 output_file_name] OR
						[-t image1 thresholdInt output_file_name]
						command from terminal
	4) Program should create a new image file in the directory
	
To run unit tests:
	1) Go into test directory from terminal
	2) Run "make" command in terminal to compile unit test program
	3) run ./unitTests command from terminal
	4) Should execute all tests
	
eg: ./imageOps -t Lenna_standard.pgm 100 #The image this creates is pretty cool too :)

Choose only one of the arguments above; either -a, -s, -i, -l or -t.

-a i j output_file_name :
						-a =  addition of two Image objects (pixels of each added)
						i = first fileName ;
						j = second fileName
						output_file_name = name of the output file that will be created
						
-s i j output_file_name :
						-s =  subtraction of two Image objects (pixels of each differenced)
						i = first fileName ;
						j = second fileName
						output_file_name = name of the output file that will be created

-i fileName output_file_name :
						-i =  Inverse of Image object (pixels inversed -> 255 - pixel)
						fileName = file to Inverse;
						output_file_name = name of the output file that will be created
						
-l i j output_file_name :
						-l =  Creates mask of two Image objects (Masks main image into other images mask)
						i = first fileName ;
						j = second fileName
						output_file_name = name of the output file that will be created
	
-t i thresholdInt output_file_name :
						-t =  Create threshold cap on images (pixels capped)
						i = first fileName ;
						thresholdInt = threshold cap for image
						output_file_name = name of the output file that will be created

Image.cpp :
	Implementation of the Image class 
	Allows for operations - add, subtract, mask, inverse, threshold
	
main.cpp:
	Driver class to run program

Image.h:
	Header file for the VolImage class declarations
	
test\ImageTests.cpp:
	Implementation of Unit tests to evaluate Image object
	
test\ImageTests.h:
	Header file for unit tests

	