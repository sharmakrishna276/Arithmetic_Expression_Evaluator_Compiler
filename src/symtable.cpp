/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symtable.h"

//Write your code below this line

SymbolTable::SymbolTable(){
    this->root = NULL;
    this->size = 0;
}

// BST insertion without height balancing

SymNode* insertBST(SymNode* root, string key){
	if (root==NULL)  {root = new SymNode(key); return root;}
	SymNode* ptr = root;
	while (ptr->left!=NULL or ptr->right!=NULL){
		if (ptr->key.compare(key)<0){
			if (ptr->right==NULL) break;
			else ptr = ptr->right;
		}
		else if (ptr->key.compare(key)>0){
			if (ptr->left==NULL) break;
			else ptr = ptr->left;
		}
		else{
			return root;
		}
	}
	if (ptr->key.compare(key)<0){
		ptr->right = new SymNode(key); 
		ptr->right->par = ptr;
	}
	else{
		ptr->left = new SymNode(key); 
		ptr->left->par = ptr;
	}
	return root;
}

// Helper function to fetch height of nodes

int getH(SymNode* root){
	if (root==NULL) return 0;
	else return root->height;
}

int get_balance(SymNode* root){
	if (root==NULL) return 0;
	else return (getH(root->left) - getH(root->right));
}

// updating the heights of nodes after insertion

int updateHeight(SymNode* root, string k){
	if (root==NULL)  return 0;
	if (root->key.compare(k)<0){
		if (root->right != NULL){
			root->right->height = updateHeight(root->right, k);
		}
	}
	else{
		if (root->left != NULL){
			root->left->height = updateHeight(root->left, k);
		}		
	}
	root->height = max (getH(root->left) , getH(root->right)) + 1;
	return root->height;
}

// AVL insertion

SymNode* insertAVL(SymNode* root, string key){
	root = insertBST(root,key);
	root->height = updateHeight(root,key);

	SymNode* ptr = root;
	SymNode* parent = NULL;

	SymNode* ans = NULL;
	SymNode* ans_p = NULL;

	while (ptr->key.compare(key) != 0){
		// condition for imbalance of heights
        if (abs(get_balance(ptr)) > 1) { ans = ptr; ans_p = parent;} 

		if (ptr->key.compare(key) < 0) {parent = ptr; ptr = ptr->right;}
		else {parent = ptr; ptr = ptr->left;} 
	}

	if (ans==NULL)  return root; //heights are already balanced

    ptr = ans;
    parent = ans_p;

	if (getH(ptr->left) > getH(ptr->right)){  // Node inserted in left child

		// Case 1 (Node inserted in left subtree of left child)

		if ((key.compare(ptr->left->key) < 0)){
			if (parent!=NULL){
				if (ptr == parent->left)  parent->left = ptr->RightRightRotation();
				else parent->right = ptr->RightRightRotation();
			}
			else {
                root = ptr->RightRightRotation();
            }
		}

		// Case 3 (Node inserted in right subtree of left child)

		else{
			if (parent!=NULL){
				if (ptr == parent->left)  parent->left = ptr->RightLeftRotation();
				else parent->right = ptr->RightLeftRotation();
			}
			else{
                root = ptr->RightLeftRotation();
            }
		}

	}

	else {    // Node inserted in right child

		// Case 2 (Node inserted in right subtree of right child)

		if (key.compare(ptr->right->key)>0)	{
			if (parent!=NULL){
				if (ptr == parent->left)  parent->left = ptr->LeftLeftRotation();
				else parent->right = ptr->LeftLeftRotation();
			}
			else{
                root = ptr->LeftLeftRotation();
            }
		}

		// Case 4 (Node inserted in left subtree of right chlid)

		else{
			if (parent!=NULL){
				if (ptr == parent->left)  parent->left = ptr->LeftRightRotation();
				else parent->right = ptr->LeftRightRotation();
			}
			else{
                root = ptr->LeftRightRotation();
            }
		}
	}

    root->height = updateHeight(root,key);
	return root;
}

void SymbolTable::insert(string k){
	if (this->search(k)!=-2)  return;
    this->root = insertAVL(this->root,k); 
    size++;
}

