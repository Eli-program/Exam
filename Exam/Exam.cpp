
#include <iostream>
#include <fstream>
#include <vector>
#include <cctype>
#include <string>
#include <algorithm>

using namespace std;

char NormalizeToken(const string& token) {
    for (unsigned char c : token) {
        if (isalpha(c)) return static_cast<char>(toupper(c));
    }
    return '\0';
}


vector<char> ReadAnswers(const string& path) {
    ifstream file(path);
    if (!file.is_open()) {
        throw runtime_error("Failed to open file: " + path);
    }

    cout << "\nREADING FILE:\n" << path << "\n";

    vector<char> answers;
    string token;

    int i = 0;
    while (file >> token) {
        char normalized = NormalizeToken(token);
        cout << i++ << ": [" << token << "] -> " << normalized << endl;
        if (normalized != '\0') {
            answers.push_back(normalized);
        }
    }

    cout << "TOTAL READ: " << answers.size() << "\n";
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
		int grade = static_cast<int>((static_cast<double>(score) / correct.size()) * 100);
		
        cout << "Correct Answers: " << score << endl;
        cout << "Total Answers: " << student.size() << endl;
        cout << "Grade: " << grade << "%" << endl;
    }
    catch (const exception& e) {
        cerr << e.what() << endl;
        return 1;
    }


    return 0;
}
