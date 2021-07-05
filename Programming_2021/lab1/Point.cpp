#pragma once

class Point {
private:
    double x_point;
    double y_point;

public:
    Point (): x_point(0.0), y_point(0.0)
    {}
    Point (double x, double y): x_point(x), y_point(y)
    {}
    Point (int x, int y): x_point(x), y_point(y)
    {}
    Point(const Point &t){
        x_point = t.getX(); 
        y_point = t.getY();
    }
    void setX (double x) {
        x_point = x;
    }
    void setY (double y) {
        y_point = y;
    }
    void setXY(double x, double y) {
        x_point = x;
        y_point = y;
    }
    double getX () const {
        return x_point;
    }
    double getY () const {
        return y_point;
    }
    
    void print_point () const {
        std::cout << x_point << " - " << y_point << std::endl;
    }
    
    void operator= (const Point &t) {
        x_point = t.getX(); 
        y_point = t.getY();
    };

    ~Point () {}
};


