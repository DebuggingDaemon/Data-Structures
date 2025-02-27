#include<string>
using namespace std;
class District{
public:
    string name;
    int births;
    int deaths;

    District(string name, int births, int deaths){
        this->name=name;
        this->births=births;
        this->deaths=deaths;
    }
    bool operator < (const District& cmp) const{
        return ((this->births)<(cmp.births));
    }
    bool operator > (const District& cmp) const{
        return (this->deaths)>cmp.deaths;
    }
    bool operator == (const District& cmp) const{
		return this->births==cmp.births;
	}
};

