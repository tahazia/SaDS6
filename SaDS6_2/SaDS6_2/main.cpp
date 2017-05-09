//
//  main.cpp
//  SaDS6_2
//
//  Created by Taha Zia on 08/05/2017.
//  Copyright © 2017 Taha Zia. All rights reserved.
//

#include <iostream>
#include "SymEnc.h"
#include <string>
#include <ctime>
#include <cstdlib>
#include <fstream>


using namespace std;


int main(int argc, const char * argv[]) {
    std::vector<char> data;
    ifstream input;
    ofstream outputCBC;
    
    input.open("random.png", ios::binary);
    if(!input.is_open()){
        cerr<<"Unable to open input file"<<endl;
        exit(1);
    }
    
    string content( (std::istreambuf_iterator<char>(input) ),
                   (std::istreambuf_iterator<char>()) );
    
    CBC Encryption(content, 170, 38950);
    
    input.close();
    
    outputCBC.open("outputCBC.png",ios::binary);
    if(!outputCBC.is_open()){
        cerr<<"Unable to open output file"<<endl;
        exit(1);
    }
    outputCBC<<Encryption.getData();
    
    outputCBC.close();
    
    ofstream outputTBC;
    outputTBC.open("outputTBC.png", ios::binary);
    if(!outputTBC.is_open()){
        cerr<<"Unable to open output file"<<endl;
        exit(1);
    }
    
    TBC trivialEncryption(content,38950);
    outputTBC<<trivialEncryption.getData();
    
    
    outputTBC.close();
    
    return 0;
}
