/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symtable.h"
// #include <iostream>
// using namespace std;

SymbolTable::SymbolTable(){
    this->root=new SymEntry();
    this->size=0;
}

SymbolTable::~SymbolTable(){
    // delete root->left;
    // delete root->right;
    // cout<<"Deleting: "<<root->key<<endl;

    SymEntry* temp = root;

    if (root->left==nullptr and root->right==nullptr){
        delete root;
        return;
    }

    if (temp->left!=nullptr){
        root = temp->left;
        this->~SymbolTable();
    }

    if (temp->right!=nullptr){
        root=temp->right;
        this->~SymbolTable();
    }

    delete temp;
}

SymEntry* findSuccessor(SymEntry* root){
    if (root==nullptr) return nullptr;
    root = root->right;
    while (root->left!=nullptr){
        root=root->left;
    }
    return root;
}

SymEntry* addSE(SymEntry* root, string s, UnlimitedRational* v) {
    if (root==nullptr or root->val==nullptr) {SymEntry* temp = new SymEntry(s,v); root=temp; return root;}
    if (s.compare(root->key)<0) {
        if (root->left==nullptr)  {SymEntry* temp = new SymEntry(s,v); root->left=temp;}
        else addSE(root->left,s,v);
    }
    else {
        if (root->right==nullptr)  {SymEntry* temp = new SymEntry(s,v); root->right=temp;}
        else addSE(root->right,s,v);
    }
    return root;
}

void SymbolTable::insert(string s,UnlimitedRational* v){
    SymEntry* ptr = this->get_root();
    root = addSE(ptr,s,v);
    size++;
}

SymEntry* deleteSE(SymEntry* root, string s){
    if (root==nullptr)  return root;
    if (s.compare(root->key)==0){
        if (root->left==nullptr && root->right==nullptr){
            delete root;
            root = nullptr;
        }
        else if (root->left==nullptr){
            SymEntry* temp = root->right;
            delete root;
            root = temp;
        }
        else if (root->right==nullptr){
            SymEntry* temp = root->left;
            delete root;
            root = temp;
        }
        else{
            SymEntry* successor = findSuccessor(root);
            root->key=successor->key;
            root->right=deleteSE(root->right,successor->key);
        }
    }
    else if (root->key.compare(s) > 0) {
        root->left=deleteSE(root->left,s);
    }
    else{
        root->right=deleteSE(root->right,s);
    }
    return root;
}

void SymbolTable::remove(string s){
    root=deleteSE(root,s);
    size--;
}

SymEntry* find(SymEntry* root, string k){
    if(root == nullptr) return nullptr;

    if(k.compare(root->key)==0) return root;
    else if(k.compare(root->key)<0)  return find(root->left, k);
    else return find(root->right, k);
    
    return root;
}

UnlimitedRational* SymbolTable::search(string k){
    SymEntry* found = find(root,k);
    if (found==nullptr) return nullptr;
    else return found->val;
}

SymEntry* SymbolTable::get_root(){
    return root;
}

int SymbolTable::get_size(){
    return size;
}

// int main(){
//     SymbolTable* s = new SymbolTable();
//     UnlimitedInt* one = new UnlimitedInt(1);
//     UnlimitedInt* two = new UnlimitedInt(2);
//     UnlimitedInt* three = new UnlimitedInt(3);
//     UnlimitedInt* four = new UnlimitedInt(4);
//     UnlimitedRational* a = new UnlimitedRational(one,four);
//     UnlimitedRational* b = new UnlimitedRational(two,four);
//     UnlimitedRational* c = new UnlimitedRational(three,two);
//     UnlimitedRational* d = new UnlimitedRational(four,three);
//     UnlimitedRational* e = new UnlimitedRational(two,four);
//     UnlimitedRational* f = new UnlimitedRational(four,two);
//     s->insert("b", b);
//     s->insert("c", c);
//     s->insert("a", a);
//     s->insert("d", d);
//     s->insert("e", e);
//     s->insert("f", f);
//     s->remove("b");
//     cout<<s->search("a")->get_frac_str()<<endl;
//     cout<<s->search("c")->get_frac_str()<<endl;
//     cout<<s->search("d")->get_frac_str()<<endl;

//     delete s;
// }