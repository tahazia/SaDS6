//
//  SymEnc.cpp
//  SaDS6
//
//  Created by Taha Zia on 08/05/2017.
//  Copyright © 2017 Taha Zia. All rights reserved.
//

#include "SymEnc.h"

char SubCypher::subBox(char c){
    int i = c;
    c = ((i+1)*7)%17 - 1;
    return c;
}

char SubCypher::pBox(char c){
    char pb = c & (64+128);
    pb = pb >> 6;
    pb = pb & 3;
    
    c = c<<2;
    c = c | pb;
    return c;
}

char SubCypher::invpBox(char c){
    int i = c;
    char pb = i & 3;
    pb = pb << 6;
    
    c = c >>2;
    c = c & (1+2+4+8+16+32);
    
    c = c | pb;
    
    
    return c;
}

char SubCypher::keyxor(char c, int k) {
    c ^= k;
    return c;
}

void SubCypher::Encrypt(){
    int k1, k2;
    
    k1 = this->Key>>8;
    k2 = this->Key & 255;
    int k = 0;
    char c= 0, c2 = 0;
    char encrypted = this->data;
    for(int j = 0; j < 2; j++){
        
        c2 = encrypted & 15;
        c = encrypted >> 4;
        c = c & 15;
        
        
        c = subBox(c);
        c2 = subBox(c2);
        
        c = c<<4;
        c = c | c2;
        
        c = pBox(c);
        
        if(j == 0){k = k1;}else if(j == 1){k = k2;}
        c = keyxor(c, k);
        encrypted = c;
    }
    this->data = encrypted;
}

char SubCypher::invsubBox(char c){
    int i = c;
    
    switch (i) {
        case 0:
            c = 4;
            break;
        case 1:
            c = 9;
            break;
        case 2:
            c = 14;
            break;
        case 3:
            c = 2;
            break;
        case 4:
            c = 7;
            break;
        case 5:
            c = 12;
            break;
        case 6:
            c = 0;
            break;
        case 7:
            c = 5;
            break;
        case 8:
            c = 10;
            break;
        case 9:
            c = 15;
            break;
        case 10:
            c = 3;
            break;
        case 11:
            c = 8;
            break;
        case 12:
            c = 13;
            break;
        case 13:
            c = 1;
            break;
        case 14:
            c = 6;
            break;
        case 15:
            c = 11;
            break;
            
        default:
            std::cerr<<"Invalid argument to function"<<std::endl;
            exit(1);
            break;
    }
    return c;
}

void SubCypher::Decrypt(){
    int k1, k2;
    
    k1 = this->Key>>8;
    k2 = this->Key & 255;
    int k = 0;
    char c= 0, c2 = 0;
    char decrypted= this->data;
    for (int j = 1; j >= 0 ; j--){
        
        c = decrypted;
        if(j == 0){k = k1;}else if(j == 1){k = k2;}
        c = keyxor(c, k);
        
        c = invpBox(c);
        
        
        c2 = c & 15;
        c = c >> 4;
        c = c &15;
        
        c= invsubBox(c);
        c2 = invsubBox(c2);
        
        c = c<<4;
        c = c | c2;
        decrypted = c;
    }
    
    this->data = decrypted;
}

SubCypher::SubCypher(char d, int k){
    data = d;
    Key = k;
    Encrypt();
}


CBC::CBC(std::string newdat, int VF, int nkey){
    data = newdat;
    IVF = VF;
    key = nkey;
    this->Encrypt();
}

void CBC::Encrypt(){
    std::string blockEncrypted = this->data;
    int ci[blockEncrypted.size()];
    ci[0] = this->IVF;
    
    
    for(int i = 0; i < blockEncrypted.size(); i++){
        blockEncrypted[i] ^= ci[i];
        this->BlockCyphers.push_back(SubCypher(blockEncrypted[i], this->key));
        blockEncrypted[i]= BlockCyphers[i].getData();
        ci[i+1] = BlockCyphers[i].getData();
    }
    this->data = blockEncrypted;
    
}

void CBC::Decrypt(){
    std::string blockDecrypted = this->data;
    int ci[blockDecrypted.size()];
    ci[0] = this->IVF;
    
    
    for(int i = 0; i < blockDecrypted.size(); i++){
        if(i+1 != blockDecrypted.size()){
            ci[i+1] = blockDecrypted[i];
        }
        BlockCyphers[i].Decrypt();
        blockDecrypted[i] = BlockCyphers[i].getData();
        blockDecrypted[i] ^= ci[i];
    }
    this->data = blockDecrypted;
    
}

std::string CBC::getData(){
    return this->data;
}

void TBC::Encrypt(){
    std::string blockEncrypted = this->data;
    for(int i = 0; i < blockEncrypted.size(); i++){
        this->BlockCyphers.push_back(SubCypher(blockEncrypted[i], this->key));
        blockEncrypted[i]= BlockCyphers[i].getData();
    }
    this->data = blockEncrypted;
    
}

void TBC::Decrypt(){
    std::string blockDecrypted = this->data;
    
    //std::cout<<"blockDecrypting..."<<std::endl;
    for(int i = 0; i < blockDecrypted.size(); i++){
        BlockCyphers[i].Decrypt();
        blockDecrypted[i] = BlockCyphers[i].getData();
    }
    this->data = blockDecrypted;
    
}

TBC::TBC(std::string newdat, int nkey){
    data = newdat;
    key = nkey;
    this->Encrypt();
}



