#include<iostream>
#include <utility>
#include <vector>
#include <string>
#include <chrono>
#include "quicksort.cpp"
#include "readFile.cpp"
using namespace std;
using namespace std::chrono;

pair<size_t, size_t> BISgenerate(vector<District>& A, District& ke1, District& ke2);
pair<size_t, size_t> IBSgenerate(vector<District>& A, District& ke1, District& ke2);

int main(){
	pair<vector<District>, vector<Record>> ptr=readData("bd-dec22-births-deaths-by-region.txt");
	q_sort<District>(ptr.first, MIN);
	int a, b;
	cout<<"Insert range to search for"<<endl;
	cout<<"lower: ";
	cin>>a;
	cout<<"upper: ";
	cin>>b;
	string str;
	if(a<b){
		District dstr(str, a, 0);
		District dstr2(str, b, 0);
		cout<<"BIS\n";
		auto start1 = high_resolution_clock::now();
		pair<size_t, size_t> pr1=BISgenerate(ptr.first,dstr,dstr2);
		auto stop1 = high_resolution_clock::now();
        auto duration1 = duration_cast<microseconds>(stop1 - start1);
        cout<<duration1.count()<<" microseconds"<<endl;
        for(size_t j=pr1.first; j<=pr1.second; ++j){
			cout<<ptr.first[j].name<<"\t Births: "<<ptr.first[j].births<<endl;
		}
		cout<<"IBS\n";
		auto start2 = high_resolution_clock::now();
		pair<size_t, size_t> pr2=IBSgenerate(ptr.first,dstr,dstr2);
		auto stop2 = high_resolution_clock::now();
        auto duration2 = duration_cast<microseconds>(stop2 - start2);
        cout<<duration2.count()<<" microseconds"<<endl;
        for(size_t j=pr2.first; j<=pr2.second; ++j){
			cout<<ptr.first[j].name<<"\t Births: "<<ptr.first[j].births<<endl;
		}
	}
	
}

pair<size_t, size_t> BISgenerate(vector<District>& A, District& ke1, District& ke2){
	int x=BIS(ke1,A, 0, A.size()-1);
	int low=(A[x]<ke1)? x+1:x;
	size_t j=low;
	while(j<A.size() && A[j].births<ke2.births){
			j++;
	}
	size_t x2=(A[j].births==ke2.births)? j : j-1;
	return 	make_pair(low, x2);
}

pair<size_t, size_t> IBSgenerate(vector<District>& A, District& ke1, District& ke2){
	int x=interpolated_binSearch(A, 0, A.size()-1, ke1);
	size_t low=(A[x]<ke1)? x+1:x;
	low=(A[x-1].births>=ke1.births)? x-1:low;
	size_t j=low;
	while(j<A.size() && A[j].births<ke2.births){
			j++;
	}
	size_t x2=(A[j].births==ke2.births)? j : j-1;
	return make_pair(low, x2);
}


	

