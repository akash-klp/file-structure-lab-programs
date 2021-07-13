#include<iostream>
#include<fstream>
#include<string.h>
#include<stdlib.h>
using namespace std;

class student{	
	string usn,name,sem,buffer;
	public:
	void unpack();
	void read();
	void read_file();
	void write_file();
	void display();
	void pack();
	int del(string);
	void modify(string);
	int search1(string);
}s;

int main(){
	int ch;
	string regno;
	cout<<"\nVARIABLE LENGTH RECORDS";
	while(1){
		cout<<"\n1:Pack 2:Unpack 3:Search 4:Modify 5:exit\n";
		cin>>ch;
		switch(ch){
			case 1:
				s.read();
				s.pack();
				s.write_file();
				break;
			case 2:
				s.read_file();
				break;
			case 3:
				cout<<"Enter regno to search\n";
				cin>>regno;
				s.search1(regno);
				break;
			case 4:
				cout<<"Enter regno to search\n";
				cin>>regno;
				s.modify(regno);
				break;
			default : exit(0);
		}
	}
}

void student::read(){
	cout<<"Enter details[USN,Name,Sem]\n";
	cin>>usn>>name>>sem;
}

void student::pack(){
	buffer.erase();
	buffer+=usn+"|"+name+"|"+sem+"$\n";
}

void student::read_file(){	
	ifstream ifile;
	ifile.open("3");
	if(ifile)
	{
		std::ifstream ifs("3",std::ios::ate);
		if(ifs.tellg() == 0){
			cout<<"No Records Inserted\n";
		}
		else{
			fstream fp;
			fp.open("3",ios::in);
			while(!fp.eof())
			{
				buffer.erase();
				getline(fp,buffer);
				unpack();
				if(!fp.eof()&&buffer[0]!='*')
					display();
			}
		fp.close();
		}	
	}
	else{
		cout<<"\nError! File open\n";
	}
}

void student::unpack(){
	int i=0;
	usn.erase();
	while(buffer[i]!='|')
		usn+=buffer[i++];
	i++;
	name.erase();
	while(buffer[i]!='|')
		name+=buffer[i++];
	i++;
	sem.erase();
	while(buffer[i]!='$')
		sem+=buffer[i++];
}

void student::display(){
	cout<<"Usn:"<<usn<<" Name:"<<name<<" Sem:"<<sem<<endl;
}

int student::search1(string regno){
	fstream fp;
	int recno=0,flag=0,pos=0;
	fp.open("3",ios::in);
	while(!fp.eof()){
		buffer.erase();
		getline(fp,buffer);
		if(buffer[0]!='*') //check the buffer ==*
			recno++;
		unpack();
		if(usn==regno){
			cout<<"\nRecord is "<<buffer;
			cout<<"\nRecord Found at Position "<<recno << endl;
			pos=fp.tellg();
			flag=1;
			return pos;
		}
	}
	fp.close();
	if(!flag)
		cout<<"Record not found\n";
	return pos;
}
int student::del(string regno){
	fstream fp;
	char mark='*',t;
	int pos,flag=0;
	pos=search1(regno);
	if(pos){
		fp.open("3",ios::in|ios::out);
		pos-=2;
		cout<<"delelted record position "<<pos;
		t=fp.get();
		while(t!='$'&&pos!=0){
			pos--;
			fp.seekp(pos,ios::beg);
			t=fp.get();
		}
		if(pos!=0)
			fp.seekp(pos+2,ios::beg);
		else
			fp.seekp(pos,ios::beg);
		fp.put(mark);
		flag=1;
	}
	fp.close();
	if(!flag)
		return 0;
	else
		return 1;
}

void student::modify(string regno){
	if(del(regno)){
		cout<<"\nEnter details[USN,Name,Sem] to modify\n";
		cin>>usn>>name>>sem;
		buffer.erase();
		pack();
		write_file();
	}
}

void student::write_file(){
	fstream fp;
	fp.open("3",ios::out|ios::app);
	fp<<buffer;
	fp.close();
}