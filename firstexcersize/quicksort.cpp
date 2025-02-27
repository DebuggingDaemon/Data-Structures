#include <vector>
#include <cstdlib>
#define MIN 0
#define MAX 1
using namespace std;

template<typename T>

bool compare_func(T a, T b, bool type){
    bool ret=a<b;
    return (type==MIN)? ret : !ret;
}




size_t random_number(size_t lower, size_t upper){
	return (lower+rand()%(upper-lower+1));
}

template<typename T>

int partition(vector<T>& arr, int low, int high, bool type){
	int index=random_number(low, high);
	swap(arr[index], arr[high]);
    T pivot=arr[high];
    int i=(low-1);
    for(int j=low; j<=high; j++){
        if(compare_func<T>(arr[j], pivot, type)){
			i++;
			swap(arr[i],arr[j]);
		}
	}
    swap(arr[i+1],arr[high]);
    return (i+1);
}

 template<typename T>
           
void quickSort(vector<T>& arr, int low, int high, bool type)
{
  if(low<high){
    int pi=partition<T>(arr, low, high, type);
    quickSort(arr, low, pi-1, type);
    quickSort(arr, pi+1, high, type);
  }
}

template<typename T>

void q_sort(vector<T>& arr, bool type){
    quickSort(arr, 0, arr.size()-1, type);
}
