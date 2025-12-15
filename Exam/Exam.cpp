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