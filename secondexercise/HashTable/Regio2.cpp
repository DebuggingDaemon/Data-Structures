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
        if(this->period==(cmp.period))
			return(this->name.compare(cmp.name)<0);
		else
			return(this->period<(cmp.period));
    }
    bool operator > (const Region& cmp) const{
        if(this->period==(cmp.period))
			return(this->name.compare(cmp.name)>0);
		else
			return(this->period>(cmp.period));
			
    }
    bool operator == (const Region& cmp) const{
        if(this->period==(cmp.period))
			return(this->name.compare(cmp.name)==0);
		else
			return(this->period==(cmp.period));
        
    }
    
};

ostream& operator<<(ostream& os,const Region& reg)
{
    os << reg.period<<"\t"<<reg.name<<"\t Births: "<<reg.births<<endl;
    return os;
}


