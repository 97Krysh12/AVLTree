//============================================================================
// Name        : BinaryTreeAVL.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : BinaryTreeAVL implementation C++, Ansi-style
//============================================================================
#include<iostream>
#include<cstdio>
#include<algorithm>

//#define pow2(n) (1 << (n))
using namespace std;

struct Node{

	Node* left;  // Left Son
	Node* right; // Right Son
	int data;    // Node Value
	//int height = 0;
};
Node *root = NULL;

class Tree

{

    public:

        int height(Node *); // finds height of subtree
        int setBalance(Node *); // find balance factor of subtree
        Node * RightRot(Node *); // Single Right Rotation
        Node * LeftRot(Node *); // Single Left Rotation
        Node * LeftRightRot(Node *); // Left then Right Rotation
        Node * RightLeftRot(Node *); // Right then Left Rotation
        Node * balance(Node *); // Rotates tree accordingly after Insert
        Node * InsertAVL(Node *, int); // Adds a new element to tree
        void display(Node *, int); // Method used to visualize the tree structure (Taken from the internet)
        void Inorder(Node *);   // Inorder Traversal
        void Preorder(Node *); // Preorder Traversal
        void Postorder(Node *); // Postorder Traversal
        Node * DeleteAVL(Node* , int); // Removes Given element from tree (currently only works without rotation)
        bool Search(Node*, int); // Searches the tree for a value
};







/////////////////////
//GLOBAL VARIABLES///
int maxpath = 0;
int CurrentPath = 0;
int NewPath = 0;
int height = 0;
int nrNodes = 0;
int leaf = 0;

int Max(int a, int b) {
	if(a>b) return a;
	return b;
}

Node* FindMin(Node* root) {
	if(root->left == NULL) return root;
	else return FindMin(root->left);
}


Node* NewNode(int data) {
	Node* newNode = new Node();
	newNode->data = data;
	newNode->left = NULL;
	newNode->right = NULL;
	nrNodes++;
	return newNode;
}

bool Tree::Search(Node* root , int data) {
	if(root == NULL) return false;
	else if(root->data == data) return true;
	else if(data <= root->data) return Search(root->left,data);
	else return Search(root->right, data);
}


void Tree::Preorder(Node* root) {
	if(root == NULL) return;
	cout << root->data << "  ";
	Preorder(root->left);
	Preorder(root->right);
}

void Tree::Inorder(Node* root) {
	if(root == NULL) return;
	Inorder(root->left);
	cout << root->data<< "  ";
	Inorder(root->right);
}

void Tree::Postorder(Node* root) {
	if(root == NULL) return;

	Postorder(root->left);
	Postorder(root->right);
	cout << root->data<< "  ";
}


void MaxPath(Node* root) {

	CurrentPath++;
	if(root == NULL) {
		CurrentPath--;
		if(CurrentPath > maxpath) {
			maxpath = CurrentPath;
		}

		return;
	}

	MaxPath(root->left);
	MaxPath(root->right);
	CurrentPath--;

}


void MaxPathArray(Node* root, int* path) {
	NewPath++;
	if(root != NULL) path[NewPath-1] = root->data;
	if(root == NULL) {
		NewPath--;
		if(NewPath > height) height = NewPath;


		return;
	}


	MaxPathArray(root->left, path);
	MaxPathArray(root->right, path);
	NewPath--;
}


void ShowMaxPath(Node* root) {
    MaxPath(root);
	int* path = new int[maxpath];
	MaxPathArray(root,path);
	for(int i = 0 ; i < maxpath ; i++) cout << path[i] << "  ";

}

int Tree::height(Node* root) {
	if(root == NULL) return -1;
	return Max(height(root->left),height(root->right))+1;
}

int Tree::setBalance(Node* root) {

    return height(root->left) - height(root->right);
}


Node*  Tree::RightRot(Node* root) {
    Node *temp;
    temp = root->right;
    root->right = temp->left;
    temp->left = root;

    return temp;

}

Node* Tree::LeftRot(Node* root) {


	 Node *temp;
	 temp = root->left;

	 root->left = temp->right;

	 temp->right = root;
	 return temp;
}

Node* Tree::LeftRightRot(Node *root)

{

    Node *temp;
    temp = root->left;
    root->left = RightRot(temp);

    return LeftRot(root);

}


Node* Tree::RightLeftRot(Node* root)

{

    Node *temp;
    temp = root->right;
    root->right = LeftRot(temp);

    return RightRot(root);

}


