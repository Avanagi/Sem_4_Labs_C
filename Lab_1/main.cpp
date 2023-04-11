#include <iostream>
#include <cmath>

using namespace std;

class Complex{
private:
    int Image;
    int Real;
public:
    friend ostream &operator<<(ostream &os, const Complex &complex) {
        os << "Real: " << complex.Real << " Image: " << complex.Image;
        return os;
    }
    friend istream &operator>>(istream &in, Complex &complex) {
        in >> complex.Image;
        in >> complex.Real;
        return in;
    }

    bool operator>(const Complex &complex) const{
        return sqrt(pow(Image, 2) + pow(Real, 2)) > sqrt(pow(complex.Image, 2) + pow(complex.Real, 2));
    }

};

template<class T>
class Matrix{
private:
    int size;
    T** elem;
public:

    explicit Matrix(int size) : size(size) {
         *elem = new T[size];
        for (int i = 0; i < size; ++i)
            elem[i] = new T[size];

    }

    virtual ~Matrix() {
        for (int i = 0; i < size; ++i) {
            delete elem[i];
        }
        delete[] elem;
    }

    void input(){
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                cin >> elem[i][j];
            }
        }
    }

    void output(){
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                cout << elem[i][j] << " ";
            }
            cout << endl;
        }
    }

    T getElem(int i, int j) {
        return elem[i][j];
    }

    int getSize() {
        return size;
    }

};

template<class T>
class Vector{
private:
    int size;
    T *elem;
public:

    explicit Vector(int size) : size(size) {
        elem = new T [size];
    }

    virtual ~Vector() {
        delete[] elem;
    }

    void output(){
        for (int i = 0; i < size; ++i) {
            cout << elem[i] << " ";
        }
        cout << endl;
    }

    void setElem(int index, T element) {
        elem[index] = element;
    }

};

template<typename T>
void decision(Matrix<T>& matrix, Vector<int> &vector){
    bool flag;
    for (int i = 0; i < matrix.getSize(); i++) {
        flag = false;
        for (int j = i + 1; j < matrix.getSize(); j++) {
            if(matrix.getElem(i, j) > matrix.getElem(i, i)){
                flag = true;
                break;
            }
        }
        vector.setElem(i, 0);
        if (flag){
            vector.setElem(i, 1);
        }
    }
}

int main() {
    int size;
    cin >> size;
    Matrix<float> matrix(size);
    matrix.input();
    matrix.output();
    Vector<int> vector(size);
    decision<float>(matrix, vector);
    vector.output();
}
