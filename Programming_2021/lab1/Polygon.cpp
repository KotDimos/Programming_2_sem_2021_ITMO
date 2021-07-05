#pragma once

class Polygon {
protected:
    std::vector <Point> points;

public:
    Polygon () {}
    Polygon (std::vector <Point> &m): points(m) {}
    
    void print_points () {
        std::cout << "print_points" << std::endl;
        int size = points.size();
        for (int i = 0; i < size; ++i) {
            std::cout << points[i].getX() << " - " << points[i].getY() << std::endl;
        }
    }
    
    
    void Perimeter () {
        int size = points.size();          
        double line;
        double P = 0;
        for (int i = 0; i < size - 1; ++i) {
            line = sqrt(pow(points[i + 1].getX() - points[i].getX(), 2) + pow(points[i + 1].getY() - points[i].getY(), 2)); 
            P += line;
        }
        P += sqrt(pow(points[size - 1].getX() - points[0].getX(), 2) + pow(points[size - 1].getY() - points[0].getY(), 2));

        std::cout << "Периметр - " << P << std::endl;
    }
    
    void Area () {
        int size = points.size();          
        double S = 0;
        double x, y;
        
        for (int i = 0; i < size - 1; ++i) {
            x = points[i].getX();
            y = points[i + 1].getY();
            S += x * y;
        }
        x = points[size - 1].getX();
        y = points[0].getY();
        S +=  x * y;

        for (int i = 0; i < size - 1; ++i) {
            x = points[i + 1].getX();
            y = points[i].getY();
            S -= x * y;
        }
        x = points[0].getX();
        y = points[size - 1].getY();
        S -=  x * y;
        
        S = abs(S);
        S = S / 2;

        std::cout << "Площадь - " << S << std::endl;
    }

    ~Polygon () {}
};
