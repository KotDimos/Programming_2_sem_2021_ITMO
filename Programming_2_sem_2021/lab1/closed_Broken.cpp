#pragma once

class closed_Broken : public open_Broken {
public: 
    
    closed_Broken(std::vector <Point> points) : open_Broken(points) {}
    
    void Perimeter () {
        int size = points.size();
        double P = 0;
        
        for (int i = 0; i < size; ++i) {
            P += sqrt(pow(points[i + 1].getX() - points[i].getX(), 2) + pow(points[i + 1].getY() - points[i].getY(), 2));
        }
        std::cout << "Периметр - " << P << std::endl;
    }
};
