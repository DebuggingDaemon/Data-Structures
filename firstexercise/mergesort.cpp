#include<vector>
using namespace std;

template<typename T>

vector<T> merge_sorted(vector<T>& v1, vector<T>& v2){
    size_t  ptr1=0, ptr2=0;
    vector<T> merged;
    while(ptr1<v1.size() && ptr2<v2.size()){
        if(v1[ptr1]<v2[ptr2]){
            merged.push_back(v1[ptr1]);
            ptr1++;
        }
        else {
            merged.push_back(v2[ptr2]);
            ptr2++;
        }
    }
    while(ptr1<v1.size()){
        merged.push_back(v1[ptr1]);
        ptr1++;
    }
    while(ptr2<v2.size()){
        merged.push_back(v2[ptr2]);
        ptr2++;
    }
    return merged;
}

template<typename T>

vector<T> mergeSort(vector<T>& arr, int low, int high){
    if(low<high){
        int center=(low+high)/2;
        vector<T> vect1=mergeSort(arr, low, center);
        vector<T> vect2=mergeSort(arr, center+1, high);
        return merge_sorted(vect1, vect2);
    }
    else{
        vector<T> vect;
        vect.push_back(arr[low]);
        return vect;
    }
}
