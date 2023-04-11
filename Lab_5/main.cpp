#include <iostream>

using namespace std;

template<class T>
class Set {
private:
    int maxSize;
    int currentCounter = 0;
    T *elem;
public:
    explicit Set() {
        try {
            maxSize = 0;
            elem = new T[0];
        } catch (const bad_alloc &e) {
            cout << "Error: " << e.what() << '\n';
        }
    }

    explicit Set(int size) {
        try {
            maxSize = size;
            elem = new T[size];
        } catch (const bad_alloc &e) {
            cout << "Error: " << e.what() << '\n';
        }
    }

    virtual ~Set() {
        delete[] elem;
        maxSize = 0;
        currentCounter = 0;
    }

    T *decreaseArray(int &maxSize, int index) {
        maxSize -= 1;
        T *elem = new T[maxSize];
        for (int i = 0; i < index; ++i) {
            elem[i] = this->elem[i];
        }
        for (int i = index; i < maxSize; ++i) {
            elem[i] = this->elem[i + 1];
        }
        delete[] this->elem;
        return elem;
    }

    void addElem(T element) {
        if (checkElemInSet(element)) {
            if (currentCounter < maxSize) {
                elem[currentCounter] = element;

                currentCounter++;
            }
        }
    }

    bool checkElemInSet(T element, int &index) {
        for (int i = 0; i < maxSize; ++i) {
            if (element == elem[i]) {
                index = i;
                break;
            }
        }
        return index == -1;
    }

    bool checkElemInSet(T element) {
        for (int i = 0; i < maxSize; ++i) {
            if (element == elem[i]) {
                return false;
            }
        }
        return true;
    }

    Set operator+(const Set &set){
        Set<T> newSet(5);
        for (int i = 0; i < currentCounter; i++) {
            newSet.addElem(elem[i]);
        }
        for (int i = 0; i < set.currentCounter; i++) {
            if (newSet.checkElemInSet(set.elem[i])) {
                newSet.addElem(set.elem[i]);
            }
        }
        return newSet;
    }

    Set operator*(Set &set) {
        Set<T> newSet(5);
        if (set.maxSize >= maxSize) {
            for (int i = 0; i < maxSize; ++i) {
                if (!set.checkElemInSet(elem[i])) {
                    newSet.addElem(elem[i]);
                }
            }
        } else {
            for (int i = 0; i < set.maxSize; ++i) {
                if (!checkElemInSet(set.elem[i])) {
                    newSet.addElem(set.elem[i]);
                }
            }
        }
        return newSet;
    }

    friend istream &operator>>(istream &in, Set &set) {
        T element;
        in >> element;
        set.addElem(element);
        return in;
    }

    friend ostream &operator<<(ostream &os, const Set &set) {
        for (int i = 0; i < set.currentCounter; ++i) {
            os << set.elem[i] << " ";
        }
        cout << '\n';
        return os;
    }
};

// {Ski Skate Biathlon Hockey Bobsleigh}
int main() {
    Set<string> firstStadium(5);
    int sizeFirstStadium;
    cin >> sizeFirstStadium;
    for (int i = 0; i < sizeFirstStadium; ++i) {
        cin >> firstStadium;
    }

    Set<string> secondStadium(5);
    int sizeSecondStadium;
    cin >> sizeSecondStadium;
    for (int i = 0; i < sizeSecondStadium; ++i) {
        cin >> secondStadium;
    }

    Set<string> thirdStadium(5);
    int sizeThirdStadium;
    cin >> sizeThirdStadium;
    for (int i = 0; i < sizeThirdStadium; ++i) {
        cin >> thirdStadium;
    }

    Set<string> unificationSet = firstStadium + secondStadium + thirdStadium;
    cout << unificationSet;
    Set<string> intersectionSet = firstStadium * secondStadium * thirdStadium;
    cout << intersectionSet;
}
