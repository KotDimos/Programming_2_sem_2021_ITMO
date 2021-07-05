#include <iostream>
#include <ostream>
#include <vector>


class ElementPolynom {
private:
    double factor;
    int power;
public:
    ElementPolynom () {}
    ElementPolynom (double factr, int pow) : factor(factr), power(pow) {}
    
    double getFactor () const {
        return factor;
    }
    int getPower () const {
        return power;
    }
    void setFactor (double factr) {
        factor = factr;
    }
    void setPower (int pow) {
        power = pow;
    }

    void operator= (ElementPolynom elPol) {
        factor = elPol.getFactor();
        power = elPol.getPower();
    } 

    ~ElementPolynom () {}
};


class Polynom {
private:
    std::vector <ElementPolynom> arr;
    
public:
    Polynom () {}
    Polynom (std::vector <ElementPolynom> &a) : arr(a) {}

    void SumFactor (std::vector <ElementPolynom> &a) {
        if (a.size() > 0) {
            for (unsigned i = 0; i < a.size(); i++) {
                for (unsigned j = (i + 1); j < a.size(); j++) {
                    if (a[i].getPower() == a[j].getPower()) {
                        a[i].setFactor(a[i].getFactor() + a[j].getFactor());
                        a.erase(a.begin() + j);
                        --j;
                    }
                }
            }
        }
    }
    void print () {
        int size = arr.size();
        for (int i = 0; i < size; ++i) {
            std::cout <<  arr[i].getFactor() << "^" << arr[i].getPower() << std::endl;
        }
    }


    Polynom operator= (const Polynom &p) {
        arr.resize(p.arr.size());
        for (unsigned i = 0; i < p.arr.size(); ++i) {
            arr[i] = p.arr[i];
        }
        SumFactor(arr);
        return *this;
    } 

    bool operator== (const Polynom &p) {
        int size_p = p.arr.size();
        int size = arr.size();
        if (size_p != size) {
            return false; 
        }
        for (int i = 0; i < size; ++i) {
            if ((arr[i].getFactor() != p.arr[i].getFactor()) || (arr[i].getPower() != p.arr[i].getPower())) {
                return false;
            }
        }
        return true;
    } 
    bool operator!= (const Polynom &p) {
        int size_p = p.arr.size();
        int size = arr.size();
        if (size_p != size) {
            return true; 
        }
        for (int i = 0; i < size; ++i) {
            if ((arr[i].getFactor() != p.arr[i].getFactor()) || (arr[i].getPower() != p.arr[i].getPower())) {
                return true;
            }
        }
        return false;
    } 

    Polynom operator+ (Polynom &p1) {
        std::vector <ElementPolynom> sum;
        int size = arr.size();
        for (int i = 0; i < size; ++i) {
            sum.push_back(arr[i]);
        }
        size = p1.arr.size();
        for (int i = 0; i < size; ++i) {
            sum.push_back(p1.arr[i]);
        }
        SumFactor(sum);
        return Polynom(sum);
    }
    
    void operator+= (Polynom &p1) {
        int size = p1.arr.size();
        for (int i = 0; i < size; ++i) {
            arr.push_back(p1.arr[i]);
        }
        SumFactor(arr);
    }

    
    Polynom operator- (Polynom &p1) {
        std::vector<ElementPolynom> sum;
        std::vector<ElementPolynom> invert = p1.arr;
        double factor;
        for (unsigned i = 0; i < p1.arr.size(); ++i) {
            factor = (-1) * invert[i].getFactor();
            invert[i].setFactor(factor);
        }
        int size = arr.size();
        for (int i = 0; i < size; ++i) {
            sum.push_back(arr[i]);
        }
        size = p1.arr.size();
        for (int i = 0; i < size; ++i) {
            sum.push_back(invert[i]);
        }
        SumFactor(sum);
        return Polynom(sum);
    }
    
    Polynom operator- () {
        std::vector<ElementPolynom> sum;
        double factr;
        
        for (unsigned i = 0; i < arr.size(); ++i) {
            factr = (-1) * arr[i].getFactor();
            sum.push_back(ElementPolynom(factr, arr[i].getPower()));
        }
        return Polynom (sum);
    }

    void operator-= (Polynom &p1) {
        std::vector<ElementPolynom> invert = p1.arr;
        double factor;
        for (unsigned i = 0; i < p1.arr.size(); ++i) {
            factor = (-1) * invert[i].getFactor();
            invert[i].setFactor(factor);
        }
        int size = p1.arr.size();
        for (int i = 0; i < size; ++i) {
            arr.push_back(invert[i]);
        }
        SumFactor(arr);
    }

