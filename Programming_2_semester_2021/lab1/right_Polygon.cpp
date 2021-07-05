#pragma once

class right_Polygon : public Polygon {
public:
    right_Polygon () {}
    right_Polygon (std::vector <Point> points) : Polygon(points) {}; 
    ~right_Polygon () {}
};
