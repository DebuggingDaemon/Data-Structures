#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <chrono>
#include <climits>
#include "binary_search.cpp"
#include "readFile.cpp"
using namespace std;
using namespace std::chrono;

pair<size_t, size_t> searchRange(vector<District>& arr, District& ke1, District& ke2);
pair<size_t, size_t> searchRange2(vector<District>& A, District& ke1, District& ke2);

int main(){
	pair<vector<District>, vector<Record>> prt=readData("bd-dec22-births-deaths-by-region.txt");
	q_sort<District>(prt.first, MIN);
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
		auto start1 = high_resolution_clock::now();
		pair<size_t, size_t> pr=searchRange(prt.first, dstr, dstr2);
		auto stop1 = high_resolution_clock::now();
        auto duration1 = duration_cast<microseconds>(stop1 - start1);
		if(pr.second<prt.first.size()){
			cout<<duration1.count()<<" microseconds"<<endl;
			for(size_t x=pr.first; x<=pr.second; ++x){
				cout<<prt.first[x].name<<"\t Births: "<<prt.first[x].births<<endl;
			}
		}
		cout<<"\ninterpolation\n";
		auto start2 = high_resolution_clock::now();
		pair<size_t, size_t> prc=searchRange2(prt.first,dstr,dstr2);	
		auto stop2 = high_resolution_clock::now();
		auto duration2 = duration_cast<microseconds>(stop2 - start2);
		if(prc.second<prt.first.size()){
			cout<<duration2.count()<<" microseconds"<<endl;
			for(size_t x=pr.first; x<=pr.second; ++x){
				cout<<prt.first[x].name<<"\t Births: "<<prt.first[x].births<<endl;
			}
		}
		
	}	
}
 
 
 pair<size_t, size_t> searchRange(vector<District>& arr, District& ke1, District& ke2){
	 size_t x=binSearch<District>(arr, ke1, MIN);
	 size_t x1=(arr[x]<ke1)? x+1 : x;
	 size_t j=x1;
	 while(j<arr.size() && arr[j]<ke2){
		 j++;
	 }
	 size_t x2=(arr[j]==ke2)? j : j-1;
	 return make_pair(x1, x2);
 }
 
pair<size_t, size_t> searchRange2(vector<District>& A, District& ke1, District& ke2){
	string str;
	int low=interpolation (ke1,A, 0, A.size()-1);
	size_t j=low;
	while(j<A.size() && A[j].births<ke2.births){
			j++;
		}
		size_t x2=(A[j].births==ke2.births)? j : j-1;
		return make_pair(low, x2);
}
