#include<iostream>
#include<fstream>
#include<string.h>
#include<stdlib.h>
using namespace std;
void reverse (char *);
int 
 main (int argc, char *argv[])
{
	char name[50];
	if (argc == 1)
	{
		do
		{
			cout << " Enter the string to be reversed ";
			cin.getline (name, 50);
			if (cin.eof ())
			break;
			reverse (name);
			cout << name;
		}while (1);
	}
	else
	{
		fstream fp1, fp2;
		char name[50];
		fp1.open (argv[1], ios::in);
		fp2.open (argv[2], ios::app);
		do
			{
				fp1.getline (name, 50);
				reverse (name);
				fp2 << name;
				if (fp1.eof ())
				break;
			}while (1);
			fp1.close ();
			fp2.close ();
	}
}
void 
reverse (char *name)
{
	int i;
	int j = strlen (name) - 1;
 	for (i = 0; i < j; i++, j--)
	{
		char tmp = name[i];
		name[i] = name[j];
		name[j] = tmp;
	}
}
