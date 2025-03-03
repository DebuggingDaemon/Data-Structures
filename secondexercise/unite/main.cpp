#include <iostream>
using namespace std;


int main(){
	bool ch;
	cout<<"0-Read the file using a tree"<<endl;
	cout<<"1-Read the file using a hash-table"<<endl;
	cin>>ch;
	if(!ch){
		bool choice;
		cout<<"0-find minimum and maximum birth region"<<endl;
	    cout<<"1-Open the application for searching and update"<<endl;
	    cin>>choice;
	    if(!choice){
			system("./test2");
		}
		else
			system("./test");
	}
	else
		system("./hash");
	
} 
