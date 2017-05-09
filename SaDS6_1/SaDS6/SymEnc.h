//
//  SymEnc.h
//  SaDS6
//
//  Created by Taha Zia on 08/05/2017.
//  Copyright © 2017 Taha Zia. All rights reserved.
//

#ifndef SymEnc_h
#define SymEnc_h

#include <iostream>
#include <string>
#include <vector>

class SymmetricEncryption
{
public:
    virtual void Encrypt() = 0;
    virtual void Decrypt() = 0;
};

class BlockCipher
{
public:
    virtual void Encrypt(void) = 0;
    virtual void Decrypt(void) = 0;
};


class SubCypher:public BlockCipher{
private:
    char data;
    int Key;
public:
    SubCypher(){data = 0; Key = 0; }
    SubCypher(char d, int k);
    ~SubCypher(){};
    
    //Encrypt and Decrypt Functions:
    void Encrypt(void);
    void Decrypt(void);
    
    
    
    char subBox(char c);
    char invsubBox(char c);
    char pBox(char c);
    char invpBox(char c);
    char keyxor(char c, int k);
    
    char getData(){return this->data;}
    
};


class CBC:public SymmetricEncryption{
private:
    std::string data;
    int IVF;
    int key;
    std::vector<SubCypher> BlockCyphers;
    
public:
    CBC(){ data ="" ,IVF = 0; key = 0;}
    CBC(std::string newdat, int VF, int key);
    ~CBC(){BlockCyphers.clear();};
    void Decrypt();
    void Encrypt();
    
    std::string getData();
};




#endif /* SymEnc_h */
