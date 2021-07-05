#include <iostream>
#include <cmath>
#include <vector>
#include <cstdlib>
 
#include "Point.cpp"
#include "open_Broken.cpp"
#include "closed_Broken.cpp"
#include "Polygon.cpp"
#include "Triangle.cpp"
#include "Trapezoid.cpp"
#include "right_Polygon.cpp"



int main () {

    

    std::vector <Point> trian = {
                                {1, 1},
                                {5, 4},
                                {9, 1}
    };
    std::vector <Point> trapez = {
                                 {1, 1},
                                 {4, 5},
                                 {10, 5},
                                 {13, 1}
    };



    Polygon *t[2];
    t[0] = new Triangle(trian);
    t[1] = new Trapezoid(trapez);

    t[0]->print_points(); 
    t[1]->print_points(); 
    
    return 0;
}











