#include <iostream>
#include <list>
#include <string>
#include <utility>

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
        filmName =  move(_filmName);
        cost = _cost;
        directorName = move(_directorName);
    }
};

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
    _List_iterator<info> it;
    it = filmList.begin();
    while (it != filmList.end()) {
        cout << *it;
        it++;
    }

    double maxCost = filmList.begin()->cost, minCost = filmList.begin()->cost;
    for (auto i: filmList) {
        if (i.cost > maxCost){
            maxCost = i.cost;
        }
        if (i.cost < minCost){
            minCost = i.cost;
        }
    }

    cout << endl << "The Result: " << endl;
    for (auto i: filmList) {
        if(i.cost > (maxCost + minCost) / 2){
            cout << i << endl;
        }
    }
}