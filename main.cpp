#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class Matrix {
private:
    vector<vector<int>> data;
    int size;

public:
    Matrix(const vector<vector<int>>& d) : data(d), size(d.size()) {}

    int getElement(int i, int j) const {
        return data[i][j];
    }

    vector<int> snakeLeftToRightBottomUp() const {
        vector<int> result;
        for (int i = size - 1; i >= size / 2; --i) {
            if ((size - i) % 2 == 0) {
                for (int j = size - 1; j >= 0; --j) {
                    result.push_back(data[i][j]);
                }
            } else {
                for (int j = 0; j < size; ++j) {
                    result.push_back(data[i][j]);
                }
            }
        }
        return result;
    }

    vector<int> spiralCentralOutClockwise() const {
        vector<int> result;
        int center = size / 2;
        int layers = (size + 1) / 2;
        for (int layer = 0; layer < layers; ++layer) {
            for (int i = center - layer; i <= center + layer; ++i) {
                result.push_back(data[center - layer][i]);
            }
            for (int i = center - layer + 1; i <= center + layer; ++i) {
                result.push_back(data[i][center + layer]);
            }
            if (layer > 0) {
                for (int i = center + layer - 1; i >= center - layer; --i) {
                    result.push_back(data[center + layer][i]);
                }
                for (int i = center + layer - 1; i > center - layer; --i) {
                    result.push_back(data[i][center - layer]);
                }
            }
        }
        return result;
    }
};

void printAuthorInfo() {
    cout << "Автор програми: Ім'я Прізвище, Група" << endl;
}

void printTaskInfo() {
    cout << "Завдання: Ділення націло." << endl;
    cout << "Послідовність 1 обходить нижній сектор матриці A змійкою зліва направо, знизу вверх." << endl;
    cout << "Послідовність 2 обходить лівий сектор матриці A спіраллю з центральної клітини всередину за годинниковою стрілкою." << endl;
}

vector<vector<int>> readMatrix(ifstream& inputFile) {
    int N;
    inputFile >> N;
    vector<vector<int>> matrix(N, vector<int>(N));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            inputFile >> matrix[i][j];
        }
    }
    return matrix;
}

void writeResults(ofstream& outputFile, const vector<int>& results) {
    for (int val : results) {
        outputFile << val << " ";
    }
    outputFile << endl;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Помилка: потрібно вказати шлях до вхідного та вихідного файлів." << endl;
        return 1;
    }

    string inputFilePath = argv[1];
    string outputFilePath = argv[2];

    cout << "Шлях до вхідного файлу: " << inputFilePath << endl;
    cout << "Шлях до вихідного файлу: " << outputFilePath << endl;

    ifstream inputFile(inputFilePath);
    if (!inputFile.is_open()) {
        cerr << "Помилка: не вдається відкрити вхідний файл." << endl;
        return 1;
    }

    ofstream outputFile(outputFilePath);
    if (!outputFile.is_open()) {
        cerr << "Помилка: не вдається відкрити вихідний файл." << endl;
        return 1;
    }

    printAuthorInfo();
    printTaskInfo();

    vector<vector<int>> matrixData = readMatrix(inputFile);
    Matrix matrix(matrixData);

    vector<int> sequence1 = matrix.snakeLeftToRightBottomUp();
    vector<int> sequence2 = matrix.spiralCentralOutClockwise();

    vector<int> results;
    size_t size = min(sequence1.size(), sequence2.size());
    for (size_t i = 0; i < size; ++i) {
        if (sequence2[i] != 0) {
            results.push_back(sequence1[i] / sequence2[i]);
        } else {
            results.push_back(0);
        }
    }

    writeResults(outputFile, results);

    cout << "Виконання завершено." << endl;

    inputFile.close();
    outputFile.close();

    return 0;
}
