#include <iostream>
#include<cmath>
#include<string>
#include<vector>
#include "AvLtree.cpp"
#include "readFile.cpp"
#define numofregions 18
using namespace std;


int Hashfunc(string region,int buckets);



int Hashfunc(string region,int buckets){
    int sum=0;
    for(size_t i=0;i<region.length();i++){
        sum+=region[i];
    }
    return(sum%buckets);
}

Region& Search(Region R,AVLTree <Region>*& HashTable){
	int pos=Hashfunc(R.name,numofregions);
	AVLNode<Region>*& nd=HashTable[pos].look_up(R);
	if(nd!=nullptr)
		return nd->key;
	else
		throw "Does not exist";
}

Region& Update(Region R,AVLTree <Region>*& HashTable){
	Region& temp=Search(R,HashTable);
	cout<<"Change count of births:"<<endl;
	int k;
	cin>>k;
	temp.births=k;
	return temp;
}

void Delete(Region R,AVLTree <Region>*& HashTable){
	int pos=Hashfunc(R.name,numofregions);
	HashTable[pos].remove_node(R);
	cout<<"node removed"<<endl;
}

Region scanRegion(){
		cout<<"Enter year"<<endl;
		string trash;
		int per;
		cin>>per;
		cout<<"Enter name of region"<<endl;
		getline(cin, trash);
		string sname;
		getline(cin, sname);
		Region reg(per, sname, 0);
		return reg;
}


int Menu(AVLTree<Region>*& HashTable){
    int k;
    do{
        cout<<"What do you wish to do:?"<<endl;
        cout<<"Press 1 if you want to search a record"<<endl;
        cout<<"Press 2 if you want to update a record"<<endl;
        cout<<"Press 3 if you want to delete a record"<<endl;
        cout<<"Press 4 if you want to exit from the app"<<endl;
        cin>>k;
    }while(k>4&&k<1);
    switch(k){
        case 1:
        {
			try{
				Region reg = scanRegion();
				cout<<"The searching is executing..."<<endl;
				Region &t=Search(reg, HashTable);
				cout<<t<<endl;
			}catch(const char* msg){
				cout<<msg<<endl;
			}     
		}
		break;
        case 2:{
			try{
				Region reg = scanRegion();
				cout<<"The searching is executing..."<<endl;
				Region &t=Update(reg, HashTable);
				cout<<t<<endl;
			}catch(const char* msg){
				cout<<msg<<endl;
			}
		}
        break;
        case 3:
        {
			try{
				Region reg = scanRegion();
				cout<<"The searching is executing..."<<endl;
				Delete(reg, HashTable);
			}catch(const char* msg){
				cout<<msg<<endl;
			}
		}
        break;
    default:
        ;
    }
    return k;
}

int main(){
    vector<Region> buffer=readData("bd-dec22-births-deaths-by-region.txt");
    AVLTree <Region>* HashTable;
    HashTable= new AVLTree<Region>[numofregions];
    int pos1;
    for(size_t i=0;i<buffer.size();i++){
        pos1=Hashfunc(buffer[i].name, numofregions);
        HashTable[pos1].add_node(buffer[i]);
    }
    int x=Menu(HashTable);
    while(x<=3&&x>0){
		x=Menu(HashTable);
	}
    cout<<"Session ended"<<endl;
	
}
