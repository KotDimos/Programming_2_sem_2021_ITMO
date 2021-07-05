#pragma once

class open_Broken {
protected:
    std::vector <Point> points;
public:
    open_Broken (){}
    
    open_Broken (std::vector <Point> &m) : points(m) {}
    

    void print_point_Broken () {
        std::cout << "print_point_Broken" << std::endl;
        int size = points.size();
        for (int i = 0; i < size; ++i) {
            std::cout << points[i].getX() << " - " << points[i].getY() << std::endl;
        }
    }
    
    void Perimeter () {
        double size = points.size();
        double P;
        for (int i = 0; i < size - 1; ++i) {
            double a = points[i + 1].getX() - points[i].getX();
            double b = points[i + 1].getY() - points[i].getY();
            P = sqrt (pow (a, 2) + pow (b, 2));
       }
       std::cout << "Периметр - " << P << std::endl;
    }

    ~open_Broken () {
        points.clear();
    }
};
