#include <iostream>
#include <vector>
#include <string>
#include <cstdio>
#include "AvLtree.cpp"
#include "readFile.cpp"
using namespace std;



template<typename T>


void insert(AVLTree<myContainer<T>>& tree, T& item);
Region& find(AVLTree<myContainer<Region>>& tree, Region& x);
int menu(AVLTree<myContainer<Region>>& tree);
Region scanRegion();

int main(){
    vector<Region> vect=readData("bd-dec22-births-deaths-by-region.txt");
    AVLTree<myContainer<Region>> tree;
    for(auto& x: vect){
		insert(tree, x);
	}
	int x=menu(tree);
	while(x>0 && x<=4){
		x=menu(tree);
	}
}

template<typename T>

void insert(AVLTree<myContainer<T>>& tree, T& item){
	myContainer<T> cont;
	cont.push_back(item);	
	AVLNode<myContainer<T>>*& test=tree.look_up(cont);
	if(test!=nullptr){
		test->key.push_back(item);
	}
	else{
		tree.add_node(cont);
	}
}

Region& find(AVLTree<myContainer<Region>>& tree, Region& x){
	myContainer<Region> cont;
	cont.push_back(x);
	AVLNode<myContainer<Region>>*& tst=tree.look_up(cont);
	if(tst){
		int low=0, high=tst->key.size()-1;
		while(low<high){
			int center=(low+high)/2;
			if(x.period == tst->key[center].period){
				return tst->key[center];
			}
			else if(x.period > tst->key[center].period){
				low=center+1;
			}
			else
				high=center;
		}
		return tst->key[low];
	}
	else
		throw "Not found";
}

void update(AVLTree<myContainer<Region>>& tree, Region& x){
	Region& reg=find(tree, x);
	cout<<"Enter count of births"<<endl;
	int count;
	cin>>count;
	reg.births=count;
}

int menu(AVLTree<myContainer<Region>>& tree){
	int choice;
	cout<<"0) Exit session"<<endl;
	cout<<"1) Inorder Traversal"<<endl;
	cout<<"2) Search Births based on region and period"<<endl;
	cout<<"3) Update Births based on region and period"<<endl;
	cout<<"4) Delete Region"<<endl;
	cout<<"Enter choice: ";
	cin>>choice;
	switch(choice){
		case 1:
			tree.inorder();
		break;
		case 2:
		{
			try{
				Region reg=scanRegion();
				cout<<find(tree, reg);
			}catch(const char* msg){
				cout<<msg<<endl;
			}
		}
		break;
		case 3:
		{
			try{
				Region reg=scanRegion();
				update(tree, reg);
				cout<<find(tree, reg);
			}catch(const char* msg){
				cout<<msg<<endl;
			}
		}
		break;
		case 4:
		{
			cout<<"Enter name of region"<<endl;
			string trash;
			getline(cin, trash);
			string sname;
			getline(cin, sname);
			Region reg(0, sname, 0);
			myContainer<Region> mc;
			mc.push_back(reg);
			tree.remove_node(mc);
		}
	}
	return choice;
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
 
