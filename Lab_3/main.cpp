#include <iostream>

using namespace std;

template<class T>
class Complex {
private:
    T Image;
    T Real;
public:
    friend ostream &operator<<(ostream &os, const Complex &complex) {
        os << complex.Real << "+i" << complex.Image;
        return os;
    }

    friend istream &operator>>(istream &in, Complex &complex) {
        in >> complex.Image;
        in >> complex.Real;
        return in;
    }

    bool operator>(const Complex &complex) const {
        return sqrt (pow (Image, 2) + pow (Real, 2)) > sqrt (pow (complex.Image, 2) + pow (complex.Real, 2));
    }

    bool operator==(const Complex &complex) const {
        return Image == complex.Image && Real == complex.Real;
    }

};

template<class T>
class Set {
private:
    int size;
    int firstSize;
    int firstCounter = 0;
    T *elem;
public:

    explicit Set(int size) {
        try {
            this->firstSize = size;
            this->size = size;
            elem = new T[size];
        } catch (const bad_alloc &e) {
            cout << "Error: " << e.what() << '\n';
        }
    }

    explicit Set(T *elem, int size) {
        try {
            for (int m = 0; m < size; m++) {
                for (int i = m + 1; i < size; i++) {
                    if (elem[m] == elem[i]) {
                        for (int k = i; k < size - 1; k++) {
                            elem[k] = elem[k + 1];
                        }
                        size--;
                    }
                }
            }

            this->firstSize = size;
            this->size = size;
            this->elem = new T[this->size];
            for (int i = 0; i < this->size; i++) {
                addElem(elem[i]);
            }
        } catch (const bad_alloc &e) {
            cout << "Error: " << e.what() << '\n';
        }
    }

    virtual ~Set() {
        delete[] elem;
    }

    T *increaseArray(int &size) {
        size += 1;
        T *elem = new T[size];
        for (int i = 0; i < size; ++i) {
            elem[i] = this->elem[i];
        }
        delete[] this->elem;
        return elem;
    }

    T *decreaseArray(int &size, int index) {
        size -= 1;
        T *elem = new T[size];
        for (int i = 0; i < index; ++i) {
            elem[i] = this->elem[i];
        }
        for (int i = index; i < size; ++i) {
            elem[i] = this->elem[i + 1];
        }
        delete[] this->elem;
        return elem;
    }

    void addElem(T element) {
        if (checkElemInSet(element)) {
            if (firstCounter < firstSize) {
                elem[firstCounter] = element;
                firstCounter++;
            } else {
                elem = increaseArray(size);
                elem[size - 1] = element;
            }
        }
    }

    void deleteElem(T element) {
        int indRemoveElem = -1;
        if (!checkElemInSet(element, indRemoveElem)) {
            elem = decreaseArray(size, indRemoveElem);
        } else {
            cout << element << " - This element does not exist" << endl;
        }

    }

    bool checkElemInSet(T element, int &index) {
        for (int i = 0; i < size; ++i) {
            if (element == elem[i]) {
                index = i;
                break;
            }
        }
        return index == -1;
    }

    bool checkElemInSet(T element) {
        for (int i = 0; i < size; ++i) {
            if (element == elem[i]) {
                return false;
            }
        }
        return true;
    }

    Set unification(const Set &set) {
        Set<T> newSet(0);
        for (int i = 0; i < size; i++) {
            newSet.addElem(elem[i]);
        }
        for (int i = 0; i < set.size; i++) {
            if (newSet.checkElemInSet(set.elem[i])) {
                newSet.addElem(set.elem[i]);
            }
        }
        return newSet;
    }

    Set intersection(Set &set) {
        Set<T> newSet(1);
        if(set.size >= size){
            for (int i = 0; i < size; ++i) {
                if(!set.checkElemInSet(elem[i])){
                    newSet.addElem(elem[i]);
                }
            }
        } else {
            for (int i = 0; i < set.size; ++i) {
                if(!checkElemInSet(set.elem[i])){
                    newSet.addElem(set.elem[i]);
                }
            }
        }
        return newSet;
    }

    void output() {
        for (int i = 0; i < size; ++i) {
            cout << elem[i] << " ";
        }
        cout << '\n';
    }

    int getSize() const {
        return size;
    }

    friend ostream &operator<<(ostream &os, const Set &set) {
        for (int i = 0; i < set.size; ++i) {
            os << set.elem[i] << " ";
        }
        os << endl;
        return os;
    }

    friend istream &operator>>(istream &in, Set<T> &set) {
        set.elem = set.increaseArray(set.size);
        in >> set.elem[set.size - 1];
        for (int m = 0; m < set.size; m++) {
            for (int i = m + 1; i < set.size; i++) {
                if (set.elem[m] == set.elem[i]) {
                    for (int k = i; k < set.size - 1; k++) {
                        set.elem[k] = set.elem[k + 1];
                    }
                    set.size--;

                }
            }
        }
        return in;
    }

};

int main() {
    Set<Complex<int>> set(0);
    for (int i = 0; i < 3; i++) {
        cin >> set;
    }
    cout << set;
    int _size;
    cin >> _size;
    Complex<int> *numbers = new Complex<int>[_size];
    for (int i = 0; i < _size; ++i) {
        cin >> numbers[i];
    }
    Set<Complex<int>> set1(numbers, _size);
    set1.output();
    Set set3 = set.unification(set1);
    cout << set3;
    Set set4 = set.intersection(set1);
    cout << set4;

}
