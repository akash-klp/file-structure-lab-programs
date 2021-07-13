#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<fstream>
#include<string>
using namespace std;
class coseq
{
	private:
	string list1[100],list2[100];
	int count1,count2;
	public:
	coseq(){count1=0;count2=0;}// constructor
	void read();
	void create_lists();
	void sort();
	void match();
}cp;
main()
{
	cout<<"\nCosequestial Matching";
	cout<<"\nInput Files 7a.txt & 7b.txt";
	cout<<"\nOutput File match.txt";
	cp.read();
	cp.create_lists();
	cp.sort();
	cp.match();
}
void coseq::read()
{
	int i=1,j=1;
	string name;
	cout<<"\nList1 no of names :\n";
	cin>>count1;//10
	fstream fp;
	fp.open("7a.txt",ios::out|ios::app);
	while(i<=count1)
	{
		cout<<"Enter the name\n";
		cin>>name;
		fp<<name<<"\n";
		i++;
	}
	fp.close();
	cout<<"\nList2 no of names :\n";
	cin>>count2;//10
	fp.open("7b.txt",ios::out|ios::app);
	while(j<=count2)
	{
		cout<<"Enter the name\n";
		cin>>name;
		fp<<name<<"\n";
		j++;
	}
	fp.close();
}
void coseq::create_lists()
{
	fstream fp;
	string name;
	count1 = 0;
	count2 = 0;
	fp.open("7a.txt",ios::in);
	do{
		getline(fp,name);
		if(fp.eof())
		break;
		list1[count1++]=name;
	}while(1);
	fp.close();
	fp.open("7b.txt",ios::in);
	do{
		getline(fp,name);
		if(fp.eof())
		break;
		list2[count2++]=name;
	}while(1);
	fp.close();
}
void coseq::sort()
{
	string temp;
	int i,j;
	for(i=0;i<count1;i++)
	{
		for(j=0;j<count1-i-1;j++)
		{
			if(list1[j]>list1[j+1])
			{
				temp=list1[j];
				list1[j]=list1[j+1];
				list1[j+1]=temp;
			}
		}
	}
	for(i=0;i<count2;i++)
	{
		for(j=0;j<count2-i-1;j++)
		{
			if(list2[j]>list2[j+1])
			{
				temp=list2[j];
				list2[j]=list2[j+1];
				list2[j+1]=temp;
			}
		}
	}
}
void coseq::match()
{
	int i=0,j=0;
	fstream fp;
	fp.open("match.txt",ios::out|ios::app);
	cout<<"\nMatched List :";
	while(i<count1 && j<count2)
	{
	// for eliminating same names
		while(list1[i]==list1[i+1])i++;
		while(list2[j]==list2[j+1])j++;
		if(list1[i]<list2[j])
		i++;
		else if(list1[i]>list2[j])
		j++;
		else
		{
			fp<<list1[i]<<"\n";
			cout<<endl;
			cout<<list1[i];
			i++;
			j++;
		}
	}
	fp.close();
	cout<<"\nMatched file name match.txt";
}