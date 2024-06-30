/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symnode.h"

//Write your code below this line

SymNode::SymNode(){
    this->key="";
    this->height=1;
    this->address=-1;
    this->left=NULL;
    this->right=NULL;
    this->par=NULL;
}

SymNode::SymNode(string k){
    this->key=k;
    this->height=1;
    this->address=-1;
    this->left=NULL;
    this->right=NULL;
    this->par=NULL;
}

int get_height(SymNode* root){
    if (root==NULL) return 0;
    return root->height;
}

SymNode* SymNode::LeftLeftRotation(){
    if (this==NULL)  return NULL;
    SymNode* b = this->right;
    b->par=this->par;
    if (this->par!=NULL){
        if (this==this->par->left)  b->par->left=b;
        else b->par->right=b;
    }
    this->par=b;
    if (b->left!=NULL){
        b->left->par = this;
    }
    this->right = b->left;
    b->left = this;

    this->height = max ( get_height(this->left) , get_height(this->right) ) + 1;
    b->height = max( get_height(b->left) , get_height(b->right) ) + 1;
    return b;
}

SymNode* SymNode::RightRightRotation(){
    if (this==NULL) return NULL;
    SymNode* b = this->left;
    b->par=this->par;
    if (this->par!=NULL){
        if (this==this->par->left)  b->par->left=b;
        else b->par->right=b;
    }
    this->par=b;
    if (b->right!=NULL){
        b->right->par = this;
    }
    this->left = b->right;
    b->right = this;

    this->height = max( get_height(this->left), get_height(this->right) ) + 1;
    b->height = max( get_height(b->left) , get_height(b->right) ) + 1;
    return b;
}

SymNode* SymNode::LeftRightRotation(){
    if (this==NULL) return NULL;
    SymNode* rst = this->right;
    rst->RightRightRotation();
    SymNode* ans= this->LeftLeftRotation();
    return ans;
}

SymNode* SymNode::RightLeftRotation(){
    if (this==NULL) return NULL;
    SymNode* lst = this->left;
    lst->LeftLeftRotation();
    SymNode* ans = this->RightRightRotation();
    return ans;
}

SymNode::~SymNode(){
    if (this!=NULL){
        if (this->left!=NULL) this->left->par=NULL;
        this->left=NULL;
        if (this->right!=NULL) this->right->par=NULL;
        this->right=NULL;
        if (this->par!=NULL){
            if (this==this->par->left) this->par->left=NULL;
            else  this->par->right=NULL;
        }
        this->par=NULL;
        // cout<<"deleting: "<<this->key<<endl;
    }
}

// int main(){
//     SymNode* root = new SymNode("d");
//     root->right = new SymNode("c");
//     root->right->par = root;
//     root->right->right = new SymNode("b");
//     root->right->right->par = root->right;
//     root->right->right->right = new SymNode("a");
//     root->right->right->right->par = root->right->right;
//     SymNode* newRoot = root->right->LeftLeftRotation();
//     cout<<newRoot->key<<endl;
//     cout<<newRoot->par->key<<endl;
//     cout<<root->right->key<<endl;
// }