    Polynom operator* (Polynom &p1) {
        std::vector <ElementPolynom> sum;
        for (unsigned i = 0; i < arr.size(); ++i) {
            for (unsigned j = 0; j < p1.arr.size(); ++j) {
                sum.push_back(ElementPolynom (p1.arr[i].getFactor() * arr[i].getFactor(), 
                                              p1.arr[i].getPower() + arr[i].getPower()));   
            }
        }
        SumFactor(sum);
        return Polynom(sum);
    }

    Polynom operator*= (Polynom &p1) {
        *this = *this * p1;
        return Polynom(p1);
    }
    
    Polynom operator/ (Polynom &p1) {
        std::vector <ElementPolynom> sum;
        int k = 0;
        int maxP = 0;
        for (unsigned i = 0; i < p1.arr.size(); ++i) {
            if (p1.arr[i].getPower() == 0) {
                k = -1 * p1.arr[i].getFactor();
            } 
            if (p1.arr[i].getPower() > maxP) {
                maxP = arr[i].getPower();
            }
        }
        if (k != 0) {
            sum.push_back(ElementPolynom (arr[0].getFactor(), arr[0].getPower() - 1));
            int c = arr[0].getFactor();
            for (unsigned i = 1; i < arr.size(); ++i) {
                c = c * k + arr[i].getFactor();
                sum.push_back(ElementPolynom(c, arr[i].getPower() - 1));
            }
            sum[arr.size() - 1].setPower(-1 * p1.arr[0].getPower());
            sum.push_back(ElementPolynom(sum[arr.size() -1].getFactor() / p1.arr[p1.arr.size() - 1].getFactor(), 0));
        }
        else if (k == 0) {
            if (p1.arr[0].getPower() != 0) {
                for (unsigned i = 0; i < arr.size(); ++i) {
                    arr[i].setFactor(arr[i].getFactor() / p1.arr[i].getFactor());
                    arr[i].setPower(arr[i].getPower() - p1.arr[i].getPower());
                }
            }
            else {
                arr.resize(0);
            }
        }
        SumFactor(arr);
        return Polynom (arr);

    }
    Polynom operator/= (Polynom &p1) {
        *this = *this / p1;
        return Polynom(p1);
    }
    
    friend void operator<< (std::ostream &out, Polynom &p1) {
        for (unsigned i = 0; i < p1.arr.size(); ++i) {
            std::cout << p1.arr[i].getFactor() << "^" << p1.arr[i].getPower() << std::endl;
        }
    }
    friend Polynom operator>> (std::istream &in, Polynom &p1) {
        double factr;
        int pow;
        std::cin >> factr >> pow;
        std::vector <ElementPolynom> sum;
        for (unsigned i = 0; i < p1.arr.size(); ++i) {
            sum.push_back(p1.arr[i]);
        }
        sum.push_back(ElementPolynom(factr, pow));
        p1 = sum;
        return Polynom(p1);
    }

    ElementPolynom operator[] (int i) {
        return arr[i];
    }
    ~Polynom () {}
};



int main () {
    ElementPolynom p11(1, 1), p12(2, 1), p13(3, 1);
    ElementPolynom p21(2, 2), p22(3, 2), p23(4, 2);
    ElementPolynom p31(3, 3), p32(4, 3), p33(5, 3);
    std::vector <ElementPolynom> polynomArr1(3);
    std::vector <ElementPolynom> polynomArr2(3);
    std::vector <ElementPolynom> polynomArr3(3);
    polynomArr1 = {p11, p12, p13};
    polynomArr2 = {p21, p22, p23};
    polynomArr3 = {p31, p32, p33};
    Polynom pol1(polynomArr1);
    Polynom pol2(polynomArr2);
    Polynom pol3(polynomArr3);
    
    //pol1 = pol2;
    //
    //if (pol1 == pol2) {
    //    std::cout << "true" << std::endl;
    //}
    //else {
    //    std::cout << "false" << std::endl;
    //}
    //
    //pol3 = pol1 + pol2;
    //pol3 += pol1;
    //
    //pol3 = pol1 - pol2;
    //pol3 -= pol1;
    //
    //pol3 = pol1 * pol2;
    //pol3 *= pol1;
    //
    //pol3 = pol1 / pol2;
    //pol3 /= pol1;
    //std::cin >> pol1;
    //std::cout << pol1; 
    
    pol3 = -pol1;
    std::cout << pol3;
    return 0;
}

