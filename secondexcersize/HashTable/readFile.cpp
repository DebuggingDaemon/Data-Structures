#include <iostream>
#include <fstream>
#include <tuple>
#include <vector>
#include "Regio2.cpp"
using namespace std;

typedef tuple<int, string, string, int> Record;

vector<Region> readData(const char* fname){
    vector<Record> records;
    ifstream fin(fname);
    string trash;
    char trashing;
    int period;
    getline(fin, trash);
    if(fin.is_open()){
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
        vector<Region> regions;
        string birth("Births");
        for(auto& x: records){
            if(get<1>(x)==birth){
                Region to_push(get<0>(x), get<2>(x), get<3>(x));
                regions.push_back(to_push);
            }

        }
        return regions;
	}
	else{
		cout<<"Error oppening the file"<<endl;
		exit(EXIT_FAILURE);
	}
}
