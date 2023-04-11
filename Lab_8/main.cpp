#include <iostream>
#include <vector>

using namespace std;

bool checkElem(const vector<int> &vector1, int A, int B) {
    for (int i: vector1) {
        if (i > A && i < B) {
            return true;
        }
    }
    return false;
}

void decision(bool check, const vector<int> &vector1, int A, int B) {
    int index;
    int number;
    vector<int>::const_iterator it;
    it = vector1.begin();
    if (!check) {
        cout << "No Elems In Current Range" << endl;
    } else {
        for (int i: vector1) {
            if (i > A && i < B) {
                index = distance(vector1.begin(), vector1.begin() + i);
                number = i;
                break;
            }
        }
        cout << "Number: " << number << "Index: " << index;
    }
}

int main() {
    int N;
    cin >> N;
    vector<int> vector1;
    int l;
    for (int i = 0; i < N; ++i) {
        cin >> l;
        vector1.push_back(l);
    }
    for (int i = 0; i < N; ++i) {
        cout << vector1[i] << " ";
    }
    int A;
    int B;
    cin >> A >> B;
    decision(checkElem(vector1, A, B), vector1, A, B);
}
