#include <iostream>
#include <vector>
#include <memory>
#include <mariadb/conncpp.hpp>
#include "readFile.cpp"

using namespace std;

int main(){
    vector<District> data = readData("bd-dec22-births-deaths-by-region.txt").first;
    try{
        sql::Driver* driver=sql::mariadb::get_driver_instance();
        sql::SQLString url("jdbc:mariadb://localhost:3306/district_data");
        sql::Properties properties({{"user", "appuser"}, {"password", "passwd"}});
        unique_ptr<sql::Connection> conn(driver->connect(url, properties));
        unique_ptr<sql::PreparedStatement> pstmt(conn->prepareStatement("INSERT INTO districts (district_name, births, deaths) VALUES (?, ?, ?)"));

        for(const auto& item: data){
            pstmt->setString(1, item.name);
            pstmt->setInt(2, item.births);
            pstmt->setInt(3, item.deaths);
            pstmt->executeUpdate();
        }

        cout<<"Data inserted succesfully"<<endl;
    }
    catch(sql::SQLException& e){
        cerr<<"SQLException: "<<e.what()<<endl;
        cerr<<"Error Code: "<<e.getErrorCode()<<endl;
        cerr<<"SQLState: "<<e.getSQLState()<<endl;
    }
    return 0;
}
