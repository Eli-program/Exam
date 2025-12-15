// file: grader.cpp
#include <iostream>
#include <fstream>
#include <vector>
#include <cctype>
#include <string>

using namespace std;

char NormalizeToken(const string& token) {
    for (unsigned char c : token) {
        if (!isspace(c)) return static_cast<char>(toupper(c));
    }
    return '\0';
}

vector<char> ReadAnswers(const string& path) {
    ifstream file(path);
    if (!file.is_open()) {
        throw runtime_error("Failed to open file: " + path);
    }

    vector<char> answers;
    string token;

    while (file >> token) {
        char normalized = NormalizeToken(token);
        if (normalized != '\0') {
            answers.push_back(normalized);
        }
    }

    return answers;
}

int main() {
    try {
        const string correctPath = "CorrectAnswers.txt";
        const string studentPath = "StudentAnswers.txt";

        vector<char> correct = ReadAnswers(correctPath);
        vector<char> student = ReadAnswers(studentPath);

        int score = 0;
        int compareCount = min(correct.size(), student.size());

        for (int i = 0; i < compareCount; ++i) {
            if (correct[i] == student[i]) {
                ++score;
            }
        }

        cout << "Correct Answers: " << score << endl;
        cout << "Total Answers: " << student.size() << endl;
    }
    catch (const exception& e) {
        cerr << e.what() << endl;
        return 1;
    }

    return 0;
}
