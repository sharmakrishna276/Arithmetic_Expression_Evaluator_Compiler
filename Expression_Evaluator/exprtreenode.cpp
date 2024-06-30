/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "exprtreenode.h"

ExprTreeNode::ExprTreeNode(){
    this->type = "";
    this->val = new UnlimitedRational();
    this->evaluated_value = new UnlimitedRational();
    this->left = nullptr;
    this->right=nullptr;
}

ExprTreeNode::ExprTreeNode(string t, UnlimitedInt* v){
    this->type = t;
    this->val = new UnlimitedRational(v,new UnlimitedInt(1));
    this->evaluated_value = new UnlimitedRational(new UnlimitedInt(), new UnlimitedInt(1));
    this->left = nullptr;
    this->right=nullptr;
}

ExprTreeNode::ExprTreeNode(string t, UnlimitedRational* v){
    this->type = t;
    this->val = v;
    this->evaluated_value = new UnlimitedRational(new UnlimitedInt() , new UnlimitedInt(1));
    this->left = nullptr;
    this->right= nullptr;
}

ExprTreeNode::~ExprTreeNode(){
    this->left=nullptr;
    this->right=nullptr;
    delete this->val;
    delete this->evaluated_value;
}