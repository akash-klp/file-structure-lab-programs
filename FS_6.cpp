#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<fstream>
#include<string>
using namespace std;
class secondary_index
{
	public:
		string name_list[100];	
		int address_list[100],count;
		void insert();
		void disp();
		void remove(string);
		void search(string);
		void readfromfile(int);	
		void delfromfile(int);
		string extract_name(string);
		void create_index();
		void sort_index();
		int search_index(string);
};
void secondary_index::disp()
{
	int i;
	cout<<"\nINDEX FILE\n";
	for(i=0;i<=count;i++)
	cout<<name_list[i]<<" "<<address_list[i]<<endl;
}
void secondary_index::create_index()
{
	fstream fp;
	int pos;
	string buffer,name;
	count=-1;
	fp.open("6.txt",ios::in);
	while(!fp.eof())
	{
		pos=fp.tellg();
		buffer.erase();
		getline(fp,buffer);
		if(buffer[0]!='*')
		{
			if(buffer.empty())
			break;
			name=extract_name(buffer);
			name_list[++count]=name;
			address_list[count]=pos;
		}
	}
	fp.close();
	sort_index();
	buffer.erase();
}
string secondary_index::extract_name(string buffer)
{
	string usn,name;
	int i=0;
	usn.erase();
	while(buffer[i]!='|')
	usn+=buffer[i++];
	name.erase();
	i++;
	while(buffer[i]!='|')
	name+=buffer[i++];
	return name;
}
void secondary_index::sort_index()
{
	int i,j,temp_address;
	string temp_name;
	for(i=0;i<=count;i++)
	{
		for(j=i+1;j<=count;j++)
		{
			if(name_list[i]>name_list[j])
			{
				temp_name=name_list[i];
				name_list[i]=name_list[j];
				name_list[j]=temp_name;
				temp_address=address_list[i];
				address_list[i]=address_list[j];
				address_list[j]=temp_address;
			}
		}
	}
}
void secondary_index::insert()
{
	string usn,name,branch,sem,buffer;
	int pos;
	fstream fp;
	cout<<"\nUSN:";
	cin>>usn;
	cout<<"\nName:";
	cin>>name;
	cout<<"\nBranch:";
	cin>>branch;
	cout<<"\nSemester: ";
	cin>>sem;
	buffer=usn+'|'+name+'|'+branch+'|'+sem+'|'+'$'+'\n';
	fp.open("6.txt",ios::out|ios::app);
	pos=fp.tellp();
	fp<<buffer;
	fp.close();
	name_list[++count]=name;
	address_list[count]=pos;
	sort_index();
}
void secondary_index::readfromfile(int pos)
{
	int address,i;
	string buffer;
	fstream fp;
	fp.open("6.txt",ios::in);
	address=address_list[pos];
	fp.seekp(address,ios::beg);
	getline(fp,buffer);
	cout<<"\nFound the record: "<<buffer;
	fp.close();
}
void secondary_index::remove(string key)
{	
	int pos=0,t,choice;
	string buffer;
	buffer.erase();
	pos=search_index(key);
	if(pos==-1)
	cout<<"\nRecord Not Found";
	else if(pos>=0)
	{
		readfromfile(pos);
		delfromfile(pos);
		t=pos;
		while(name_list[t]==key&&t>=0)
		{
			readfromfile(t);
			delfromfile(t);
			t--;
		}
		t=pos;
		while(name_list[t]==key&&t<=count)
		{
			readfromfile(t);
			delfromfile(t);
			t++;
		}
	}
}
void secondary_index::delfromfile(int pos)
{
	char delch='*';
	int i,address;
	fstream fp;
	fp.open("6.txt");
	address=address_list[pos];
	fp.seekp(address,ios::beg);
	fp.put(delch);
	cout<<"\nRecord Deleted: ";
	for(i=pos;i<count;i++) //Rearranging the LISTS
	{
		name_list[i]=name_list[i+1];
		address_list[i]=address_list[i+1];
	}
	count--;
}
void secondary_index::search(string key)
{
	int pos=0,t;
	string buffer;
	buffer.erase();
	pos=search_index(key);
	if(pos==-1)
	cout<<"\nRecord not found\n";
	else if(pos>=0)
	{
		readfromfile(pos);
		t=pos;
		while(name_list[--t]==key&&t>=0)
		readfromfile(t);
		t=pos;
		while(name_list[++t]==key&&t<=count)
		readfromfile(t);
	}
}
int secondary_index::search_index(string key)
{
	int low=0,high=count,mid=0,flag=0,pos;
	while(low<=high)
	{
		mid=(low+high)/2;
		if(name_list[mid]==key)
		{
			flag=1;
			break;
		}
		if(name_list[mid]>key)
		high=mid-1;
		if(name_list[mid]<key)
		low=mid+1;
	}
	if(flag)
	return mid;
	else
	return -1;
}
main()
{
	int choice;
	string key;
	secondary_index i1;
	i1.create_index();
	cout<<"\nSECONDARY INDEX ON Name";
	while(1)
	{
		cout<<"\n1.Add 2.Search 3.Delete 4.Exit\n";
		cout<<"Enter Choice: ";
		cin>>choice;
		switch(choice)
		{
			case 1: i1.insert();
			i1.disp();
			break;
			case 2: i1.disp();
			cout<<"\nEnter the name to display records : ";
			cin>>key;
			i1.search(key);
			break;
			case 3: cout<<"\nEnter the name to remove records: ";
			cin>>key;
			i1.remove(key);
			break;
			case 4: return 0;
			default: cout<<"\nWrong Choice\n";
			break;
		}
	}
}