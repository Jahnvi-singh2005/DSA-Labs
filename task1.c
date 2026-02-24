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
	Student data;
	struct node* next;
};
typedef struct node* NODE;

int hash1(long long key, int size)
{
	return key%m;
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

	NODE hashTable[2*n];

	char ch;

	for(int i=0;i<n;i++)
	{
		fscanf(fp,"%lld, %[^\n]",&arr[i].ID, arr[i].name);
	}

	for(int i=0;i<n;i++)
	{
		printf("%lld \t %s \n",arr[i].ID, arr[i].name);
	}

	return 0;
}
