#include <vector>
#define MAX 0
#define MIN 1
using namespace std;

template<typename T>

bool compare(T a, T b, bool type){
    bool ret = a>b;
    return ((type==MAX)? ret : (!ret));
}


template<typename T>

void heapify_up(vector<T>& vect, size_t i, bool type){
	if(i!=0){
		int parent = (i%2==0)? (i/2-1) : (i/2);
		if(!compare<T>(vect[parent], vect[i], type)){
			swap(vect[parent], vect[i]);
			heapify_up(vect, parent, type);
		}
	}
		
}

template<typename T>

void heapify_down(vector<T>& vect, size_t i, bool type){
	size_t leftChild=2*i+1;
	size_t rightChild=2*i+2;
	if(leftChild<vect.size()){
		int next;
		if(rightChild<vect.size())
			next=(compare<T>(vect[leftChild], vect[rightChild], type))? leftChild : rightChild;
		else
			next=leftChild;
		if(!compare(vect[i], vect[next], type)){
			swap(vect[i], vect[next]);
			heapify_down(vect, next, type);
		}
	}
}


template<typename T>

void create_heap(vector<T>& vect, bool type){
	for(size_t j=1; j<vect.size(); ++j){
		heapify_up<T>(vect, j, type);
	}
}

template<typename T>

void push_heap(vector<T>& vect, T item, bool type){
	vect.push_back(item);
	int place=vect.size()-1;
	heapify_up<T>(vect, place, type);
}

template<typename T>

 T pop_heap(vector<T>& vect, bool type){
	T ret=vect[0];
	swap(vect[0], vect[vect.size()-1]);
	vect.pop_back();
	heapify_down<T>(vect, 0, type);
	return ret;
}

template<typename T>

void heap_sort(vector<T>& vect, bool type){
	vector<T> ret;
	create_heap(vect, type);
	while(!vect.empty())
		ret.push_back(pop_heap(vect, type));
	vect=ret;
}





