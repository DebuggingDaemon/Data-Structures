#include <vector>
#include <iostream>
#include <string>
using namespace std;

class Region{
public:
    int period;
    string name;
    int births;
    Region(int period, string name, int births){
        this->period=period;
        this->name=name;
        this->births=births;
    }
    Region(){
		this->period=0;
        this->name="";
        this->births=0;
	}
    bool operator < (const Region& cmp) const{
        return (this->name.compare(cmp.name)<0);
    }
    bool operator > (const Region& cmp) const{
        return (this->name.compare(cmp.name)>0);
    }
    bool operator == (const Region& cmp) const{
        return (this->name.compare(cmp.name)==0);
    }
    
};

ostream& operator<<(ostream& os,const Region& reg)
{
    os << reg.period<<"\t"<<reg.name<<"\t Births: "<<reg.births<<endl;
    return os;
}



template<typename T>

class myContainer: public vector<T>{
public:
    bool operator < (const myContainer<T>& cmp) const{
        return((*this)[0]<cmp[0]);
    }
    bool operator > (const myContainer<T>& cmp) const{
        return((*this)[0]>cmp[0]);
    }
    bool operator == (const myContainer<T>& cmp) const{
        return((*this)[0]==cmp[0]);
    }
};

template<typename T>

ostream& operator<<(ostream& os,const myContainer<T>& cont){
    os<<"contains:"<<endl;
    for(auto& x : cont){
        os<<x;
    }
    return os;
}

