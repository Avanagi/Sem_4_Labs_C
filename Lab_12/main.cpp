/*4.Разбить схему на 3 части,  для каждой из частей напечатать номера цепей, которые входят в неё целиком .*/

#include <iostream>

using namespace std;

const int circles = 20; // цепи

const int elements = 14; // элементы

const int matrix[circles][elements] = // задаем матрицу 20 х 14

        {
                /* Э Л Е М Е Н Т Ы */
                {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

                {1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},

                {1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1},

                {0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0},

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

void output(const int matr[circles][elements], int circ, int elem, int l) {
    for (int i = 0; i < circ; i++) {
        for (int j = l; j < elem; j++) {
            cout << matr[i][j] << " ";
        }
        cout << " - Circle: " << i + 1 << endl;
    }
}

void decision(const int matr[circles][elements], int circ, int elem) {
    int countFirst;
    int countSecond;
    int countThird;
    for (int i = 0; i < circ; i++) {
        countFirst = 0;
        countSecond = 0;
        countThird = 0;
        for (int j = 0; j < elements / 3 + 1; j++) {
            if (matr[i][j] == 1) {
                countFirst++;
            }
        }
        for (int j = elements / 3 + 1; j < 2 * (elements / 3 + 1); j++) {
            if (matr[i][j] == 1) {
                countSecond++;
            }
        }
        for (int j = 2 * (elements / 3 + 1); j < elem; j++) {
            if (matr[i][j] == 1) {
                countThird++;
            }
        }
        if (countFirst != 0 and countSecond == 0 and countThird == 0) {
            cout << "Circle " << i + 1 << " Is Full In 1-st Part" << endl;
        } else if (countFirst == 0 and countSecond != 0 and countThird == 0) {
            cout << "Circle " << i + 1 << " Is Full In 2-nd Part" << endl;
        } else if (countFirst == 0 and countSecond == 0 and countThird != 0) {
            cout << "Circle " << i + 1 << " Is Full In 3-rd Part" << endl;
        }
    }
}

int main() {
    cout << "Initialize Matrix:" << endl;
    output(matrix, circles, elements, 0);

    cout << "1-st Part Of Matrix:" << endl;
    output(matrix, circles, elements / 3 + 1, 0);

    cout << "2-nd Part Of Matrix:" << endl;
    output(matrix, circles, 2 * (elements / 3 + 1), elements / 3 + 1);

    cout << "3-rd Part Of Matrix:" << endl;
    output(matrix, circles, elements, 2 * (elements / 3 + 1));

    decision(matrix, circles, elements);
}
