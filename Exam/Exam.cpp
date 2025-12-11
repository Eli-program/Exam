#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ifstream in("StudentAnswers.txt");
    if (!in) {
        cerr << "Failed to open StudentAnswers.txt\n";
        return 1;
    }

    // Read entire file into a string
    ostringstream ss;
    ss << in.rdbuf();
    string StudentAnswers = ss.str();

    cout << "Read " << StudentAnswers.size() << " bytes from StudentAnswers.txt\n";
    return 0;
}

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
    int correct = CorrectAnswers(StudentAnswers, AnswerKey);
    cout << "Number of correct answers: " << correct << "\n";
    cout << "Score: " << (static_cast<double>(correct) / AnswerKey.size()) * 100 << "%\n";
}

