/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "parser.h"

//Write your code below this line

Parser::Parser(){
    symtable = new SymbolTable();
}

void del_expr_tree(ExprTreeNode* root){
    ExprTreeNode* temp = root;

    if (root==NULL)  return;

    if (root->left==NULL and root->right==NULL){
        delete root;
        return;
    }

    if (temp->left!=NULL){
        root = temp->left;
        del_expr_tree(root);
    }

    if (temp->right!=NULL){
        root=temp->right;
        del_expr_tree(root);
    }

    delete temp;

	// if(temp){
	// 	if(temp->left){
	// 		delete temp->left;
	// 	}
	// 	if(temp->right){
	// 		delete temp->right;
	// 	}
	// 	delete temp;
	// }
}

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

void Parser::parse(vector<string> expression){
    vector<string> stack_1; //parantheses and operators
    vector<ExprTreeNode*> stack_2; //nodes
    ExprTreeNode* root = new ExprTreeNode(":=",0);  //root

    if (expression[0]=="ret"){
        ExprTreeNode* ret = new ExprTreeNode("RET",0);
        root->left = ret;
    }
    else if (expression[0]=="del"){
        ExprTreeNode* del = new ExprTreeNode("DEL",0); 
        root->left = del;
    }
    else{
        ExprTreeNode* var = new ExprTreeNode("VAR",0);  //root->left
        var->id = expression[0];
        root->left = var;
    }


    for (int i=0;i<2;i++){
        vector<string>::iterator it = expression.begin();
        expression.erase(it);
    }

    for (string i:expression){
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
                    ExprTreeNode* sym = new ExprTreeNode("ADD",0);
                    sym->left = left;
                    sym->right = right;
                    stack_2.push_back(sym);
                }
                else if (temp=="-"){
                    ExprTreeNode* sym = new ExprTreeNode("SUB",0);
                    sym->left = left;
                    sym->right = right;
                    stack_2.push_back(sym);
                }
                else if (temp=="*"){
                    ExprTreeNode* sym = new ExprTreeNode("MUL",0);
                    sym->left = left;
                    sym->right = right;
                    stack_2.push_back(sym);
                }
                else if (temp=="/"){
                    ExprTreeNode* sym = new ExprTreeNode("DIV",0);
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
                int data = stoi(temp);   // VAL type node
                ExprTreeNode* val = new ExprTreeNode("VAL",data);
                stack_2.push_back(val);
            }
            else{                     // VAR type node
                ExprTreeNode* var = new ExprTreeNode("VAR",0);
                var->id = temp;
                stack_2.push_back(var);
            } 
        }
    }

    // the only element left in stack_2 is the right subtree node of := (root)    
    root->right = stack_2[stack_2.size()-1];  stack_2.pop_back();

    // updating symbol table

    if (root->left->type=="VAR")  {symtable->insert(root->left->id);}
    if (root->left->type=="DEL")  {last_deleted = symtable->search(root->right->id); symtable->remove(root->right->id);}  

    // push the root of expression into the expr_trees vector
    expr_trees.push_back(root);
}

Parser::~Parser(){
    delete symtable;
    for (auto i: expr_trees)  del_expr_tree(i);
}

// int main(){
//     Parser a;
//     vector <string> v1 = { "x" , ":=" , "3" };
//     vector <string> v2 = { "y" , ":=" , "2" };
//     vector <string> v3 = { "x" , ":=" , "4"};
//     vector <string> v4 = { "del", ":=" , "x"};
//     vector <string> v5 = { "z" , ":=" , "(" , "0" , "-" , "y", ")" };
//     vector <string> v6 = { "ret" , ":=" , "z" };

//     a.parse(v1);
//     a.parse(v2);
//     a.parse(v3);
//     a.parse(v4);
//     a.parse(v5);
//     a.parse(v6);
// }