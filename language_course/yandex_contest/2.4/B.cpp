#include <iostream>
#include <string>

using namespace std;

string soundex(string s) {
    if (s.empty()) return "";
    
    // Convert to uppercase
    for (char &c : s) c = toupper(c);
    
    char first = s[0];
    string remaining = "";
    
    // Remove vowels from remaining part
    for (size_t i = 1; i < s.length(); ++i) {
        char c = s[i];
        if (c == 'A' || c == 'E' || c == 'H' || c == 'I' || c == 'O' || c == 'U' || c == 'W' || c == 'Y') continue;
        remaining += c;
    }
    
    // Replace letters with digits
    for (char &c : remaining) {
        if (c == 'B' || c == 'F' || c == 'P' || c == 'V') c = '1';
        else if (c == 'C' || c == 'G' || c == 'J' || c == 'K' || c == 'Q' || c == 'S' || c == 'X' || c == 'Z') c = '2';
        else if (c == 'D' || c == 'T') c = '3';
        else if (c == 'L') c = '4';
        else if (c == 'M' || c == 'N') c = '5';
        else if (c == 'R') c = '6';
    }
    
    // Collapse consecutive identical digits
    string digits = "";
    if (!remaining.empty()) {
        digits += remaining[0];
        for (size_t i = 1; i < remaining.length(); ++i) {
            if (remaining[i] != remaining[i - 1]) {
                digits += remaining[i];
            }
        }
    }
    
    // Build result: first letter + digits
    string result = "";
    result += first;
    result += digits;
    
    // Truncate to 4 characters
    if (result.length() > 4) {
        result = result.substr(0, 4);
    }
    
    // Pad with zeros if less than 4
    while (result.length() < 4) {
        result += '0';
    }
    
    return result;
}

int main() {
    string word;
    while (cin >> word) {
        cout << soundex(word) << endl;
    }
    return 0;
}
