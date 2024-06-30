/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "entry.h"
// #include <iostream>
// using namespace std;

SymEntry::SymEntry(){
    this->val = nullptr;
    this->key="";
    this->left=nullptr;
    this->right=nullptr;
}

SymEntry::SymEntry(string k, UnlimitedRational* v){
    this->left=nullptr;
    this->right=nullptr;
    this->key=k;
    this->val=v;
}

SymEntry::~SymEntry(){
    this->left = nullptr;
    this->right =  nullptr;
    // cout<<"Deleting: "<<this->key<<endl;
    if(this->val)
    delete this->val;
}