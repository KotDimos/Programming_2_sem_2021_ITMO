#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <map>
#include <cstdlib>
#include "./pugixml/src/pugixml.cpp"


class Transport {
private:
    std::map <std::string, int> routes; 
    std::string routes_transport;

public:

    Transport (std::string trans) : routes_transport(trans) {}
    void print_all_routes () {
        std::string name;
        std::map <std::string, int>::iterator iter;
        for (iter = routes.begin(); iter != routes.end(); ++iter) {
            std::cout << "name_routes = " << "'" << iter->first << "'" << "\tcount_routes = "<< iter->second << std::endl;
	    }
    }

    void print_max_routes() {
        int max = -1;
        std::string name;
        std::map <std::string, int>::iterator iter;
        for (iter = routes.begin(); iter != routes.end(); ++iter) {
	    	if (iter->second > max) {
                max = iter->second;
                name = iter->first;
            } 
	    }
        std::cout << "name_routes = " << "'" <<  name << "'" << "\tmax_routes = "<< max << std::endl;
    }
    
    void maps_routes() {
        pugi::xml_document doc;
        if (!doc.load_file("data.xml")) 
            exit(1);
 
        //pugi::xml_node panels = doc.child("dataset");    
        pugi::xml_node panels = doc.first_child();
        for (pugi::xml_node panel1 = panels.first_child(); panel1; panel1 = panel1.next_sibling()) {
            std::string transport;  
            for (pugi::xml_node panel2 = panel1.first_child(); panel2; panel2 = panel2.next_sibling()) {
                std::string name = panel2.name();
                std::string value = panel2.child_value();
                if (name == "type_of_vehicle") {
                    transport = value;    
                }
                if ((transport == routes_transport) && (name == "routes")) {
                    int size = value.length();
                    std::string value_temp;
                    for (int i = 0; i < size; ++i) {
                        char ch;
                        ch = value[i];
                        if ((ch == '.') || (ch == ',')) {
                            routes[value_temp]++;
                            value_temp = "";
                        }
                        else {
                            value_temp += ch;
                        }
                    }
                    if ((value_temp != "") && (value_temp != " ")){
                        routes[value_temp]++;
                    }
                }
            }
        }
    }
};

//<number>1</number>
//<type_of_vehicle>Автобус</type_of_vehicle>
//<object_type>Остановка</object_type>
//<name_stopping>КОНДРАТЬЕВСКИЙ ПР., 62</name_stopping>
//<the_official_name>КОНДРАТЬЕВСКИЙ ПР., 62</the_official_name>
//<location>Кондратьевский пр., Маршала Блюхера пр.</location>
//<routes>105.137</routes>
//<coordinates>59.978951,30.394102</coordinates>


int main () {
    std::string bus = "Автобус";
    std::string trolley = "Троллейбус";
    std::string tram = "Трамвай";
    Transport a1(bus);

    a1.maps_routes();
    //a1.print_max_routes();
    a1.print_all_routes();
    return 0;
}
