#include <iostream>
#include <vector>
#include <string>
#include <cstdio>
#include "AvLtree.cpp"
#include "readFile.cpp"

template<typename T>

void insert(AVLTree<myContainer<T>>& tree, T& item);
myContainer<Region> max(AVLTree<myContainer<Region>>& tree);
myContainer<Region> min(AVLTree<myContainer<Region>>& tree);

int main(){
	vector<Region> regs=readData("bd-dec22-births-deaths-by-region.txt");
	AVLTree<myContainer<Region>> tree;
    for(auto& x: regs){
		insert(tree, x);
	}
	bool ch;
	cout<<"0-If you want regions with minimum births"<<endl;
	cout<<"1-If you want regions with maxumum births"<<endl;
	cin>>ch;
	if(!ch)
		cout<<min(tree);
	else
		cout<<max(tree);
}

myContainer<Region> max(AVLTree<myContainer<Region>>& tree){
	auto rec=tree.maximum();
	return rec;
}

myContainer<Region> min(AVLTree<myContainer<Region>>& tree){
	auto rec=tree.minimum();
	return rec;
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
