#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cctype>

using namespace std;

int CorrectAnswers(const string& StudentAnswers, const string& AnswerKey) {
    int correctCount = 0;
    size_t length = min(StudentAnswers.size(), AnswerKey.size());
    for (size_t i = 0; i < length; ++i) {
        if (StudentAnswers[i] == AnswerKey[i]) {
            ++correctCount;
        }
    }
    return correctCount;
}

void GradeExam(const string& StudentAnswers, const string& AnswerKey) {
    if (AnswerKey.empty()) {
        cout << "Answer key is empty — cannot grade.\n";
        return;
    }
    int correct = CorrectAnswers(StudentAnswers, AnswerKey);
    cout << "Number of correct answers: " << correct << "\n";
    cout << "Score: " << (static_cast<double>(correct) / AnswerKey.size()) * 100 << "%\n";
}

static bool ReadAnswersFile(const string& path, string& outCleaned) {
    ifstream in(path);
    if (!in) return false;
    outCleaned.clear();
    string line;
    while (getline(in, line)) {
        for (char c : line) {
            if (!isspace(static_cast<unsigned char>(c))) outCleaned.push_back(c);
        }
    }
    return true;
}

int main() {
    string StudentAnswers;
    if (!ReadAnswersFile("StudentAnswers.txt", StudentAnswers)) {
        cerr << "Failed to open StudentAnswers.txt\n";
        return 1;
    }

    string AnswerKey;
    if (!ReadAnswersFile("CorrectAnswers.txt", AnswerKey)) {
        cerr << "Failed to open CorrectAnswers.txt\n";
        return 1;
    }

    cout << "Read " << StudentAnswers.size() << " answers from StudentAnswers.txt\n";
    cout << "Read " << AnswerKey.size() << " answers from CorrectAnswers.txt\n";

    GradeExam(StudentAnswers, AnswerKey);
    return 0;
}

