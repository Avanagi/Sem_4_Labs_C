#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Функция для оценки качества решения
double evaluateSolution(const vector<vector<int>>& incidenceMatrix, const vector<int>& solution) {
    double totalDistance = 0;
    for (int i = 0; i < solution.size(); i++) {
        for (int j = i + 1; j < solution.size(); j++) {
            if (incidenceMatrix[solution[i]][solution[j]] == 1) {
                totalDistance += 1;
            }
        }
    }
    return totalDistance;
}

// Функция для генерации новых решений с учетом коэффициента связности
vector<int> generateNewSolution(const vector<vector<int>>& incidenceMatrix, const vector<int>& currentSolution) {
    vector<int> newSolution = currentSolution;

    // Находим два элемента с наибольшим коэффициентом связности (исключая фиксированные элементы)
    int maxI = -1;
    int maxJ = -1;
    int maxIncidence = -1;
    for (int i = 1; i < newSolution.size(); i++) {
        for (int j = i + 1; j < newSolution.size(); j++) {
            if (incidenceMatrix[newSolution[i]][newSolution[j]] > maxIncidence) {
                maxIncidence = incidenceMatrix[newSolution[i]][newSolution[j]];
                maxI = i;
                maxJ = j;
            }
        }
    }

    // Меняем местами два элемента с наибольшим коэффициентом связности
    swap(newSolution[maxI], newSolution[maxJ]);

    return newSolution;
}

// Функция для решения задачи с использованием последовательного итерационного метода размещения
std::vector<int> solve(const vector<vector<int>>& incidenceMatrix, int fixedElement1, int fixedElement2) {
    // Инициализируем начальное решение с учетом того, что два элемента уже расположены в левом верхнем углу и по центру платы
    vector<int> currentSolution(incidenceMatrix.size());
    for (int i = 0; i < currentSolution.size(); i++) {
        currentSolution[i] = i;
    }
    swap(currentSolution[0], currentSolution[fixedElement1]);
    swap(currentSolution[currentSolution.size() / 2], currentSolution[fixedElement2]);
    vector<int>::iterator iter = currentSolution.begin();
    ++iter;
    ++iter;
    ++iter;
    random_shuffle(currentSolution.begin() + 1, iter);
    ++iter;
    ++iter;
    random_shuffle(iter, currentSolution.end());

    vector<int> newSolution = generateNewSolution(incidenceMatrix, currentSolution);

    // Оцениваем качество начального решения
    double currentScore = evaluateSolution(incidenceMatrix, currentSolution);

    // Итеративно улучшаем решение
    for (int iteration = 0; iteration < 10000; iteration++) {
        // Генерируем новое решение с помощью локальных изменений
        vector<int> newSolution = generateNewSolution(incidenceMatrix, currentSolution);

        // Оцениваем качество нового решения
        double newScore = evaluateSolution(incidenceMatrix, newSolution);

        // Если новое решение лучше текущего, то принимаем его
        if (newScore < currentScore) {
            currentSolution = newSolution;
            currentScore = newScore;
        }
    }

    return currentSolution;
}

vector<vector<int>> rebuild(const vector<vector<int>>& G)
{
    size_t vxs = G[0].size(); // Количество столбцов

    // Здесь по-хорошему нужно убедиться, что
    // в каждой строке одно и то же число столбцов

    vector<vector<int>> R(vxs, vector<int>(vxs, 0)); // Результат

    // Проход по строкам
    for (const auto& s : G)
    {
        vector<size_t> ix; // Собираем ненулевые значения
        for (size_t i = 0; i < s.size(); ++i)
            if (s[i]) ix.push_back(i);
        // Если их хотя бы 2...
        if (ix.size() > 1)
        {
            // Каждый с каждым - расставляем единицы
            for (size_t i = 0; i < ix.size() - 1; ++i)
                for (size_t j = i + 1; j < ix.size(); ++j)
                    R[ix[i]][ix[j]] = R[ix[j]][ix[i]] = 1;
        }
    }
    return R;
}

int main() {
    // Задаем матрицу инцидентности для 9 элементов
    vector<vector<int>> incidenceMatrix = {
        {1, 0, 1, 0, 0, 0, 0, 0, 0},

        {1, 1, 0, 1, 0, 0, 0, 0, 0},

        {1, 0, 0, 0, 0, 1, 0, 0, 1},

        {0, 0, 0, 0, 0, 0, 1, 0, 0},

        {0, 1, 0, 0, 0, 0, 0, 1, 0},

        {1, 0, 0, 0, 0, 0, 0, 0, 0},

        {0, 0, 0, 0, 1, 0, 0, 0, 0},

        {0, 0, 0, 0, 0, 0, 0, 0, 1},

        {0, 0, 0, 1, 0, 0, 0, 0, 1}
    };

    vector<vector<int>> R = rebuild(incidenceMatrix);


    // Задаем номера элементов, которые изначально расположены в левом верхнем углу и по центру платы
    int fixedElement1 = 0;
    int fixedElement2 = 8;

    // Решаем задачу с использованием последовательного итерационного метода размещения
    vector<int> solution = solve(R, fixedElement1, fixedElement2);

    // Выводим решение
    for (int element : solution) {
        cout << element + 1 << ' ';
    }

}