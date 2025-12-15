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
        for (char ch : line) {
            unsigned char c = static_cast<unsigned char>(ch);
            if (!isspace(c)) {
                char up = static_cast<char>(toupper(c));
                // keep only letters A-Z (commonly answer keys like A,B,C,D)
                if (up >= 'A' && up <= 'Z') outCleaned.push_back(up);
            }
        }
    }
    return true;
}

static void PrintDebugComparison(const string& student, const string& key) {
    cout << "StudentAnswers (cleaned, length=" << student.size() << "):\n" << student << "\n";
    cout << "AnswerKey      (cleaned, length=" << key.size() << "):\n" << key << "\n";

    size_t len = min(student.size(), key.size());
    cout << "Mismatches (index: student vs key):\n";
    int mismatches = 0;
    for (size_t i = 0; i < len; ++i) {
        if (student[i] != key[i]) {
            cout << i+1 << ": " << student[i] << " vs " << key[i] << "\n";
            ++mismatches;
        }
    }
    cout << "Total mismatches in compared range: " << mismatches << "\n";
    if (student.size() != key.size()) {
        cout << "Note: lengths differ (student=" << student.size() << ", key=" << key.size() << ")\n";
    }
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

    // Debug output to confirm exactly what was read and compared
    PrintDebugComparison(StudentAnswers, AnswerKey);

    GradeExam(StudentAnswers, AnswerKey);
    return 0;
}

