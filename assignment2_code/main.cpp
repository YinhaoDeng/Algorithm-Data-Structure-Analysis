#include <iostream>
#include <string>
#include <vector>

using namespace std;

class AVLTree{
    public:
        struct Node
        {
            int data;
            int height = 0;
            Node* left = NULL;
            Node* right = NULL;
        };
        Node* root = NULL; //root of the tree

    void handle_input(string command)
    {
        string num_store = "";
        if(command[0]=='A')
        {
            for(int j=1; j<command.length();j++)
            {
                num_store = num_store + command[j];
            }
            root = insert_node(root,stoi(num_store));
            
        }else if(command[0]=='D')
        {
            for(int k=1; k<command.length(); k++)
            {
                num_store = num_store + command[k];
            }
            root = delete_node(root,stoi(num_store));
        }else
            print_tree(command); //"EMPTY" case
    }


    //create new tree and use input data as node data
    Node *create_new_tree(int data)
    {
        Node *store = new Node();
        store -> data = data;
        store -> left = NULL;
        store -> right = NULL;
        store -> height = 1;
        return store;
    }

    //return the height of the tree, if tree not exist, return 0
    int height(Node* node)
    {
        return node==NULL? 0:node->height;
    }

    
    Node *insert_node(Node *root, int data)
    {
        if(root != NULL) //if the tree exist
        {
            if(data < root->data)//insert into left (smaller)
                root -> left = insert_node(root->left,data);
            else if(data > root->data)//into right subtree
                root -> right = insert_node(root->right,data);
            else
                return root;
        }else
            return create_new_tree(data);

        root -> height = max(height(root->left),height(root->right)) + 1;
        
        //rebalance the tree
        int node_height = height_difference(root);
        if(node_height < -1 && data > root-> right -> data)
            return right_right_rotation(root);
        if(node_height > 1 && data < root-> left -> data)
            return left_left_rotation(root);
        if(node_height > 1 && data > root->left->data)
        {
            root->left = right_right_rotation(root->left);
            return left_left_rotation(root);
        }
        if(node_height < -1 && data < root-> right -> data)
        {
            root->right = left_left_rotation(root->right);
            return right_right_rotation(root);
        }
        return root;
    }

    //Node deletion is the continuous exchange of data, change and delete the node, and finally locate the leaf node
    Node *delete_node(Node *node,int data)
    {
        if(node == NULL) //tree not exist
            return node;
        else
        {
            if(data < node->data)
                node->left = delete_node(node->left,data);
            else if(data > node->data)
                node->right = delete_node(node->right,data);
            else
            {
                if(data == node->data && (node->left == NULL || node->right == NULL))
                {
                    if(node->left != NULL)
                    {
                        Node *store = node->left;
                        if(store == NULL)
                        {
                            store = node;
                            node = NULL;
                        }else
                            *node = *store;
                    }else
                    {
                        Node *store = node->right;
                        if(store == NULL)
                        {
                            store = node;
                            node = NULL;
                        }else
                            *node = *store;
                    }
                }else
                {
                    Node *store = getMax(node->left);
                    node->data = store -> data;
                    node->left = delete_node(node->left,store->data);
                }
            }
        }
        
        if(node == NULL)
            return node;
        else
        {
            node->height = max(height(node->left),height(node->right)) + 1;

            int degree = height_difference(node);
            if(degree > 1 && height_difference(node->left) >= 0)
                return left_left_rotation(node);
            if(degree > 1 && height_difference(node->left) < 0)
            {
                node->left = right_right_rotation(node->left);
                return left_left_rotation(node);
            }
            if(degree <-1 && height_difference(node->right) <= 0)
                return right_right_rotation(node);
            if(degree <-1 && height_difference(node->right) > 0)
            {
                node->right = left_left_rotation(node->right);
                return right_right_rotation(node);
            }
        }
        return node;
    }

    //left rotate
    Node* right_right_rotation(Node *node)
    {
        Node* childnode1 = node->right;
        Node* childnode2 = childnode1->left;

        childnode1->left = node;
        node->right = childnode2;

        node->height = max(height(node->left),height(node->right)) + 1;
        childnode1->height = max(height(childnode1->left),height(childnode1->right)) + 1;
        
        return childnode1;
    } 

    //right rotate
    Node* left_left_rotation(Node *node)
    {
        Node* childnode1 = node->left;
        Node* childnode2 = childnode1->right;

        childnode1->right = node;
        node->left = childnode2;

        node->height = max(height(node->left),height(node->right)) + 1;
        childnode1->height = max(height(childnode1->left),height(childnode1->right)) + 1;

        return childnode1;
    }



    int height_difference(Node *node)
    {
        return node!=NULL? height(node->left) - height(node->right):-1;
    }

    // //get the height of the tree
    // int Treeheight(Node* node)
    // {
    //     return root==NULL ? 0:max(height(root->left),height(root->right));
    // }

    //get the maximum node 
    Node* getMax(Node* node)
    {
        Node* store = node;
        while(store->right != NULL)
            store = store->right;
        return store;
    }

    //3 orders:///////////////////////////////////////////////////
    void pre_order(Node* node)
    {
        if(node != NULL)
        {
            cout<<node->data<< " ";
            pre_order(node->left);
            pre_order(node->right);
        }
        return;
    }

    void post_order(Node* node)
    {
        if(node != NULL)
        {
            post_order(node->left);
            post_order(node->right);
            cout<<node->data<<" ";
        }
        return;
    }

    void in_order(Node* node)
    {
        if(node != NULL)
        {
            in_order(node->left);
            cout<<node->data<<" ";
            in_order(node->right);
        }
        return;
    }

    void print_tree(string move)
    {
        if(root != NULL)
        {
            if(move == "PRE")
                pre_order(root);
            else if(move == "POST")
                post_order(root);
            else if(move == "IN")
                in_order(root);
        }
        else
            cout<<"EMPTY"<<endl;
    }
};


int main()
{
	vector<string> commands;
	AVLTree my_tree;
	string temp;
	while(cin)
	{
		cin>>temp;
		commands.push_back(temp);
	}
	for(int i=0; i<commands.size()-1;i++)
	{
		my_tree.handle_input(commands[i]);
	}
	return 0;
}
	