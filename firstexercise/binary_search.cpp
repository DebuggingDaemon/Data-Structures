#include <vector>
#include "quicksort.cpp"
using namespace std;

//the array is sorted

template <typename T>

int binary_search(vector<T>& vect, T key, int low, int high, bool type){
	if(low<high){
		int center=(low+high)/2;
		if(key==vect[center])
			return center;
		else if(compare_func(key,vect[center], type))
			return binary_search(vect, key, low, center-1, type);
		else
			return binary_search(vect, key, center+1, high, type);
	}
	else{
		return low;
	}
}

template <typename T>

int binSearch(vector<T>& vect, T key, bool type){
	return binary_search<T>(vect, key, 0, vect.size()-1, type);
}
