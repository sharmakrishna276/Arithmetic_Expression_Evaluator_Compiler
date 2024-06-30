/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "evaluator.h"
#include <iostream>
using namespace std;

Evaluator::Evaluator(){
    symtable = new SymbolTable();
}

void del_expr_tree(ExprTreeNode* root){
    ExprTreeNode* temp = root;

    if (root->left==nullptr and root->right==nullptr){
        delete root;
        return;
    }

    if (temp->left!=nullptr){
        root = temp->left;
        del_expr_tree(root);
    }

    if (temp->right!=nullptr){
        root=temp->right;
        del_expr_tree(root);
    }

    delete temp;
}

Evaluator::~Evaluator(){
    delete symtable;
    for (auto i: expr_trees){
        del_expr_tree(i);
    }
}


// Evaluator::~Evaluator(){
//     // // symtable->~SymbolTable();
//     // delete symtable;
//     // for (auto i: expr_trees){
//     //     // i->~ExprTreeNode();
//     //     delete i;
//     // }
// }

bool is_int(string str)
{
    if (str[0]!='-'){
        if (str[0]<48 or str[0]>57) return false;
    }
    for (int i=1;i<int(str.length());i++) {
        if (!(str[i] >= 48 && str[i] <= 57)) {
            return false;
        }
    }
    return true;
}

void Evaluator::parse(vector<string> code){
    vector<string> stack_1; //parantheses and operators
    vector<ExprTreeNode*> stack_2; //nodes
    ExprTreeNode* root = new ExprTreeNode(":=",new UnlimitedRational());  //root
    ExprTreeNode* var = new ExprTreeNode("VAR",new UnlimitedRational());  //root->left
    var->id = code[0];
    root->left = var;

    for (int i=0;i<2;i++){
        vector<string>::iterator it = code.begin();
        code.erase(it);
    }

    for (string i:code){
        if (i=="+" or i=="-" or i=="*" or i=="/" or i=="("){  
            //push operators and left bracket into stack_1
            stack_1.push_back(i);
        }
        else if (i==")"){
            // keep pushing nodes to stack_2 till left parantheses is reached
            while (stack_1[stack_1.size()-1]!="("){
                // right subtree
                ExprTreeNode* right = stack_2[stack_2.size()-1];  stack_2.pop_back();

                //left subtree
                ExprTreeNode* left = stack_2[stack_2.size()-1]; stack_2.pop_back();

                //operation
                string temp = stack_1[stack_1.size()-1];  stack_1.pop_back();

                //creating node and pushing it to stack_2
                if (temp=="+"){
                    ExprTreeNode* sym = new ExprTreeNode("ADD",new UnlimitedRational());
                    sym->left = left;
                    sym->right = right;
                    stack_2.push_back(sym);
                }
                else if (temp=="-"){
                    ExprTreeNode* sym = new ExprTreeNode("SUB",new UnlimitedRational());
                    sym->left = left;
                    sym->right = right;
                    stack_2.push_back(sym);
                }
                else if (temp=="*"){
                    ExprTreeNode* sym = new ExprTreeNode("MUL",new UnlimitedRational());
                    sym->left = left;
                    sym->right = right;
                    stack_2.push_back(sym);
                }
                else if (temp=="/"){
                    ExprTreeNode* sym = new ExprTreeNode("DIV",new UnlimitedRational());
                    sym->left = left;
                    sym->right = right;
                    stack_2.push_back(sym);
                }

            }

            // remove the left parantheses
            stack_1.pop_back();
        }
        else{
            // string is either variable or number
            string temp = i;
            if (is_int(temp)){
                int x = stoi(temp);   // VAL type node
                ExprTreeNode* val = new ExprTreeNode("VAL",new UnlimitedInt(x));
                stack_2.push_back(val);
            }
            else{                     // VAR type node
                ExprTreeNode* var = new ExprTreeNode("VAR",new UnlimitedRational());
                var->id = temp;
                stack_2.push_back(var);
            } 
        }
    }

    // the only element left in stack_2 is the right subtree node of := (root)    
    root->right = stack_2[stack_2.size()-1];  stack_2.pop_back();

    // push the root of expression into the expr_trees vector
    expr_trees.push_back(root);
}

UnlimitedRational* evaluate (SymbolTable* s, ExprTreeNode* root){
    if (root->type=="VAL"){
        // delete root->evaluated_value;
        root->evaluated_value=new UnlimitedRational(root->val->get_p(),root->val->get_q());
        // return root->evaluated_value;
    }
    else if (root->type=="VAR"){
        UnlimitedRational* res = s->search(root->id);
        // delete root->val;
        root->val = new UnlimitedRational(res->get_p(),res->get_q());
        // delete root->evaluated_value;
        root->evaluated_value = new UnlimitedRational(res->get_p(),res->get_q());
        // return root->evaluated_value;
    }
    else if (root->type=="ADD"){
        UnlimitedRational* temp_a = UnlimitedRational::add(evaluate(s,root->left),evaluate(s,root->right));
        // delete root->evaluated_value;
        root->evaluated_value=temp_a;    
        // return root->evaluated_value;
    }
    else if (root->type=="SUB"){
        UnlimitedRational* temp_s = UnlimitedRational::sub(evaluate(s,root->left),evaluate(s,root->right));
        // delete root->evaluated_value;
        root->evaluated_value=temp_s;        
        // return root->evaluated_value;
    }
    else if (root->type=="MUL"){
        UnlimitedRational* temp_m = UnlimitedRational::mul(evaluate(s,root->left),evaluate(s,root->right));
        // delete root->evaluated_value;
        root->evaluated_value=temp_m;       
        // return root->evaluated_value;        
    }
    else if (root->type=="DIV"){
        UnlimitedRational* temp_d = UnlimitedRational::div(evaluate(s,root->left),evaluate(s,root->right));
        // delete root->evaluated_value;
        root->evaluated_value=temp_d;
        // return root->evaluated_value;
    }

    return root->evaluated_value;
}