Node* Tree::balance(Node *root)

{
  int bf = setBalance(root);
    if (bf > 1) {
        if (setBalance(root->left) > 0)
        	root = LeftRot(root);
        else root = LeftRightRot(root);
    }

    else if (bf < -1) {
        if (setBalance(root->right) > 0) root = RightLeftRot(root);
        else root = RightRot(root);

    }

    return root;

}

Node* Tree::InsertAVL(Node* root, int data) {
	if(root == NULL) {
       root = NewNode(data);

	}
	else if(data < root->data) {
	root->left = InsertAVL(root->left,data);
	root = balance(root);
	}
		else if(data >= root->data) {
			root->right = InsertAVL(root->right,data);
			root = balance(root);
		}
	return root;
}

void  Tree::display(Node *ptr, int level)

	{
	    int i;
	    if (ptr != NULL)
	    {
	        display(ptr->right, level + 1);
	        printf("\n");

	        if (ptr == root) cout << "Root -> ";
	        for (i = 0; i < level && ptr != root; i++) cout << "        ";

	        cout << ptr->data;
	        display(ptr->left, level + 1);
	    }
}


Node* Tree::DeleteAVL(Node* root, int data) {

	if(root == NULL) return root;
	else if(data < root->data) {

           root->left = DeleteAVL(root->left, data);
           // root = balance(root);
            }

	else if(data > root->data) {

            root->right = DeleteAVL(root->right, data);
           //  root = balance(root);
         }

	else {
		if(root->left == NULL && root->right == NULL) {
			delete root;
			root = NULL;
		}
		else if(root->left == NULL) {
			Node* temp = root;
			root = root->right;
			delete temp;
			nrNodes--;
		}
		else if(root->right == NULL) {
			Node* temp = root;
			root = root->left;
			delete temp;
			nrNodes--;
		}
		else {
			Node* temp = FindMin(root->right);
			root->data = temp->data;
			root->right = DeleteAVL(root->right, temp->data);

		}
	}
//root = balance(root);
return root;
}

int main() {



	    int option, data;
	    Tree tree1;

	    while (1)
	    {

	        cout << "\n\n\n--------MENU-----------------" << endl;
	        cout << "AVL Tree" << endl;
	        cout << "\n---------------------" << endl;
	        cout << "1.Insert an Integer value  " << endl;
	        cout << "2.Display AVL Tree" << endl;
	        cout << "3.InOrder traversal" << endl;
	        cout << "4.PreOrder traversal" << endl;
	        cout << "5.PostOrder traversal" << endl;
	        cout << "6.Height of tree , number of nodes and leaves" << endl;
	        cout << "7.Delete an Integer value" << endl;
	        cout << "8.Search for an Integer" << endl;
	        cout << "9.Exit" << endl;
	        cout << "Enter your Choice: ";

	        cin >> option;

	        switch (option)

	        {

	            case 1:

	                cout << "Enter value to be inserted: ";
	                cin >> data;
	                root = tree1.InsertAVL(root, data);

	                break;

	            case 2:

	                if (root == NULL)

	                {

	                    cout << "Tree is Empty" << endl;

	                    continue;

	                }

	                cout << "Balanced AVL Tree:" << endl;
	                tree1.display(root, 1);

	                break;

	            case 3: {

	                cout << "Inorder Traversal:" << endl;
	                tree1.Inorder(root);
	                cout << endl;
	                break;
	            }
	            case 4: {

	                cout << "Preorder Traversal:" << endl;
	                tree1.Preorder(root);
	                cout << endl;
	                break;
	            }
	            case 5: {

	                cout << "Postorder Traversal:" << endl;
	                tree1.Postorder(root);
	                cout << endl;
	            }
	                break;

	            case 6: MaxPath(root);cout << "height of tree from root = " << maxpath - 1 << "and the path looks like this : " ; ShowMaxPath(root);
	                    cout << "\n number of nodes in tree: " << nrNodes ; break;

                case 7:
                    cout << "Enter value to be deleted: ";
	                cin >> data;
                    tree1.DeleteAVL(root,data); break;

                case 8:
                    cout << "Enter the value you want to search for: ";
	                cin >> data;
                    if(tree1.Search(root, data ) == true) cout << "\n\n FOUND\n";
                    else cout << "\n NOT FOUND\n"; break;

                case 9: exit(1); break;

	            default: cout << "Option not Found" << endl;

	        }

	    }

	    return 0;

}

