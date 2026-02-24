#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct student
{
	long long int ID;
	char name[30];
};
typedef struct student Student;

//Since chaining, we create nodes

struct node
{
	Student ele;
	struct node* next;
};
typedef struct node* NODE;

typedef struct linked_list* LIST;
struct linked_list{
	int count;
	NODE head;
};

LIST createNewList()
{
	LIST myList;
	myList = (LIST) malloc(sizeof(struct linked_list));
	myList->count=0;
	myList->head=NULL;
	return myList;
}

NODE createNewNode(Student value)
{
	NODE myNode;
	myNode = (NODE) malloc(sizeof(struct node));
	myNode->ele=value;
	myNode->next=NULL;
	return myNode;
}

void insertFirst(NODE n1, LIST l1)
{

	if(l1->count == 0)
		{
			l1->head = n1;
			n1->next = NULL;
			l1->count++;
			return;
		}
	else
	{
		NODE temp = l1->head;
		n1->next = temp;
		l1->head = n1;
		l1->count++;
		return;
		
		 
	}
	
}


int hash1(long long key, int size)
{
	return key%size;
}

int hash2(long long key, int size)
{
	int pow = 1;

	while(pow<size)
	{
		pow = pow*2;
	}
	return key%pow;
}

int hash3(long long key, int size)
{
	
	int c =0;
	int n =2;
	int prime = n;
	int flag;
	while(prime < size)
	{
		flag = 1;
		for(int i=2;i<n;i++)
		{
			if(n%i==0)
			{
				flag = 0;
				break;
			}

		}
		if(flag)
			prime = n;

		n++;
	}
	return key % prime;
}

int hash4(long long key, int size)
{
	double A = 0.6180339887;
	double frac = key*A - (int)(key * A);
	return (int)(size*frac);
}

int hash5(long long key, int size)
{
	int c =0;
	int n =2;
	int prime = n;
	int flag;
	while(prime < 0.9*size)
	{
		flag = 1;
		for(int i=2;i<n;i++)
		{
			if(n%i==0)
			{
				flag = 0;
				break;
			}

		}
		if(flag)
			prime = n;

		n++;
	}
	return key % prime;
}

int hash6(long long key, int size)
{
	int c =0;
	int n =2;
	int prime = n;
	int flag;
	while(prime < 0.9*size)
	{
		flag = 1;
		for(int i=2;i<n;i++)
		{
			if(n%i==0)
			{
				flag = 0;
				break;
			}

		}
		if(flag)
			prime = n;

		n++;
	}

	return (key* prime)%size;

}



int main()
{

	FILE* fp = fopen("t1_data.txt","r");

	int n;

	fscanf(fp,"%d",&n);

	Student arr[n];

		LIST hashTable[2*n];

		for(int i=0;i<2*n;i++)
		{
			hashTable[i] = createNewList();
		}

	char ch;

	int key;
	char t_name[30];
	int num_col = 0;


	

	//Reading input
	for(int i=0;i<n;i++)
	{
		fscanf(fp,"%lld, %[^\n]",&arr[i].ID, arr[i].name);

	}

	int ind;
	for(int i=0;i<n;i++)
	{
		key = arr[i].ID;
		strcpy(t_name,arr[i].name);

		Student s = {key,t_name};

		NODE temp = createNewNode(s);

		ind = hash1(key,n);

		if(hashTable[ind]->head != NULL)
			num_col+=1;

		insertFirst(temp,hashTable[ind]);

		
		free(temp);
		
	}
	printf("No. of collisions for hash1 : %d \n",num_col);

	num_col =0;

	for(int i=0;i<n;i++)
	{
		key = arr[i].ID;
		strcpy(t_name,arr[i].name);

		Student s = {key,t_name};

		NODE temp = createNewNode(s);

		ind = hash2(key,n);

		if(hashTable[ind]->head != NULL)
			num_col+=1;

		insertFirst(temp,hashTable[ind]);

		
		free(temp);
		
	}
	printf("No. of collisions for hash2 : %d \n",num_col);
	num_col =0;

	for(int i=0;i<n;i++)
	{
		key = arr[i].ID;
		strcpy(t_name,arr[i].name);

		Student s = {key,t_name};

		NODE temp = createNewNode(s);

		ind = hash3(key,n);

		if(hashTable[ind]->head != NULL)
			num_col+=1;

		insertFirst(temp,hashTable[ind]);

		
		free(temp);
		
	}
	printf("No. of collisions for hash3 : %d \n",num_col);
	num_col =0;

	for(int i=0;i<n;i++)
	{
		key = arr[i].ID;
		strcpy(t_name,arr[i].name);

		Student s = {key,t_name};

		NODE temp = createNewNode(s);

		ind = hash4(key,n);

		if(hashTable[ind]->head != NULL)
			num_col+=1;

		insertFirst(temp,hashTable[ind]);

		
		free(temp);
		
	}
	printf("No. of collisions for hash4 : %d \n",num_col);
	num_col =0;
	for(int i=0;i<n;i++)
	{
		key = arr[i].ID;
		strcpy(t_name,arr[i].name);

		Student s = {key,t_name};

		NODE temp = createNewNode(s);

		ind = hash5(key,n);

		if(hashTable[ind]->head != NULL)
			num_col+=1;

		insertFirst(temp,hashTable[ind]);

		
		free(temp);
		
	}
	printf("No. of collisions for hash5 : %d \n",num_col);
num_col =0;
	for(int i=0;i<n;i++)
	{
		key = arr[i].ID;
		strcpy(t_name,arr[i].name);

		Student s = {key,t_name};

		NODE temp = createNewNode(s);

		ind = hash6(key,n);

		if(hashTable[ind]->head != NULL)
			num_col+=1;

		insertFirst(temp,hashTable[ind]);

		
		free(temp);
		
	}
	printf("No. of collisions for hash6: %d \n",num_col);
num_col =0;




	

	return 0;
}