void Evaluator::eval(){
    ExprTreeNode* root = this->expr_trees[this->expr_trees.size()-1];
    delete root->right->evaluated_value;
    root->right->evaluated_value = new UnlimitedRational(evaluate(this->symtable,root->right)->get_p(),evaluate(this->symtable,root->right)->get_q());
    delete root->left->val;
    root->left->val =  new UnlimitedRational(root->right->evaluated_value->get_p() , root->right->evaluated_value->get_q());
    delete root->left->evaluated_value;
    root->left->evaluated_value = new UnlimitedRational(root->right->evaluated_value->get_p() , root->right->evaluated_value->get_q());
    this->symtable->insert(root->left->id, new UnlimitedRational(root->left->val->get_p() , root->left->val->get_q()));
}

// void printInorder(ExprTreeNode* node)
// {
//     if (node == nullptr) return;
 
//     // First recur on left subtree
//     printInorder(node->left);
 
//     // Now deal with the node
//     cout << node->type << " ";
//     if (node->type=="VAR")  cout<< node->id<<" ";
//     cout << node->evaluated_value->get_frac_str() <<endl;
 
//     // Then recur on right subtree
//     printInorder(node->right);
// }

// int main(){
//     Evaluator* a = new Evaluator();

//     // // pow1:=13
//     // vector<string> vec = {"pow1", ":=", "13"};
//     // a->parse(vec);
//     // a->eval();
//     // a->printInorder(a->expr_trees[a->expr_trees.size()-1]);  cout<<endl;

//     // // pow2:=((2*42)/(pow1*pow1))
//     // vec = {"pow2",":=","(","(","2","*","42",")","/", "(", "pow1", "*", "pow1", ")",")"};
//     // a->parse(vec);
//     // a->eval();
//     // a->printInorder(a->expr_trees[a->expr_trees.size()-1]);  cout<<endl;

//     // // pow3:=((3*42)/(pow2*pow2))
//     // vec =  {"pow3",":=","(","(","3","*","42",")","/", "(", "pow2", "*", "pow2", ")",")"};
//     // a->parse(vec);
//     // a->eval();
//     // a->printInorder(a->expr_trees[a->expr_trees.size()-1]);  cout<<endl;

//     // // pow4:=((4*42)/(pow3*pow3))
//     // vec =  {"pow4",":=","(","(","4","*","42",")","/", "(", "pow3", "*", "pow3", ")",")"};
//     // a->parse(vec);
//     // a->eval();
//     // a->printInorder(a->expr_trees[a->expr_trees.size()-1]);  cout<<endl;

//     // // pow5:=((5*42)/(pow4*pow4))
//     // vec =  {"pow5",":=","(","(","5","*","42",")","/", "(", "pow4", "*", "pow4", ")",")"};
//     // a->parse(vec);
//     // a->eval();
//     // a->printInorder(a->expr_trees[a->expr_trees.size()-1]);  cout<<endl;


// // v:=(13+(2/51))
// // g:=(2*v)
// // x:=(g+6)
// // y:=x

//     // v:=(13+(2/51))
//     vector<string> vec = {"v", ":=", "(", "13", "+", "(", "2", "/", "51", ")", ")"};
//     a->parse(vec);
//     a->eval();
//     printInorder(a->expr_trees[a->expr_trees.size()-1]);  cout<<endl;

//     // g:=(2*v)
//     vec = {"g", ":=", "(", "2", "*", "v", ")"};
//     a->parse(vec);
//     a->eval();
//     printInorder(a->expr_trees[a->expr_trees.size()-1]);  cout<<endl;

//     // x:=(g+6)
//     vec = {"x", ":=", "(", "g", "+", "6", ")"};
//     a->parse(vec);
//     a->eval();
//     printInorder(a->expr_trees[a->expr_trees.size()-1]);  cout<<endl;

//     // y:=x
//     vec =  {"y", ":=", "x"};
//     a->parse(vec);
//     a->eval();
//     printInorder(a->expr_trees[a->expr_trees.size()-1]);  cout<<endl;

//     // e:=d
//     // f:=(e+5)

//     // a:=5
//     vec =  {"a", ":=", "5"};
//     a->parse(vec);
//     a->eval();
//     printInorder(a->expr_trees[a->expr_trees.size()-1]);  cout<<endl;

//     // b:=((a+3)*2)
//     vec = {"b", ":=", "(", "(", "a", "+", "3", ")", "*", "2", ")"};
//     a->parse(vec);
//     a->eval();
//     printInorder(a->expr_trees[a->expr_trees.size()-1]);  cout<<endl;

//     // c:=(((a+b)*3)-7)
//     vec = {"c", ":=", "(", "(", "(", "a", "+", "b", ")", "*", "3", ")", "-", "7", ")"};
//     a->parse(vec);
//     a->eval();
//     printInorder(a->expr_trees[a->expr_trees.size()-1]);  cout<<endl;

//     // d:=((a/6)*(b/c))
//     vec = {"d", ":=", "(", "(", "a", "/", "6", ")", "*", "(", "b", "/", "c", ")", ")"};
//     a->parse(vec);
//     a->eval();
//     printInorder(a->expr_trees[a->expr_trees.size()-1]);  cout<<endl;  

//     delete a;
//     return 0;
// }
