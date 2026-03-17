#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

typedef struct person
{
int id;
char *name;
int age;
int height;
int weight;
}Person;


typedef struct node {
    Person value;
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

Node *new_node(Person value) 
{
    Node *node = malloc(sizeof(Node));
    node->value = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void printStruct(Person p)
{
    printf("%d , %s, %d, %d, %d \n",p.id, p.name, p.age, p.height, p.weight);
}

void traverse_in_order(Node *node)
{
    if (node == NULL)
    {
        return;
    }
    traverse_in_order(node->left);
    printStruct(node->value);
    traverse_in_order(node->right);
}

void insert(BST *bst, Person value)
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
        if (value.height < current->value.height) 
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




BST* constructBST(Person A[], int n)
{

    BST *myBST = new_bst();

    for(int i =0;i<n;i++)
    {
        insert(myBST,A[i]);

    }

    return myBST;
}

Node* search(BST *bst, int key)
{
    Node *current = bst->root;
    while (current != NULL) 
    {
        if (key == current->value.id) 
        {
            return current;
        } 
        else if (key < current->value.id) 
        {
            current = current->left;
        } 
        else 
        {
            current = current->right;
        }
    }
    return NULL;
}


Node* LCA(BST *bst, int id1, int id2)
{

    Node *p = search(bst,id1);
    Node *q = search(bst,id2);

    Node* current = bst->root;

    while(current != NULL)
    {
        if((p->value.height < current->value.height) && (q->value.height > current->value.height) ||(p->value.height > current->value.height) && (q->value.height < current->value.height) ) // 
        {
            return current;
        }

        else
        {
            if((p->value.height < current->value.height) && (q->value.height < current->value.height))
            {
                current = current->left;
            }
            if((p->value.height > current->value.height) && (q->value.height > current->value.height))
            {
                current = current->right;
            }
        }
    }


}












void printArray(Person a[], int n)
{
    printf("id \t name \t age \t height \t weight \n");
    for(int i=0;i<n;i++)
    {
        printf("%d \t %s \t %d \t %d \t %d \t \n",a[i].id, a[i].name, a[i].age, a[i].height, a[i].weight);
    }
}






// Driver program to test the above functions (feel free to play around with this)
int main()
{
    
    Person *arr1 = (Person*) malloc(10*sizeof(Person));
    /*FILE *fp;
    fp = fopen("data10.csv","r");

    if(!fp)
        printf("error\n");
    else
    {
        char buffer[1024];
        int i =0;
        while(fgets(buffer,1024,fp))
        {
            fscanf(fp,"%d,%[^,],%d,%d,%d",&arr1[i].id,arr1[i].name,&arr1[i].age,&arr1[i].height,&arr1[i].weight);
                i++;
        }
    }
*/

    Person A[]= {
          {0,"Donald Scantling",39,77,231},
           { 1,"Levi Maier",56,77,129},
           { 2,"Barbara Donnelly",63,78,240},
            {3,"Dorothy Helton",47,72,229},
           { 4,"Florence Smith",24,75,171},
            {5,"Erica Anyan",38,73,102},
            {6,"Norma Webster",23,75,163},
           { 7,"Randell Jones",44,78,204},
            {8,"Nancy Shipman",29,63,272},
            {9,"Jessica Meyer",79,63,246},
            {10,"Susan Harrison",96,75,135}
    };
    
    BST *myBST = constructBST(A,10);

    traverse_in_order(myBST->root);


    printStruct(LCA(myBST,3,7)->value);

    return 0;
}
