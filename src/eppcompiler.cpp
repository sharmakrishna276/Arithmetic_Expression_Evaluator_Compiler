/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "eppcompiler.h"

//Write your code below this line

EPPCompiler::EPPCompiler(){
    this->memory_size = 0;
    this->output_file = "";
    this->mem_loc = vector<int>();
}

EPPCompiler::EPPCompiler(string out_file,int mem_limit){
    this->output_file = out_file;
    this->memory_size = mem_limit;
    for (int i=0;i<this->memory_size;i++)  this->mem_loc.push_back(0);
}

// converts integer to string
string itos(int x){
    string s;
    int sgn = 1;
    int temp =x;
    if (x<0){
        sgn = -1;
        temp = -1*temp;
    }
    if (x==0){
        return "0";
    }
    while (temp>0){
        int t = temp%10;
        temp = temp/10;
        s = char(48+t) + s;
    }
    if (sgn==-1){
        s = '-' + s;
    }
    return s;
}

void EPPCompiler::compile(vector<vector<string>> code){
    vector<string> commands;
    for (auto i: code){

        // creating expression tree
        targ.parse(i);

        // accessing root of last created tree
        ExprTreeNode* node = targ.expr_trees.back();

        // assigning memory mapping for variable assignment
        if (node->left->type == "VAR"){
            if (this->targ.symtable->search(node->left->id) == -1){
                int loc;
                for (int j=0;j<this->memory_size;j++) {
                    if (this->mem_loc[j]==0) {
                        loc=j; 
                        this->mem_loc[j]=1; 
                        break;
                    }
                }
                this->targ.symtable->assign_address(node->left->id,loc);
            }
        }

        // freeing memory address for delete statement
        if (node->left->type == "DEL"){
            int loc = this->targ.last_deleted;
            this->mem_loc[loc]=0;
        }

        // generating targ command from recently created expression tree 
        vector<string> output = this->generate_targ_commands();
        if (commands.empty()) commands.insert(commands.begin() , output.begin() , output.end());
        else commands.insert(commands.end() , output.begin() , output.end());
    }

    this->write_to_file(commands);
}

void generate(ExprTreeNode* root, vector<string> &commands, Parser &targ){
    if (root->left == NULL and root->right==NULL){
        if (root->type=="VAL"){
            string s1 = "PUSH ";
            string s2 = itos(root->num);
            s1.append(s2);
            commands.push_back(s1);
            // std::cout<<s1<<std::endl;
            return;
        }

        if (root->type=="VAR"){
            string s1 = "PUSH mem[";
            int loc = targ.symtable->search(root->id);
            string s2 = itos(loc);
            s1.append(s2);
            string s3 = "]";
            s1.append(s3);
            commands.push_back(s1);
            // std::cout<<s1<<std::endl;
            return;
        }
    }

    generate(root->right,commands,targ);
    generate(root->left,commands,targ);
    // std::cout<<root->type<<std::endl;
    commands.push_back(root->type);
}

vector<string> EPPCompiler::generate_targ_commands(){
    vector<string> commands;

    ExprTreeNode* node = targ.expr_trees.back();

    if (node->left->type!="DEL") generate(node->right , commands, this->targ);

    if (node->left->type == "VAR"){
        int loc = this->targ.symtable->search(node->left->id);
        string s1 = "mem[";
        string s2 = itos(loc);
        s1.append(s2);
        string s3 = "] = POP";
        s1.append(s3);
        commands.push_back(s1);  
    }

    if (node->left->type == "DEL"){
        int loc = this->targ.last_deleted;
        string s1 = "DEL = mem[";
        string s2 = itos(loc);
        s1.append(s2);
        string s3 = "]";
        s1.append(s3);
        commands.push_back(s1);
    }

    if (node->left->type == "RET"){
        string s1 = "RET = POP";
        commands.push_back(s1);
    }

    return commands;
}

void EPPCompiler::write_to_file(vector<string> commands){
    fstream mera_file;
    mera_file.open(this->output_file, std::ios::out);
    for (string i : commands){
        mera_file << i <<"\n";
    }
    mera_file.close();
}

EPPCompiler::~EPPCompiler(){
    // delete targ.symtable;
}

/* !!!!!!!! MAIN !!!!!!!!!*/

// int main(){
//     vector <string> v1 = { "x" , ":=" , "3" };  // mem[0]
//     vector <string> v2 = { "y" , ":=" , "x" };  // mem[1]
//     vector <string> v3 = { "z" , ":=" , "4"};  // mem[2]
//     vector <string> v4 = {"w" , ":=" , "10"};  //mem[3]
//     vector <string> v5 = { "del", ":=" , "w"};  // del = mem[3]
//     vector <string> v6 = { "z" , ":=" , "(" , "0" , "-" , "y", ")" };  // mem[2] = pop
//     vector <string> v7 = {"del" , ":=" , "y"};  // del = mem[1]
//     vector <string> v8 = {"del" , ":=" , "x"};  // del = mem[0]
//     vector <string> v9 = { "ret" , ":=" , "z" };  // push mem[2]
//     vector<vector<string>> vec = {v1 , v2, v3 , v4, v5 , v6 , v7 , v8 , v9};
//     EPPCompiler *a = new EPPCompiler("a" , 5);
//     a->compile(vec);
// }

