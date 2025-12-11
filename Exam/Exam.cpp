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