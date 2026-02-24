#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct student
{
	long long int ID;
	char name[30];
};
typedef struct student Student;



int main()
{

	FILE* fp = fopen("t1_data.txt","r");

	int n;

	fscanf(fp,"%d",&n);

	Student arr[n];

	

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