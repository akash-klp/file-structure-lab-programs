#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<fstream>
#include<string>
using namespace std;
class merge
{
	string list[100];
	char filename[30];
	int n;//NAMES FOR INSERTION
	int cur_index;
	public: merge ()
	{
		n = 0;
		cur_index = 0;
	}
	void read ();
	void sort ();
	string currentitem ();
	int check ();
	void update (string);
}
m[10];
void	merge::update (string minele)
{
	while (list[cur_index] == minele && cur_index < n)
	cur_index++;
}
string merge::currentitem ()
{
	return (list[cur_index]);
}
int merge::check ()
{
	if (cur_index >= n)
	return 0;
	else
	return 1;
}
void	merge::read ()
{
	cout << "\nEnter filename(With .txt extension) : ";
	cin >> filename;
	fstream fp;
	fp.open (filename, ios::out);
	cout << "Enter no of keys : ";
	cin >> n;//>5
	int i = 0;
	cout << "\nEnter " << n << " keys :\n";
	while (i < n)
	{
		cin >> list[i];
		fp << list[i] << "\n";
		i++;
	}
	fp.close ();
}
void	merge::sort ()
{
	for (int i = 0; i < n; i++)
	for (int j = 0; j < n - i - 1; j++)
	if (list[j] > list[j + 1])
	{
		string temp = list[j];
		list[j] = list[j + 1];
		list[j + 1] = temp;
	}
	fstream fp;
	fp.open (filename, ios::out);
	for (int k = 0; k < n; k++)
	fp << list[k];
}
main ()
{
	int nooffiles = 0;
	cout<<"\nK-Way Merging";
	cout << "\nEnter no of files : ";
	cin >> nooffiles;//8
	int i = 0;
	while (i < nooffiles)
	{
		m[i].read ();
		m[i].sort ();
		i++;
	}
	string list[10];
	fstream fp;
	fp.open ("mergedfile.txt", ios::out);
	int index = 0;
	int flag = 0;
do
{
	flag = 0;
	index = 0;
	for (int i = 0; i < nooffiles; i++)
	list[i] = "";// NO ELEMENTS
	for (int i = 0; i < nooffiles; i++)
	{
		if (m[i].check ())
		{
			list[index++] = m[i].currentitem ();
			flag = 1;
		}
	}
	if (flag)
	{
		string min = list[0];
		for (int i = 1; i < index; i++)
		if (min > list[i])
		min = list[i];
		cout << "\nCurrent MinEle = " << min;
		fp << min << "\n";
		for (int i = 0; i < nooffiles; i++)
		{
			m[i].update (min);
		}
	}
}
while (flag);
fp.close ();
cout << "\n\n\tMerged file name is mergedfile.txt \n";
system ("mergedfile.txt");
return 0;
}