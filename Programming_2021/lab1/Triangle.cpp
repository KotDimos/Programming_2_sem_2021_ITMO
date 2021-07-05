#pragma once

class Triangle : public Polygon {
public:
    Triangle () {}
    Triangle (std::vector <Point>& points) : Polygon (points) {}
    int check_Triangle () {
        double line1 = sqrt(pow(points[1].getX() - points[0].getX(), 2) + pow(points[1].getY() - points[0].getY(), 2)); 
        double line2 = sqrt(pow(points[2].getX() - points[1].getX(), 2) + pow(points[2].getY() - points[1].getY(), 2)); 
        double line3 = sqrt(pow(points[0].getX() - points[2].getX(), 2) + pow(points[0].getY() - points[2].getY(), 2)); 
        if (line1 + line2 <= line3) {
            std::cout << "Неверные данные у треугольника" << std::endl;
            return 1;
        }
        else if (line1 + line3 <= line2) {
            std::cout << "Неверные данные у треугольника" << std::endl;
            return 1;
        }
        else if (line2 + line3 <= line1) {
            std::cout << "Неверные данные у треугольника" << std::endl;
            return 1;
        }
        return 0;
    } 
    
    ~Triangle () {}
};
