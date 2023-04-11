#include <iostream>
#include <list>
#include <string>
#include <utility>
#include <algorithm>

using namespace std;

struct info {
public:
    string filmName;
    double cost;
    string directorName;

    friend istream &operator>>(istream &in, info &ob) {
        cout << "filmName:";
        in >> ob.filmName;
        cout << "Cost:";
        in >> ob.cost;
        cout << "directorName:";
        in >> ob.directorName;
        return in;
    }

    friend ostream &operator<<(ostream &out, info &ob) {
        out << endl;
        out << "filmName:" << ob.filmName << endl;
        out << "Cost:" << ob.cost << endl;
        out << "directorName:" << ob.directorName << endl;
        return out;
    }

    explicit info(string _filmName = "", double _cost = 0.0, string _directorName = "") {
        filmName = std::move(_filmName);
        cost = _cost;
        directorName = std::move(_directorName);
    }
};

struct Average {
public:
    double maxCost;
    double minCost;

    explicit Average(double _maxCost = 0.0, double _minCost = 1000000.0) {
        maxCost = _maxCost;
        minCost = _minCost;
    }

    void operator()(const info &x) {
        if(x.cost > maxCost)
            maxCost = x.cost;
        if(x.cost < minCost)
            minCost = x.cost;
    }

};

Average averageNumber;

bool check(const info& x) {
    return ((x.cost > (averageNumber.minCost + averageNumber.maxCost) / 2));
}

int main() {
    int N;
    cout << "Input N:";
    cin >> N;
    info film;
    list<info> filmList;
    printf("\nInput list: \n");
    for (int i = 0; i < N; i++) {
        cin >> film;
        filmList.push_back(film);
    }

    printf("\nOutput list: \n");
    auto it = filmList.begin();
    while (it != filmList.end()) {
        cout << *it;
        it++;
    }

    averageNumber = for_each(filmList.begin(), filmList.end(), averageNumber);

    printf("\nThe Result: \n");
    it = filmList.begin();
    while (it != filmList.end()) {
        it = find_if(it, filmList.end(), check);
        if (it != filmList.end()) {
            cout << *it << endl;
            it++;
        }
    }
}