// int main(){
//     vector<string> v1 = { "x" , ":=" , "2"};  // mem[0]
//     vector<string> v2 = {"y" , ":=" , "4"};  //mem[1]
//     vector<string> v3 = {"z" , ":=" , "6"};  //mem[2]
//     vector <string> v4 = { "del", ":=" , "y"}; // del = mem[1]
//     vector <string> v5 = { "ret" , ":=" , "z" }; // push mem[2]
//     vector<vector<string>> vec = {v1 , v2, v3 , v4 , v5};
//     EPPCompiler *res = new EPPCompiler("output" , 5);
//     res->compile(vec);
// }

// int main(){
//     Parser pars = Parser();
//     vector<string> commands;
//     int memory_size = 5;
//     vector<int> mem_loc(5);

//     // **************************8
//     vector<string> vec = {"a", ":=", "(" , "1" ,"+", "2", ")"};
//     pars.parse(vec);
//     ExprTreeNode* root = pars.expr_trees.back();

//     // assigning memory mapping for variable assignment
//     if (root->left->type == "VAR"){
//         int loc;
//         for (int i=0;i<memory_size;i++) {if (mem_loc[i]==0) {loc=i; mem_loc[i]=1; break;}}
//         pars.symtable->assign_address(root->left->id,loc);
//     }

//     // freeing memory address for delete statement
//     if (root->left->type == "DEL"){
//         int loc = pars.last_deleted;
//         mem_loc[loc]=0;
//     }
    
//     if (root->left->type!="DEL") generate(root->right , commands , pars);

//     if (root->left->type == "VAR"){
//         int loc = pars.symtable->search(root->left->id);
//         string s1 = "mem[";
//         string s2 = itos(loc);
//         s1.append(s2);
//         string s3 = "] = POP";
//         s1.append(s3);
//         // std::cout<<s1<<std::endl;
//         commands.push_back(s1);  
//     }

//     if (root->left->type == "DEL"){
//         int loc = pars.last_deleted;
//         string s1 = "DEL = mem[";
//         string s2 = itos(loc);
//         s1.append(s2);
//         string s3 = "]";
//         s1.append(s3);
//         // std::cout<<s1<<std::endl;
//         commands.push_back(s1);
//     }

//     if (root->left->type == "RET"){
//         string s1 = "RET = POP";
//         // std::cout<<s1<<std::endl;
//         commands.push_back(s1);
//     }

//     for (auto i : commands){
//         std::cout<<i<<std::endl;
//     }
//     commands.clear();

//     // *************************************
//     std::cout<<"\n"; vec = {"b", ":=", "(" , "1" ,"+", "2", ")"};
//     pars.parse(vec);
//     root = pars.expr_trees.back();

//     // assigning memory mapping for variable assignment
//     if (root->left->type == "VAR"){
//         int loc;
//         for (int i=0;i<memory_size;i++) {if (mem_loc[i]==0) {loc=i; mem_loc[i]=1; break;}}
//         if (pars.symtable->search(root->left->id)==-1) pars.symtable->assign_address(root->left->id,loc);
//     }

//     // freeing memory address for delete statement
//     if (root->left->type == "DEL"){
//         int loc = pars.last_deleted;
//         mem_loc[loc]=0;
//     }

//     if (root->left->type!="DEL") generate(root->right , commands , pars);
    
//     if (root->left->type == "VAR"){
//         int loc = pars.symtable->search(root->left->id);
//         string s1 = "mem[";
//         string s2 = itos(loc);
//         s1.append(s2);
//         string s3 = "] = POP";
//         s1.append(s3);
//         // std::cout<<s1<<std::endl;
//         commands.push_back(s1);  
//     }

//     if (root->left->type == "DEL"){
//         int loc = pars.last_deleted;
//         string s1 = "DEL = mem[";
//         string s2 = itos(loc);
//         s1.append(s2);
//         string s3 = "]";
//         s1.append(s3);
//         // std::cout<<s1<<std::endl;
//         commands.push_back(s1);
//     }

//     if (root->left->type == "RET"){
//         string s1 = "RET = POP";
//         // std::cout<<s1<<std::endl;
//         commands.push_back(s1);
//     }

//     for (auto i : commands){
//         std::cout<<i<<std::endl;
//     }
//     commands.clear();

//     // **************************** 
//     std::cout<<"\n"; vec = {"ret", ":=", "(" , "a" ,"+", "b", ")"};  

//     pars.parse(vec);
//     root = pars.expr_trees.back();

