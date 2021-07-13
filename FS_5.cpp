#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
using namespace std;

class primaryindex {
    public:
    string usnlist[100];
    int count,addlist[100];
    void createindex();
    void remove(string);
    void insert();
    int searchindex(string);
    void search(string);
    void sortindex();
    string extractusn(string);
};

int main(){
    int ch;
    string key;
    primaryindex p;
    p.createindex();
    cout<<"\nSIMPLE INDEX ON USN";

    while(1){
        cout<<"\nEnter 1:Add a record 2:Search 3:Delete 4:Exit\n";
        cout<<"enter your choice\n";
        cin>>ch;
        switch(ch){
            case 1: cout<<"data\n";
                    p.insert();
                    break;

            case 2: cout<<"Enter usn\n";
                    cin>>key;
                    p.search(key);
                    break;

            case 3: cout<<"Enter usn\n";
                    cin>>key;
                    p.remove(key);
                    break;

            case 4: exit(0);
                    //break;

            default:cout<<"Invalid option\n";
                    break;
        }
    }
}

void primaryindex::createindex(){
     fstream file;
     int pos;
     string buffer,usn;
     count=-1;
     file.open("5.txt",ios::in);
     
    while(!file.eof()){
        pos=file.tellg();
        buffer.erase();
        getline(file,buffer);
        if(buffer[0]!='*'){
            if(buffer.empty())
                break;
            usn=extractusn(buffer);
            usnlist[++count]=usn;
            addlist[count]=pos;
        }
    } 
    file.close();
    sortindex();
    buffer.erase();
}

string primaryindex::extractusn(string buffer){
    string usn;
    int i=0;
    usn.erase();
    while(buffer[i]!='|')
        usn+=buffer[i++];
    return usn;
}

void primaryindex::insert(){
    string usn,name,branch,sem,buffer;
    int semister,pos;
    fstream file;
    cout<<"Enter values for usn,name,branch,sem\n";
    cin>>usn>>name>>branch>>sem;
    buffer=usn+"|"+name+"|"+branch+"|"+sem+"$\n";
 
    file.open("5.txt",ios::out|ios::app);
    pos=file.tellp();
    file<<buffer;
    file.close();
    usnlist[++count]=usn;
    addlist[count]=pos;
    sortindex();
}

void primaryindex::sortindex(){
    int i,j,tempadd;
    string tempusn;
    for(i=0;i<=count;i++){
        for(j=i+1;j<=count;j++){
            if(usnlist[i]>usnlist[j]){
                tempusn=usnlist[i];
                usnlist[i]=usnlist[j];
                usnlist[j]=tempusn;
                tempadd=addlist[i];
                addlist[i]=addlist[j];
                addlist[j]=tempadd;
            }
        }
    }
    cout<<"\n\tINDEXLIST";
    cout<<"\nUSN\t\tADDRESS";
    for(i=0;i<=count;i++)
        cout<<"\n"<<usnlist[i]<<"\t\t"<<addlist[i];
}

void primaryindex::search(string key){
    int pos=0,t;
    string buffer;
    fstream file;
    buffer.erase();
    pos=searchindex(key);
    if(pos==-1)
        cout<<"Record not found\n";
    else if(pos>=0){
        file.open("5.txt");
        t=addlist[pos];
        file.seekp(t,ios::beg);
        getline(file,buffer);
        cout<<"Record found\n";
        cout<<"\nRecord:"<<buffer;
        file.close();
    }
}

int primaryindex::searchindex(string key){
    int low=0,high=count,mid=0,flag=0;
    while(low<=high){
        mid=(low+high)/2;
        if(usnlist[mid]==key){
            flag=1;
            break;
        }
        else if(usnlist[mid]<key)
            low=mid+1;
        else if(usnlist[mid]>key)
            high=mid-1;
    }
    if(flag)
        return mid;
    else
        return -1;
}

void primaryindex::remove(string key){
    fstream fp;
    char delch='*';
    int pos=0,i,address;
    string buffer,usn,name,sem;
    fstream file;
    pos=searchindex(key);
    if(pos>=0){
        file.open("5.txt");
        address=addlist[pos];
        file.seekp(address,ios::beg);
        file.put(delch);
        file.close();
        cout<<"Record has been deleted\n";
        for(i=pos;i<count;i++){
            usnlist[i]=usnlist[i+1];
            addlist[i]=addlist[i+1];
        }
        count--;
    }
    else
        cout<<":record not found\n";
    cout<<"\nupdated file is\n";
    system(" 5.txt");
}
