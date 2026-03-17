#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>




typedef struct node {
    int value;
    struct node *left;
    struct node *right;
} Node;


typedef struct bst {
    Node *root;
} BST;

BST *new_bst() 
{
    BST *bst = malloc(sizeof(BST));
    bst->root = NULL;
    return bst;
}

Node *new_node(int value) 
{
    Node *node = malloc(sizeof(Node));
    node->value = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void traverse_in_order(Node *node)
{
    if (node == NULL)
    {
        return;
    }
    traverse_in_order(node->left);
    printf("%d ", node->value);
    traverse_in_order(node->right);
}

void insert(BST *bst, int value)
{
    Node *node = new_node(value);
    if (bst->root == NULL) 
    {
        bst->root = node;
        return;
    }
    Node *current = bst->root;
    while (current != NULL) 
    {
        if (value < current->value) 
        {
            if (current->left == NULL) 
            {
                current->left = node;
                return;
            }
            current = current->left;
        } 
        else 
        {
            if (current->right == NULL) 
            {
                current->right = node;
                return;
            }
            current = current->right;
        }
    }
}

int search(BST *bst, int key)
{
    Node *current = bst->root;
    while (current != NULL) 
    {
        if (key == current->value) 
        {
            return 1;
        } 
        else if (key < current->value) 
        {
            current = current->left;
        } 
        else 
        {
            current = current->right;
        }
    }
    return 0;
}

int find_min(BST *bst)
{
    Node *current = bst->root;
    while (current->left != NULL) 
    {
        current = current->left;
    }
    return current->value;
}

int find_max(BST *bst)
{
    Node *current = bst->root;
    while (current->right != NULL) 
    {
        current = current->right;
    }
    return current->value;
}

Node *predecessor(Node *node) // predeccessor : largest node smaller than the given node
{
    if (node->left == NULL) // there is no node smaller than this node
    {
        return NULL;
    }
    Node *current = node->left; // the left subtree has all nodes smaller than the current node
    // the left child helps access all the smaller nodes
    while (current->right != NULL)
    {
        current = current->right;
    } // traverse to the leaf of the right subtree of the left child of the given node to find the 
    // largest node smaller than the given node
    return current;
}

Node *successor(Node *node) // successor: smallest number greater than the node
{
    if (node->right == NULL) // there is no node higher than this node
    {
        return NULL;
    }
    Node *current = node->right; // start to traverse the right child of the node(this or its children are successors)
    while (current->left != NULL) 
    {
        current = current->left;
    } // smallest successor is the leaf node of the left subtree of the right child of the node
    return current;
}

void delete(BST *bst, Node *node)
{
    if (node == NULL)
        return;

    if (node->left == NULL && node->right == NULL) // Case: Leaf node
    {
        // Node is a leaf
        Node* current = bst->root;

        // if the node is a leaf, traverse to its parent, then the node can be either the left
        // or right child of this parent node, just make the parent point to null to remove the node
        // if the current node is not the parent of the node to be removed, check if the node can be 
        // found in the left subtree or the right subtree 
        // for this compare the value contained in the node with its left and right children and move the 
        // current pointer accordingly

        while (current != NULL)
        {
            if (current->left == node)
            {
                current->left = NULL;
                break;
            }
            if (current->right == node)
            {
                current->right = NULL;
                break;
            }
            if (node->value < current->value)
            {
                current = current->left;
            }
            else
            {
                current = current->right;
            }
        }
        free(node);
        return;
    }
    
    if (node->left == NULL)  // Node only has right child
    {
       
        Node* current = bst->root;
        if (current == node) // if the node to be deleted is the root node, and it has only the right child
            // the root is updated to be the right child
        {
            bst->root = node->right;
            free(node);
            return;
        }


        // otherwise : non leaf, non root node
        while (current != NULL)
        {
            if (current->left == node) // if left child of current node is to be deleted, point the left child
                // to the right child of the node to be deleted(since we know that in has only the right child)
            {
                current->left = node->right;
                break;
            }
            if (current->right == node)
            {
                current->right = node->right;
                break;
            }

            // if the node to be deleted is not the child of the current node then shift to the 
            // left or right child node accordingly
            if (node->value < current->value)
            {
                current = current->left;
            }
            else
            {
                current = current->right;
            }
        }
        free(node);
        return;
    }

    if (node->right == NULL) // Node only has left child
    {
        
        Node* current = bst->root;
        if (current == node) // node to be deleted is the root
        {
            bst->root = node->left;
            free(node);
            return;
        }
        while (current != NULL)
        {
            //node to be deleted is the left or right child of some node

            if (current->left == node)
            {
                current->left = node->left;
                break;
            }
            if (current->right == node)
            {
                current->right = node->left;
                break;
            }
            if (node->value < current->value)
            {
                current = current->left;
            }
            else
            {
                current = current->right;
            }
        }
        free(node);
        return;
    }

    // Node has both children
    Node *temp = successor(node);
    node->value = temp->value;
    delete(bst, temp);
    return;
}

void traverse_pre_order(Node *node)
{
    if(node == NULL)
        return;
    printf("%d ", node->value);
    traverse_pre_order(node->left);
    traverse_pre_order(node->right);

}

void traverse_post_order(Node *node)
{
    if(node == NULL)
        return;
    traverse_post_order(node->left);
    traverse_post_order(node->right);
    printf("%d ", node->value);
}

void in_order_null(Node *node)
{
    if (node == NULL)
    {
       printf("null ");
       return;
    }
    in_order_null(node->left);
    printf("%d ", node->value);
    in_order_null(node->right);

}

void pre_order_null(Node *node)
{
    if(node == NULL)
    {
        printf("null ");
        return;
    }
    printf("%d ", node->value);
    pre_order_null(node->left);
    pre_order_null(node->right);
}

void post_order_null(Node *node)
{
    if(node == NULL)
    {
        printf("null ");
        return;
    }
   post_order_null(node->left);
    post_order_null(node->right);
    printf("%d ", node->value);
}

BST* constructBST(int A[], int n)
{

    BST *myBST = new_bst();

    for(int i =0;i<n;i++)
    {
        insert(myBST,A[i]);

    }

    return myBST;
}





/*
void removeHalfNodes(BST *bst) //Doubt
{
    Node *current = bst->root;
    if(bst == NULL)
        return;

    // check if current node is a half node

    if(current->left != NULL && current->right == NULL) // only left child
    {
        Node *temp = current->parent;
        temp->left = current->left;
        free(current);
        return;
    }

    if(current->right != NULL && current->left == NULL) // only right child
    {
        Node *temp = current->parent;
        temp->left = current->left;
        free(current);
        return;
    

    


    // identify nodes having either only left or right child
    // remove them
    //maintain BST property                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     

}*/








int checkBstHelper(Node *node,int min, int max)
{
    if(node == NULL)
        return 1;
    if(node->value <= min || node->value >= max)
        return 0;

    return checkBstHelper(node->left,min,node->value) && checkBstHelper(node->right, node->value, max);

}


int checkBSTRec(BST *bst)
{
    int min = find_min(bst);
    int max = find_max(bst);
    

    // Base case : An empty tree is always a BST
    if(bst == NULL)
        return 1;

    return checkBstHelper(bst->root, INT_MIN, INT_MAX);
}



int max(int a, int b)
{
    if(a>b)
        return a;
    else
        return b;
}

int height(Node *node)
{
    Node *current = node;

    if(node == NULL)
        return -1;

    return 1 + max(height(current->left),height(current->right));
    

}
/*
void removeHalfNode(BST *bst)
{
    Node* current = bst->root;

    // checking left subtree of root
    while(current != NULL)
    { 
    
        
        // delete that node while maintaining BST property

        //halfnode is root
        if(current == bst->root)
        {
            if(current->left !=NULL && current->right==NULL)
            {
                bst->root = current->left;
                free(current);
                
            }
           if(current->left ==NULL && current->right!=NULL)
            {
                bst->root = current->right;
                free(current);
                
            }
        }

        
        else // non root half nodes
        {
        if(current->value < current->parent->value) // current node is left node
        {
            if(current->left !=NULL && current->right==NULL) // current node has only left child
            {
                current->parent->left = current->left;

            }
            if(current->left ==NULL && current->right!=NULL) // current node has only right child
            {
                current->parent->left = current->right;
            }
        }

        else // current node is right node
        {
            if(current->left !=NULL && current->right==NULL) // current node has only left child
            {
                current->parent->right = current->left;

            }
            if(current->left ==NULL && current->right!=NULL) // current node has only right child
            {
                current->parent->right = current->right;
            }
        }

         }

         current = current->left;
    }

     while(current != NULL)
    { 
    
        
        // delete that node while maintaining BST property

        //halfnode is root
        if(current == bst->root)
        {
            if(current->left !=NULL && current->right==NULL)
            {
                bst->root = current->left;
                free(current);
                
            }
           if(current->left ==NULL && current->right!=NULL)
            {
                bst->root = current->right;
                free(current);
                
            }
        }

        
        else // non root half nodes
        {
        if(current->value < current->parent->value) // current node is left node
        {
            if(current->left !=NULL && current->right==NULL) // current node has only left child
            {
                current->parent->left = current->left;

            }
            if(current->left ==NULL && current->right!=NULL) // current node has only right child
            {
                current->parent->left = current->right;
            }
        }

        else // current node is right node
        {
            if(current->left !=NULL && current->right==NULL) // current node has only left child
            {
                current->parent->right = current->left;

            }
            if(current->left ==NULL && current->right!=NULL) // current node has only right child
            {
                current->parent->right = current->right;
            }
        }

         }

         current = current->right;
    }




}

*/







// Driver program to test the above functions (feel free to play around with this)
int main()
{
    BST *bst = new_bst();
    insert(bst, 2);
    insert(bst, 1);
    insert(bst, 3);
    insert(bst, 4);
    insert(bst, 5);
    insert(bst, 6);
    insert(bst, 7);
    insert(bst, 8);

    printf("In-order\n");
   traverse_in_order(bst->root);
   printf("\n");
   printf("Pre-order\n");
    traverse_pre_order(bst->root);
    printf("\n");
    printf("Post-order\n");
    traverse_post_order(bst->root);
    printf("\n");

printf("in-order-null\n");
    in_order_null(bst->root);
     printf("\n");
     printf("Pre-order-null\n");
     pre_order_null(bst->root);
     printf("\n");
     printf("Post-order-null\n");
     post_order_null(bst->root);
     printf("\n");

    int A[] = {1,2,3,4,5,6,7,8,};
    int k =8;
    BST *myBST = constructBST(A,k);

    printf("constructed BST in-order\n");
    traverse_in_order(myBST->root);
    printf("\n");
    printf("constructed BST pre-order\n");
    traverse_pre_order(bst->root);
    printf("\n");

    FILE* fp = fopen("n_integers.txt","r");
    int n;
    //read the first integer
    fscanf(fp,"%d",&n);
    int *arr = (int*)malloc(n*sizeof(int));
    char ch;

    while((ch = fgetc(fp))!=EOF)
    {
        if(isdigit(ch))
        {
            ungetc(ch,fp);
            break;
        }
    }

    // input from file
    for(int i=0;i<n;i++)
    {
        fscanf(fp, "%d", &arr[i]);
    }

    //BST creation

    BST *bst1 = constructBST(arr,n);


//   traverse_in_order(bst1->root);
  //  printf("\n");


    if(checkBSTRec(myBST) == 1)
        printf("IS BST \n");
    else
        printf("IS NOT BST \n");


    printf("Height : %d \n",height(bst1->root));

   


    /*
    printf("Max = %d\n", find_max(bst));
    printf("Min = %d\n", find_min(bst));
    printf("Predecessor of root = %d\n", predecessor(bst->root)->value);
    printf("Successor of root = %d\n", successor(bst->root)->value);
    delete(bst, bst->root->left);
    traverse_in_order(bst->root);
    printf("\n");
    delete(bst, bst->root->right);
    traverse_in_order(bst->root);
    printf("\n");
    delete(bst, bst->root);
    traverse_in_order(bst->root);
    printf("\n");
    */
    free(arr);
    return 0;
}
