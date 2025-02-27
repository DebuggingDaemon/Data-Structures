#include <iostream>
#include <fstream>
#include <utility>
#include <vector>
#include <string>
#include <chrono>
#include "mergesort.cpp"
#include "quicksort.cpp"
#include "readFile.cpp"
using namespace std;
using namespace std::chrono;

void sort_by_birth_count1(vector<District>& vect);
void sort_by_birth_count2(vector<District>& vect);

auto choose_sorting(vector<District>& vect){
    int choice;
    cout<<"Choose Algorithm to sort by birth count"<<endl;
    cout<<"1) Quicksort"<<endl;
    cout<<"2) Mergesort\n";
    cin>>choice;
    if(choice==1){
		auto start = high_resolution_clock::now();
        sort_by_birth_count1(vect);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        return duration;
	}
    else{
		auto start = high_resolution_clock::now();
        sort_by_birth_count2(vect);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        return duration;
	}
}


int main(){
    pair<vector<District>, vector<Record>> vectors=readData("bd-dec22-births-deaths-by-region.txt");
    cout<<choose_sorting(vectors.first).count()<<"\t microseconds"<<endl;
    for(District& x: vectors.first)
        cout<<x.name<<"\n"<<x.births<<"\t"<<x.deaths<<endl;

}



void sort_by_birth_count1(vector<District>& vect){
    q_sort<District>(vect, MIN);
}

void sort_by_birth_count2(vector<District>& vect){
    vector<District> ve=mergeSort<District>(vect, 0, vect.size()-1);
    vect=ve;
}







