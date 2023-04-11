/*4.Разбить схему на 3 части,  для каждой из частей напечатать номера цепей, которые входят в неё целиком .*/

#include <iostream>
#include <algorithm>
#include <set>

using namespace std;

const int circles = 20; // цепи

const int elements = 14; // элементы

const int matrix[circles][elements] = // задаем матрицу 20 х 14

        {
                /* Э Л Е М Е Н Т Ы */
                {1, 1, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0},

                {1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},

                {1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1},

                {0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0},

                {0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0},

                {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},

                {0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0},

                {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0}, //Ц

                {0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0}, //Е

                {1, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 1, 0, 1}, //П

                {0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0}, //И

                {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},

                {0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1},

                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},

                {0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},

                {0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 1, 0, 1},

                {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},

                {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1},

                {0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1},

                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1},
        };

void output(const int matr[circles][elements], int circ, int elem, int l){
    for (int i = l; i < circ; i++){
        for (int j = 0; j < elem; j++) {
            cout << matr[i][j] << " ";
        }
        cout << " - Circle: " << i + 1 << endl;
    }
}

set<int> determinateElemsInPart(const int matr[circles][elements], int circ, int elem, int l){
    set <int> det;
    for (int i = l; i < circ; i++){
        for (int j = 0; j < elem; j++) {
            if(matr[i][j] == 1){
                det.insert(j + 1);
            }
        }
    }
    for (auto item: det) {
        cout << item << " ";
    }
    cout << endl;
    return det;
}

int main() {
    cout << "Initialize Matrix:" << endl;
    output(matrix, circles, elements, 0);

    cout << "1-st Part Of Matrix:" << endl;
    output(matrix, circles / 3 + 1, elements, 0);

    cout << "2-nd Part Of Matrix:" << endl;
    output(matrix, 2 * (circles / 3 + 1), elements, circles / 3 + 1);

    cout << "3-rd Part Of Matrix:" << endl;
    output(matrix, circles, elements, 2 * (circles / 3 + 1));

    cout << "Elements In 1-st Part:" << endl;
    set<int> det1 = determinateElemsInPart(matrix, circles / 3 + 1, elements, 0);

    cout << "Elements In 2-st Part:" << endl;
    set<int> det2 = determinateElemsInPart(matrix, 2 * (circles / 3 + 1), elements, circles / 3 + 1);

    cout << "Elements In 3-st Part:" << endl;
    set<int> det3 = determinateElemsInPart(matrix, circles, elements, 2 * (circles / 3 + 1));

    std::vector<int> v1(14);
    std::vector<int> v2(14);
    std::vector<int> v3(14);
    std::vector<int> v4(14);
    std::vector<int> v5(14);
    std::vector<int> v6(14);
    std::vector<int>::iterator ls1, ls2, ls3, ls4, ls5, ls6;
    ls1 = std::set_difference(det1.begin(), det1.end(), det2.begin(), det2.end(), v1.begin());
    ls2 = std::set_difference(det1.begin(), det1.end(), det3.begin(), det3.end(), v2.begin());

    ls3 = std::set_difference(det2.begin(), det2.end(), det1.begin(), det1.end(), v3.begin());
    ls4 = std::set_difference(det2.begin(), det2.end(), det3.begin(), det3.end(), v4.begin());

    ls5 = std::set_difference(det3.begin(), det3.end(), det1.begin(), det1.end(), v5.begin());
    ls6 = std::set_difference(det3.begin(), det3.end(), det2.begin(), det2.end(), v6.begin());

    v1.resize(ls1 - v1.begin());
    v2.resize(ls2 - v2.begin());
    v3.resize(ls3 - v3.begin());
    v4.resize(ls4 - v4.begin());
    v5.resize(ls5 - v5.begin());
    v6.resize(ls6 - v6.begin());

    cout << endl;
    for (auto item: v1) {
        cout << item << " ";
    }
    cout << endl;
    for (auto item: v2) {
        cout << item << " ";
    }

    cout << endl;
    cout << endl;
    for (auto item: v3) {
        cout << item << " ";
    }
    cout << endl;
    for (auto item: v4) {
        cout << item << " ";
    }

    cout << endl;
    cout << endl;
    for (auto item: v5) {
        cout << item << " ";
    }
    cout << endl;
    for (auto item: v6) {
        cout << item << " ";
    }

    vector<int> z1;
    vector<int> z2;
    vector<int> z3;
    cout << endl;
    cout << endl;
    for (auto item: v1) {
        bool found = std::find(v2.begin(), v2.end(), item) != v2.end();
        if (found){
            z1.push_back(item);
            cout << item << " ";
        }
    }
    cout << endl;
    for (auto item: v3) {
        bool found = std::find(v4.begin(), v4.end(), item) != v4.end();
        if (found){
            z2.push_back(item);
            cout << item << " ";
        }
    }
    cout << endl;
    for (auto item: v5) {
        bool found = std::find(v6.begin(), v6.end(), item) != v6.end();
        if (found){
            z3.push_back(item);
            cout << item << " ";
        }
    }


    cout << endl << "Answer" << endl;
    cout << endl;
    for (int i = 0; i < circles / 3 + 1; i++){
        int count1 = 0;
        int count2 = 0;
        for (int j = 0; j < elements; j++) {
            bool found = true;
            if(matrix[i][j] != 0){
                found = std::find(z1.begin(), z1.end(), j + 1) != z1.end();
            }
            if (found){
                count1++;
            }
            if (!found){
                count2++;
            }
        }
        if(count1 >= 2 && count2 == 0){
            cout << "Circle - " << i + 1 << endl;
        }
    }

    cout << endl;
    for (int i = circles / 3 + 1; i < 2 * (circles / 3 + 1); i++){
        int count1 = 0;
        int count2 = 0;
        for (int j = 0; j < elements; j++) {
            bool found = true;
            if(matrix[i][j] != 0){
                found = std::find(z2.begin(), z2.end(), j + 1) != z2.end();
            }
            if (found){
                count1++;
            }
            if (!found){
                count2++;
            }
        }
        if(count1 >= 2 && count2 == 0){
            cout << "Circle - " << i + 1 << endl;
        }
    }

    cout << endl;
    for (int i = 2 * (circles / 3 + 1); i < circles; i++){
        int count1 = 0;
        int count2 = 0;
        for (int j = 0; j < elements; j++) {
            bool found = true;
            if(matrix[i][j] != 0){
                found = std::find(z3.begin(), z3.end(), j + 1) != z3.end();
            }
            if (found){
                count1++;
            }
            if (!found){
                count2++;
            }
        }
        if(count1 >= 2 && count2 == 0){
            cout << "Circle - " << i + 1 << endl;
        }
    }
}