//     // assigning memory mapping for variable assignment
//     if (root->left->type == "VAR"){
//         int loc;
//         for (int i=0;i<memory_size;i++) {if (mem_loc[i]==0) {loc=i; mem_loc[i]=1; break;}}
//         if (pars.symtable->search(root->left->id)==-1) pars.symtable->assign_address(root->left->id,loc);
//     }

//     // freeing memory address for delete statement
//     if (root->left->type == "DEL"){
//         int loc = pars.last_deleted;
//         mem_loc[loc]=0;
//     }

//     if (root->left->type!="DEL") generate(root->right , commands , pars);
    
//     if (root->left->type == "VAR"){
//         int loc = pars.symtable->search(root->left->id);
//         string s1 = "mem[";
//         string s2 = itos(loc);
//         s1.append(s2);
//         string s3 = "] = POP";
//         s1.append(s3);
//         // std::cout<<s1<<std::endl;
//         commands.push_back(s1);  
//     }

//     if (root->left->type == "DEL"){
//         int loc = pars.last_deleted;
//         string s1 = "DEL = mem[";
//         string s2 = itos(loc);
//         s1.append(s2);
//         string s3 = "]";
//         s1.append(s3);
//         // std::cout<<s1<<std::endl;
//         commands.push_back(s1);
//     }

//     if (root->left->type == "RET"){
//         string s1 = "RET = POP";
//         // std::cout<<s1<<std::endl;
//         commands.push_back(s1);
//     }

//     for (auto i : commands){
//         std::cout<<i<<std::endl;
//     }
//     commands.clear();

//     // ************************
//     std::cout<<"\n"; vec = {"del", ":=", "v"};

//     pars.parse(vec);
//     root = pars.expr_trees.back();

//     // assigning memory mapping for variable assignment
//     if (root->left->type == "VAR"){
//         int loc;
//         for (int i=0;i<memory_size;i++) {if (mem_loc[i]==0) {loc=i; mem_loc[i]=1; break;}}
//         if (pars.symtable->search(root->left->id)==-1) pars.symtable->assign_address(root->left->id,loc);
//     }

//     // freeing memory address for delete statement
//     if (root->left->type == "DEL"){
//         int loc = pars.last_deleted;
//         mem_loc[loc]=0;
//     }

//     if (root->left->type!="DEL") generate(root->right , commands , pars);
    
//     if (root->left->type == "VAR"){
//         int loc = pars.symtable->search(root->left->id);
//         string s1 = "mem[";
//         string s2 = itos(loc);
//         s1.append(s2);
//         string s3 = "] = POP";
//         s1.append(s3);
//         // std::cout<<s1<<std::endl;
//         commands.push_back(s1);  
//     }

//     if (root->left->type == "DEL"){
//         int loc = pars.last_deleted;
//         string s1 = "DEL = mem[";
//         string s2 = itos(loc);
//         s1.append(s2);
//         string s3 = "]";
//         s1.append(s3);
//         // std::cout<<s1<<std::endl;
//         commands.push_back(s1);
//     }

//     if (root->left->type == "RET"){
//         string s1 = "RET = POP";
//         // std::cout<<s1<<std::endl;
//         commands.push_back(s1);
//     }

//     for (auto i : commands){
//         std::cout<<i<<std::endl;
//     }
//     commands.clear();

//     // **************************************
//     std::cout<<"\n"; vec = {"ret", ":=", "(" , "x" , "/" , "2" , ")"};

//     pars.parse(vec);
//     root = pars.expr_trees.back();

//     // assigning memory mapping for variable assignment
//     if (root->left->type == "VAR"){
//         int loc;
//         for (int i=0;i<memory_size;i++) {if (mem_loc[i]==0) {loc=i; mem_loc[i]=1; break;}}
//         if (pars.symtable->search(root->left->id)==-1) pars.symtable->assign_address(root->left->id,loc);
//     }

//     // freeing memory address for delete statement
//     if (root->left->type == "DEL"){
//         int loc = pars.last_deleted;
//         mem_loc[loc]=0;
//     }

//     if (root->left->type!="DEL") generate(root->right , commands , pars);
    
//     if (root->left->type == "VAR"){
//         int loc = pars.symtable->search(root->left->id);
//         string s1 = "mem[";
//         string s2 = itos(loc);
//         s1.append(s2);
//         string s3 = "] = POP";
//         s1.append(s3);
//         // std::cout<<s1<<std::endl;
//         commands.push_back(s1);  
//     }

//     if (root->left->type == "DEL"){
//         int loc = pars.last_deleted;
//         string s1 = "DEL = mem[";
//         string s2 = itos(loc);
//         s1.append(s2);
//         string s3 = "]";
//         s1.append(s3);
//         // std::cout<<s1<<std::endl;
//         commands.push_back(s1);
//     }

//     if (root->left->type == "RET"){
//         string s1 = "RET = POP";
//         // std::cout<<s1<<std::endl;
//         commands.push_back(s1);
//     }

//     for (auto i : commands){
//         std::cout<<i<<std::endl;
//     }
//     commands.clear();
// }
