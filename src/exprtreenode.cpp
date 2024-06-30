/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "exprtreenode.h"

//Write your code below this line

ExprTreeNode::ExprTreeNode(){
    this->type="";
    this->left=NULL;
    this->right=NULL;
}

ExprTreeNode::ExprTreeNode(string t,int v){
    this->type =t;
    this->num =v;
    this->left=NULL;
    this->right=NULL;
}

ExprTreeNode::~ExprTreeNode(){
    this->left=NULL;
    this->right=NULL;
}

