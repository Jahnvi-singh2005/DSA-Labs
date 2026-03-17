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

Node *predecessor(Node *node)
{
    if (node->left == NULL)
    {
        return NULL;
    }
    Node *current = node->left;
    while (current->right != NULL)
    {
        current = current->right;
    }
    return current;
}

Node *successor(Node *node)
{
    if (node->right == NULL)
    {
        return NULL;
    }
    Node *current = node->right;
    while (current->left != NULL)
    {
        current = current->left;
    }
    return current;
}

void delete(BST *bst, Node *node)
{
    if (node == NULL)
        return;
    if (node->left == NULL && node->right == NULL)
    {
        // Node is a leaf
        Node* current = bst->root;
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
    
    if (node->left == NULL)
    {
        // Node only has right child
        Node* current = bst->root;
        if (current == node)
        {
            bst->root = node->right;
            free(node);
            return;
        }
        while (current != NULL)
        {
            if (current->left == node)
            {
                current->left = node->right;
                break;
            }
            if (current->right == node)
            {
                current->right = node->right;
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

    if (node->right == NULL)
    {
        // Node only has left child
        Node* current = bst->root;
        if (current == node)
        {
            bst->root = node->left;
            free(node);
            return;
        }
        while (current != NULL)
        {
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

/*int checkBSTIte(BST *bst)
{
    if(bst == NULL)
        return 1;


}*/

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
   // traverse_in_order(bst->root);
   //printf("\n");
    //traverse_pre_order(bst->root);
    //printf("\n");
    //traverse_post_order(bst->root);
    //printf("\n");

    /*in_order_null(bst->root);
     printf("\n");
     pre_order_null(bst->root);
     printf("\n");
     post_order_null(bst->root);
     printf("\n");*/

    int A[] = {1,2,3,4,5,6,7,8,};
    int k =8;
    BST *myBST = constructBST(A,k);
    //traverse_in_order(myBST->root);
    //printf("\n");
    //traverse_pre_order(bst->root);
    //printf("\n");

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

    traverse_in_order(bst1->root);
    printf("\n");


    if(checkBSTRec(myBST) == 1)
        printf("IS BST \n");
    else
        printf("IS NOT BST \n");


    printf("Height : %d ",height(bst1->root));



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
