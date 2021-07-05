#pragma once

class Trapezoid : public Polygon {
public:
    Trapezoid () {}
    Trapezoid (std::vector <Point> points) : Polygon (points) {}
    ~Trapezoid () {}
};


