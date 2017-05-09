//
//  main.cpp
//  SaDS6
//
//  Created by Taha Zia on 08/05/2017.
//  Copyright © 2017 Taha Zia. All rights reserved.
//

#include <iostream>
#include "SymEnc.h"
#include <string>

using namespace std;

int main(int argc, const char * argv[]) {
    string str = "taz";
    
    CBC encryption(str, 170, 38950);
    
    cout << "Original String: " << str << endl;
    
    cout<<"Encrypted version: "<<encryption.getData()<<endl;
    
    encryption.Decrypt();
    
    cout<<"Decrypted back: "<<encryption.getData()<<endl;
    
    
    
    return 0;
}
