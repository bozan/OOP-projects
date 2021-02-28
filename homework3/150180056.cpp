/* @ozan18
Student Name: BEYZA OZAN
Student ID: 150180056
Date: 12.05.2020 */

#include "classes.h"
#include <iostream>
#include <string>
#include <cmath>
#include <fstream>

using namespace std;

int main(int argc,char* argv[]){
    
    Network MyNetwork; // create Network object as MyNetwork
    char *myfile = argv[1]; // get files as arguments
    MyNetwork.read_from_file(myfile);
    MyNetwork.print_result();
    
    return 0;
}
