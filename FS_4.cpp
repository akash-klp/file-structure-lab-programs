#include<iostream>
#include<fstream>
#include<string.h>
#include<stdlib.h>
using namespace std;

class student{
	int rrn_array[100], no_of_recs;
	string usn, name, sem, buffer;
	public:
	void read ();
	void pack ();
	void write_to_file ();
	void create_rrn_list ();
	void search (int);
} s;

int main (){
	int ch, rrn_no;
	cout<<"\nRRN";

	while (1){
		cout << "\nEnter\n1:Insert record 2:Search 3:Exit\n";
		cin >> ch;

		switch (ch){
			case 1:
				s.read ();
				s.pack ();
				s.write_to_file ();
				break;
			case 2:
				s.create_rrn_list ();
				cout << "\nEnter the RRN\n";
				cin >> rrn_no;
				s.search (rrn_no);
				break;
			case 3: exit(0);
		}
	}
}

void student::read (){
	cout << "\nEnter usn,name &sem\n";
	cin >> usn >> name >> sem;
}

void student::pack (){
	buffer.erase ();
	buffer += usn + "|" + name + "|" + sem + "$\n";
}

void student::write_to_file (){
	fstream fp;
	fp.open ("4.txt", ios::out | ios::app);
	fp << buffer;
	fp.close ();
}

void student::create_rrn_list (){
	int pos,rrn=0;
	fstream fp;
	fp.open ("4.txt", ios::in);
	no_of_recs = 0;
	cout<<"\nRR no.\tRecord\n";
	do{
		pos = fp.tellg ();
		rrn_array[no_of_recs++] = pos;
		getline (fp, buffer);
		if (fp.eof ())
			break;
		cout<<"\n"<<rrn<<"\t"<<buffer;
		rrn++;
	}while (1);

	fp.close ();
}

void student::search (int rrn_no){
	int pos;
	if (rrn_no <=0 || rrn_no >= no_of_recs)
		cout << "\nRecord not found\n";

	else{
		pos = rrn_array[rrn_no-1];
		fstream fp;
		fp.open ("4.txt", ios::in);
		fp.seekg (pos, ios::beg);
		cout << "\nRecord found\n";
		getline (fp, buffer);
		cout << buffer;
		fp.close ();
	}
}