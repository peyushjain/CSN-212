#include<bits/stdc++.h>
using namespace std;
#define pp pair<int,int>
#define mp make_pair
#define ss second
#define ff first

struct Interval{
	int low;
	int high;
};
// creating node of interval tree
struct node{
	Interval interval;
	node* left;
	node* right;
	int maxI; // stores max of high[root],max(left subtree, right subtree)
};

// creating new node
node* create(Interval input){    
	node* n=new node;
	n->interval=input;
	n->left=NULL;
	n->right=NULL;
	n->maxI=input.high;
}

// insert operation in interval tree. assuming interval tree is keyed at low
node* insert(node* root,Interval input){   
   // base case
   if(root==NULL) return create(input);
   
   if (input.low < root->interval.low){
   	 root->left=insert(root->left,input);
   }
   else{
   	 root->right=insert(root->right,input);
   }
   // updating maximum value of the current root node.
   if(root->left){
   	 root->maxI=max(root->left->maxI,root->maxI);
   }
   if(root->right){
   	 root->maxI=max(root->right->maxI,root->maxI);
   }	
   
   return root;
}

// preorder traversal of interval tree.
void preorder(node *root)
{
	if (root == NULL) return;
    cout << "[" << root->interval.low << ", " << root->interval.high << "]"<< " max = " << root->maxI << endl;
	preorder(root->left);
    preorder(root->right);
}

// searching for an overlapping interval. return true if overlapping interval  is found  (also prints overlapping interval) else return false. 
bool search( node* root, Interval input){
	
	while(root!=NULL && ( (input.low > root->interval.high) || (input.high < root->interval.low))){ 	
		//cout<<"overlaps with "<<"[" << root->interval.low << ", " << root->interval.high << "]"<<endl;	   	
		if(root->left && input.low <= root->left->maxI ){
	   	   root = root->left; 	
		}
		else{
		   root = root->right;
		}
	}
	if(root) {
	 cout<<"overlaps with "<<"[" << root->interval.low << ", " << root->interval.high << "]"<<endl;
	 return true;	
	}
	else return false;
}

bool equal(Interval i,Interval j){	
   return (i.low==j.low && i.high==j.high);	
}

// function to return successor node of a node in interval tree.
node* successor(node* root){
	node* current = root;
    // loop down to find the leftmost leaf 
    while (current->left != NULL) {
        current = current->left;
    }
    return current;
}

// function to delete node from interval tree. assuming interval to be deleted is given as input.
node* deleteNode( node* root, Interval input){
	
	if(root==NULL) return root;
	//cout<<"["<< root->interval.low << ", " << root->interval.high << "]"<<endl;
	if( equal(root->interval,input) ){	
		if(root->left==NULL && root->right!=NULL){
			node* temp= root->right;
			delete root;
			return temp;
		}
		else if(root->left!=NULL && root->right==NULL){
			node* temp= root->left;
			delete root;
			return temp;
		}
		else if(root->right==NULL && root->left==NULL){
			return NULL;
		}
		
		node* temp=successor(root->right);
		root->interval=temp->interval;
	//	root->maxI=max(temp->maxI,max(root->left->maxI, root->right->maxI));
		root->right= deleteNode(root->right,temp->interval);
	}
	if(input.low < root->interval.low)
	  root->left=deleteNode( root->left,input);
	else
	  root->right=deleteNode( root->right,input);
   
    root->maxI= root->interval.high;	
    if(root->left){
   	 root->maxI=max(root->left->maxI,root->maxI);
    }
    if(root->right){
   	 root->maxI=max(root->right->maxI,root->maxI);
    }
    return root;	  
}
int main(){
	Interval input[]= {{15, 20}, {10, 30}, {17, 19},{5, 20}, {12, 15}, {30, 40}};
    
	int n=sizeof(input)/sizeof(input[0]);  // number of intervals
	
	node* root=NULL; //  root of the interval tree
	for(int i=0;i<n;i++){
	   root=insert(root,input[i]);
	}
	// preorder traversal to check contructed tree
	preorder(root);
	
	// searching an interval
	Interval search_interval = {14, 16};
	Interval search_interval2 = {21, 23};
	
	if(!search(root,search_interval2)){
		cout<<"No overlapping intervals"<<endl;
	}
    
    // performing node deletion operation
    Interval del = {5,20};
    root=deleteNode(root,del);
    preorder(root);	
    
    // searching an interval after delete operation
	if(!search(root,search_interval)){
		cout<<"No overlapping intervals"<<endl;
	}
	return 0;    
}