SymNode* deleteAVL(SymNode* root, string key){
	if (root==NULL) return root;

	if (root->key.compare(key)<0) {
		SymNode* temp = deleteAVL(root->right,key);
		root->right = temp;
		if (temp!=NULL) temp->par = root;
	}
	else if (root->key.compare(key)>0)  {
		SymNode* temp = deleteAVL(root->left,key);
		root->left = temp;
		if (temp!=NULL) temp->par = root;
	}
	else{
		if (root->left==NULL and root->right==NULL){
			delete root;
			root = NULL;
		}
		else if (root->left==NULL){
			SymNode* ptr = root->right;
			root->right=NULL;
			delete root;
			root = ptr;
			root->par = NULL;
		}
		else if (root->right == NULL){
			SymNode* ptr = root->left;
			root->left=NULL;
			delete root;
			root = ptr;
			root->par = NULL;
		}
		else{
			SymNode* suc = root->right;
			while (suc->left!=NULL){
				suc=suc->left;
			}
			root->key = suc->key;
			root->address = suc->address;
			SymNode* temp = deleteAVL(root->right,suc->key);
			root->right = temp;
			if (temp!=NULL) temp->par = root;
		}
	}

	if (root==NULL) return root;

	root->height = 1 + max( getH(root->left) , getH(root->right) );
	int balance = get_balance(root);

	if (balance>1){
		if (get_balance(root->left)>=0){
			return root->RightRightRotation();
		}
		else{
			return root->RightLeftRotation();
		}
	}

	if (balance<-1){
		if (get_balance(root->right)<=0){
			return root->LeftLeftRotation();
		}
		else{
			return root->LeftRightRotation();
		}
	}

	return root;
}


SymNode* searchNode(SymNode* root, string k){     //search helper function
    if (root==NULL) return NULL;
    if (root->key.compare(k)==0)  return root;
    else if (root->key.compare(k)<0)  return searchNode(root->right,k);
    else return searchNode(root->left,k);
}

int SymbolTable::search(string k){
    SymNode* found = searchNode(this->get_root(),k);
    if (found!=NULL)  return found->address;
    else return -2;
}

void SymbolTable::remove(string k){
	if (this->search(k)==-2)  return;
	this->root = deleteAVL(this->get_root(),k);
	// if (this->root!=NULL)  this->root->height = updateHeight(this->root,k);
	size--;
	return;
}

void SymbolTable::assign_address(string k,int idx){
    SymNode* found = searchNode(this->root,k);
    if (found)  {found->address=idx;}
	else {this->insert(k); found = searchNode(this->root,k); found->address=idx;}
	return;
}

int SymbolTable::get_size(){
    return this->size;
}

SymNode* SymbolTable::get_root(){
    return this->root;
}

SymbolTable::~SymbolTable(){
    SymNode* temp = this->root;

	if (this->root==NULL)  return;

    if (this->root->left==NULL and this->root->right==NULL){
        delete this->root;
        return;
    }

    if (temp->left!=NULL){
        this->root = temp->left;
        this->~SymbolTable();
    }

    if (temp->right!=NULL){
        this->root=temp->right;
        this->~SymbolTable();
    }

    delete temp;
}

// void iorder(SymNode* root){
//     if (root==NULL) return;
//     iorder(root->left);
//     cout<<"key: "<<root->key<<" , Height: "<<root->height<<" , Address: "<<root->address<<endl;
//     iorder(root->right);
// }

// int main(){
//     SymbolTable* a = new SymbolTable();
//     a->insert("a");
// 	a->assign_address("a",12);
// 	a->remove("a");
//     a->insert("b");
// 	a->assign_address("b",13);
//     a->insert("c");
// 	a->assign_address("c",14);
//     a->insert("f");
// 	a->assign_address("f",15);
//     a->insert("d");
// 	a->assign_address("d",17);
// 	a->insert("e");
// 	a->assign_address("e",121);
// 	a->remove("b");
// 	a->remove("a");
// 	a->remove("c");
// 	a->assign_address("b",14);
// 	inorder(a->get_root());

// 	// a->remove("c");
// 	// inorder(a->get_root());
// 	// a->remove("b");
// 	// cout<<a->get_root()->key<<endl;
// 	// a->remove("c");
// 	// cout<<a->get_root()->key<<endl;
// 	// a->remove("d");
// 	// cout<<a->get_root()->key<<endl;

// 	delete a;
// }

// int main(){
// 	SymbolTable a;
// 	a.insert("x");
// 	a.assign_address("x" , 0);
// 	a.insert("y");
// 	a.assign_address("y" , 1);
// 	a.insert("z");
// 	a.assign_address("z" , 2);
// 	a.remove("y");
// 	cout<<a.search("z")<<endl;
// }