#include <fstream>
#include <iostream>
#include <vector>
#include <utility>
#include <tuple>
#include <string>
#include <cmath>
#include <algorithm>
#include "District.cpp"
#define EARLIEST 2005
#define LATEST 2022
#define NUMOFREGIONS 18
using namespace std;

typedef tuple<int, string, string, int> Record;


pair<vector<District>, vector<Record>> readData(const char* fname){
        vector<Record> records;
        vector<District> districts;
        string birth("Births");
        string death("Deaths");
        ifstream fin(fname);
        string trash;
        char trashing;
        int period;
        getline(fin, trash);
        if(fin.good()){
            while(fin>>period){
                string birth_death, region;
                fin>>trashing;
                getline(fin, birth_death, ',');
                getline(fin, region, ',');
                int count;
                fin>>count;
                Record rec(period, birth_death, region, count);
                records.push_back(rec);
                getline(fin, trash);
            }
            fin.close();
            for(int i=0; i<NUMOFREGIONS; i++){
                District dr(get<2>(records[i]), 0, 0);
                districts.push_back(dr);
            }
            for(size_t i=0; i<records.size(); i+=NUMOFREGIONS){
                for(int j=0; j<NUMOFREGIONS; ++j){
                    if(get<1>(records[i+j])==birth)
                        districts[j].births+=get<3>(records[i+j]);
                    else
                        districts[j].deaths+=get<3>(records[i+j]);
                }
            }
            pair<vector<District>, vector<Record>> pr(districts, records);
            return pr;
        }
        else{
            cout<<"Error oppenning the file"<<endl;
            fin.close();
            exit(EXIT_FAILURE);
        }
}


int find_max(vector <District> &arr){
	int max=arr[0].deaths;
	for(size_t i=1;i<arr.size();i++){
		if(arr[i].deaths>max){
			max=arr[i].deaths;
			}
		}
		return max;
}


vector<District> Counting(vector <District> &arr){
	size_t k=find_max(arr);
	string str("empty");
	District drc(str, 0, 0);
	vector<int> counts(k+1,0);
	vector<District> sorted(arr.size(),drc);
	
	for(size_t i=0;i<arr.size();i++){
		counts[arr[i].deaths]++;
	}
	
	for(size_t i=1;i<=k;i++){
		counts[i]+=counts[i-1];
	}
	for(int i=arr.size()-1; i>=0; i--){
		sorted[counts[arr[i].deaths]-1]=arr[i];
		counts[arr[i].deaths]--;
	}
	return sorted;
}
 
 vector<District> space(int down,int up,vector<District> &A){
	vector<District> sp;
	for(int i=down;i<=up;i++){
		sp.push_back(A[i]);
	}
	return sp;
}



int interpolation(District b1, vector<District> &A, int low, int high){
	int next=0;
	int j=0;
	while(!(A[high].births<b1.births)&&(b1.births>A[low].births)){
		next=low +((b1.births-A[low].births)/(A[high].births-A[low].births))*(high-low);
		if (b1.births>A[next].births)
			{low=next+1; j++;}
		else if(b1.births<A[next].births)
			{high=next-1; j++;}
		else {low=next; j++;}
	}
	return low; //low is thessi
	
}

int BIS(District b1,vector<District> &arr, size_t low, size_t high){
    size_t prev =((b1.births-arr[low].births)/(arr[high].births-arr[low].births))*(high-low);
    size_t step = prev+sqrt(high-low+1);
    while (arr[min(step, arr.size())-1].births < b1.births){
        prev = step;
        step += sqrt(high-low+1);
        if (prev >= arr.size())
            return arr.size()-1;
    }
    if(arr[prev].births<b1.births)
		return interpolation(b1, arr, prev, min(step, high-low));
	return prev;
}

int interpolated_binSearch(vector<District>& vect, int low, int high, District key){
    if(low<high){
        int pos=low +((key.births-vect[low].births)/(vect[high].births-vect[low].births))*(high-low);
        if(pos<low)
            return low;
        if(pos>high)
            return high;
        if(key.births>vect[pos].births){
            int imid=(pos+high)/2;
            if(key.births<=vect[imid].births){
                return interpolated_binSearch(vect, pos+1, imid, key);
            }
            else
                return interpolated_binSearch(vect, imid+1, high, key);
        }
        else if(key.births<vect[pos].births){
            int imid=(pos+low)/2;
            if(key.births>=vect[imid].births){
                return interpolated_binSearch(vect, imid, pos-1, key);
            }
            else
                return interpolated_binSearch(vect, low, imid-1, key);
        }
        else
            return pos;
    }
    return low;
}
