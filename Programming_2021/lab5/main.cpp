#include <iostream>
#include <ostream>
#include <iterator>
#include <algorithm>


template <class T>
class Circular_Buffer {
private:
    int capacity;
    T *data;
    int head = 0;
    int tail = 0;

public:
    class Iterator : public std::iterator<std::random_access_iterator_tag, T> {
    private:
        T *p;
    
    public:
        Iterator() : p (nullptr) {}
        Iterator(T *p) : p (p) {}

        Iterator operator++ () {
            p++;
            return *this;
        }

        Iterator operator++ (int) {
            Iterator tmp(*this);
            ++p;
            return tmp;
        }
        
        Iterator &operator-- () {
            p--;
            return *this;
        }

        Iterator operator-- (int) {
            Iterator tmp(*this);
            --p;
            return tmp;
        }

        Iterator operator+ (int x) {
            return Iterator(p + x);
        }

        Iterator &operator+= (int x) {
            p += x;
            return *this;
        }
        
        auto operator- (const Iterator &it) {
            return (p - it.p);
        }
        
        Iterator operator- (int x) {
            return Iterator(p - x);
        }

        Iterator &operator-= (int x) {
            p -= x;
            return *this;
        }
        T &operator* () const {
            return *p;
        }

        T *operator-> () const {
            return p;
        }

        T &operator[] (const int x) {
            return p[x];
        }

        bool operator== (const Iterator &x) const {
            return x.p == this->p;
        }

        bool operator!= (const Iterator &x) const {
            return x.p != this->p;
        }

        bool operator< (const Iterator &x) const {
            return x.p < this->p;
        }

        bool operator> (const Iterator &x) const {
            return x.p > this->p;
        }

        bool operator>= (const Iterator &x) const {
            return x.p >= this->p;
        }

        bool operator<= (const Iterator &x) const {
            return x.p <= this->p;
        }
    };
    
    Circular_Buffer() {};

    Circular_Buffer (int cap) : capacity(cap) {
        head = 0;
        tail = 0;
        data = new T[capacity];
    }


    Iterator begin () const {
        return Iterator(data + head);
    }

    Iterator end () const {
        return Iterator(data + tail);
    }

    T &operator[] (int index) {
        return data[index % capacity];
    }

    void push_front(const T &x) {
        if (tail == capacity) {
            data[head] = x;
            return;
        }
        for (int i = tail; i >= head; i--) {
            data[i + 1] = data[i];
        }
        data[head] = x;
        tail++;
    }

    void pop_front() {
        data[head] = 0;
        for (int i = head; i <= tail; ++i) {
            data[i] = data[i + 1];
        }
        data[tail] = 0;
        --tail;
    }

    void push_back(const T &x) {
        if (tail == capacity) { 
            tail--;
        }
        data[tail] = x;
        if (tail != capacity + 1) {
            tail++;
        }
    }

    void pop_back() {
        data[tail] = 0;
        tail--;
    }

    void resize(const int &n) {
        T *tmp = new T[n];
        for (int i = 0; i < n; i++) {
            tmp[i] = data[i];
        }
        delete[] data;
        data = tmp;
        capacity = n;
    }
 
    friend std::ostream& operator<< (std::ostream &out, Circular_Buffer &buf) {
        for (Iterator iter = buf.begin(); iter != buf.end(); ++iter) {
            out << *iter << " ";
        }
        out << std::endl;
        return out;
    }

    ~Circular_Buffer() {
        delete[] data;
    }
};



int main() {
    Circular_Buffer <int> buffer(5);

    buffer.push_back(1);
    buffer.push_back(2);
    buffer.push_back(3);
    
    std::cout << buffer; 
    
    buffer.pop_front();
    
    buffer.push_back(4);
    
    std::cout << buffer; 
    
    std::sort(buffer.begin(), buffer.end());
    std::cout << buffer;

    auto result = std::max_element (buffer.begin(), buffer.end()); 
    std::cout << "max = " << *result << std::endl;

    return 0;
}

