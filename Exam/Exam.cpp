#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cctype>

using namespace std;




int CorrectAnswers(const string& correctPath, const string& studentPath) {
    ifstream correctFile(correctPath);
    ifstream studentFile(studentPath);
    if (!correctFile.is_open() || !studentFile.is_open()) {
        cerr << "Error opening files: " << correctPath << " or " << studentPath << endl;
        return -1;
    }

    auto normalize = [](const string& token) -> char {
        for (unsigned char c : token) {
            if (!isspace(c)) return static_cast<char>(toupper(c));
        }
        return '\0';
    };

    int score = 0;
    string correctToken, studentToken;
    // Read tokens (whitespace-delimited) from both files in lockstep.
    while (correctFile >> correctToken && studentFile >> studentToken) {
        char c = normalize(correctToken);
        char s = normalize(studentToken);
        if (c != '\0' && c == s) ++score;
    }

    return score;
}

int StudentAnswers(const string& studentPath) {
    ifstream studentFile(studentPath);
    if (!studentFile.is_open()) {
        cerr << "Error opening file: " << studentPath << endl;
        return -1;
    }
    auto normalize = [](const string& token) -> char {
        for (unsigned char c : token) {
            if (!isspace(c)) return static_cast<char>(toupper(c));
        }
        return '\0';
    };
    int count = 0;
    string studentToken;
    while (studentFile >> studentToken) {
        char s = normalize(studentToken);
        if (s != '\0') ++count;
    }
    return count;
}

int main() {
    string correctPath = "CorrectAnswers.txt";
    string studentPath = "StudentAnswers.txt";
    int correctCount = CorrectAnswers(correctPath, studentPath);
    if (correctCount == -1) return 1;
    int totalCount = StudentAnswers(studentPath);
    if (totalCount == -1) return 1;
    cout << "Correct Answers: " << correctCount << endl;
    cout << "Total Answers: " << totalCount << endl;
    return 0;
}