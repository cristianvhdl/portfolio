As per request from one of my colleagues, I created this simple app to 
improve our sequencing pipeline.  This is meant to be a quick start document.

#Hamming Distance#

ham.cpp - A simple app to compute the hamming distance between a list of
barcodes against each other.

#To compile#

compile code within terminal:
$ g++ ham.cpp hamming_distance

g++ - the compiler
ham.cpp - source code
hamming_distance - executable program (you can name this whatever you'd like)

#To use#

$ ./hamming_distance

for this to work you need a "ref.txt" in the same directory as your executable.
An example would look like the following:

CGCCTTTC
AAAGGAGG
TTGGATCA
GCTCCAAT
ATATGGCA

the program should give you a prompt asking for the number of barcodes:

$ enter the number of barcodes in the "ref.txt" file:

in the example above you would type 5 and hit 'enter'

#Output#

within the same directory, there will be an output file called "out.txt".
this is formatted and can be opened in excel.  output file with conditional 
formatting makes for easy viewing:
![alt text](https://github.com/ktingey/portfolio/blob/master/ham/sample-out-1.png "sample output")
