#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TABLE_SIZE 1024


struct student
{
	long long int ID;
	char name[30];
};
typedef struct student Student;


struct hash_table_element
{
	Student* s;
	int status;

};
typedef struct hash_table_element *HT;


//status : {1:filled, 2:empty, 3:deleted}

int hash(int ID, int m, int i);
void insert(struct hash_table_element *table, struct student *stud, int m);
void delete(struct hash_table_element *table, int ID, int m);
struct student *search(struct hash_table_element *table, int ID, int m);

int mulHash(int key,int size)
{
	double A = 0.6180339887;
	double frac = key*A - (int)(key * A);
	return (int)(size*frac);
}

int hash(int ID, int m, int i)
{
	(mulHash(ID,m) + i)%m;
}





void insert(struct hash_table_element *table, struct student *stud, int m)
{

	for(int i=0;i<m;i++)
	{
	  int index = hash(stud->ID, m,i);

	  if(table[i].status == 2)
	  {
	  	table[i].s = stud;
	  	table[i].status = 1;
	  }

	}

}

struct student *search(struct hash_table_element *table, int ID, int m)
{
	for(int i=0;i<m;i++)
	{
		int index = hash(ID,m,i);

		if(table[index].status == 2)
			return NULL;
		else
		{
			if(table[index].status == 1 && table[index].s->ID == ID)
				return table[index].s;
		}
	}
}



void delete(struct hash_table_element *table, int ID, int m)
{
	for(int i=0;i<m;i++)
	{
		int index = hash(ID,m,i);

		if(table[index].status == 1)
		{
			table[index].s = NULL;
			table[index].status = 3;
		}
	}
}



int main()
{
	FILE* fp = fopen("t1_data.txt","r");

	int n;

	fscanf(fp,"%d",&n);
	Student arr[n];

	for(int i=0;i<n;i++)
	{
		fscanf(fp,"%lld, %[^\n]",&arr[i].ID, arr[i].name);

	}

	struct hash_table_element hashTable[TABLE_SIZE];
	int index;
	int key;
	char t_name[30];


	

	for(int i=0;i<n;i++)
	{
		hashTable[i].status = 2;
	}

	for(int i=0;i<n;i++)
	{
		Student s = {arr[i].ID, arr[i].name};
		
		insert(hashTable,&s,n);
	}
}
