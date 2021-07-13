#include<iostream>
#include<fstream>
#include<string.h>
#include<stdlib.h>
#define max 50
using namespace std;

class student
{
	char usn[20];
	char name[20];
	char sem[10];
	public:
	void read();
	void read_file();
	void pack();
	void unpack();
	void modify(char *);
	int search1(char *);
} s;

int main (){
	int ch;
	char regno[20];
	cout<<"\nFIXED LENGTH RECORDS";
	cout<<"\nSIZE OF EACH REC = "<<max;
	while (1){
		cout << "\n1:Pack 2:Unpack 3:Modify 4:Search 5:Exit\n";
		cin >> ch;
		switch (ch){
			case 1: s.read ();
					s.pack ();
					break;
			case 2: s.read_file();
					break;
			case 3: cout << "Enter USN\n";
					cin >> regno;
					s.modify (regno);
					break;
			case 4: cout << "Enter USN to search\n";
					cin >> regno;
					int f;
					f = s.search1 (regno);
					if (f == 0)
						cout << "Not found\n";
					else
						cout << "\nFound @" << f <<"position";
					break;
			case 5: exit (0);
					break;
		}
	}
}
void student::read (){
	cout << "\nEnter USN,Name & Sem\n";
	cin >> usn >> name >> sem;
}

void student::pack (){
	int i;
	fstream fp;
	fp.open ("2", ios::out | ios::app);
	fp << usn << "|" << name << "|" << sem << "|#";

	int len = strlen (usn) + strlen (name) + strlen (sem) + 4;
	for (i = len; i < max; i++)
		fp << "$";
	fp.close ();
}
void student::read_file(){	
	ifstream ifile;
	ifile.open("2");
	if(ifile)
	{
		std::ifstream ifs("2",std::ios::ate);
		if(ifs.tellg() == 0)
		{
			cout<<"No Records Inserted\n";
		}
		else
		{
			fstream fp;
			fp.open("2",ios::in);
			unpack();
		}
	}	
	else
	{
		cout<<"\nError! File open\n";
	}
}

int student::search1 (char *regno){
	int j = 0;
	fstream fp;
	fp.open ("2", ios::in);
	while (1){
		j++;
		fp.getline (usn, 20, '|');
		if (fp.fail ())
		return 0;
		if (strcmp (usn, regno) == 0){
			cout << "USN:" << usn;
			fp.getline (name, 20, '|');
			cout << "\tName:" << name;
			fp.getline (sem, 10, '|');
			cout << "\tSem:" << sem;
			fp.close ();
			return j;
		}
		else
		fp.seekg (j * max, ios::beg);
	}
}

void student::modify (char *regno){
	int i;
	fstream fp;
	fp.open ("2", ios::in | ios::out | ios::ate);
	int flag = search1 (regno);
	if (flag == 0)
		cout << "R.N.F\n";
	else{
		fp.seekp ((flag - 1) * max, ios::beg);
		read ();
		fp << usn << "|" << name << "|" << sem << "|#";
		int len = strlen (usn) + strlen (name) + strlen (sem) + 4;
		for (i = len; i < max; i++)
		fp << "$";
	}
	fp.close ();

}

void student::unpack (){
	fstream fp;
	fp.open ("2", ios::in);
	int j = 1;
	while (1){
		fp.getline (usn, 20, '|');
		if (fp.eof () == 1)
			break;
		cout << "USN:" << usn;
		fp.getline (name, 20, '|');
		cout << "\tName:" << name;
		fp.getline (sem, 10, '|');
		cout << "\tSem:" << sem << endl;
		fp.seekg (j * max, ios::beg);
		j++;
	}
fp.close ();
}