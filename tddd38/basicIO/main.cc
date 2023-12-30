#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;

void askInput(string question, string &text) {
    cout << question;
    getline(cin, text);
}

void printExtractedNumber(istringstream &is, int &number) {
    is >> number;
    cout << number << " ";
}

void printExtractedWord(istringstream &is, string &word) {
    is >> word;
    cout << word << " ";
}

int main() {
    // variable declarations
    istringstream is;
    string text;
    int number;
    double realNumber;
    char letter;


    askInput("Enter one integer: ", text);
    is = istringstream(text);
    cout << "You entered the number: ";
    printExtractedNumber(is, number);
    cout << endl;

    askInput("Enter four integers: ", text);
    is = istringstream(text);
    cout << "You entered the numbers: ";
    printExtractedNumber(is, number);
    printExtractedNumber(is, number);
    printExtractedNumber(is, number);
    printExtractedNumber(is, number);
    cout << endl;

    askInput("Enter one integer and one real number: ", text);
    is = istringstream(text);
    is >> number;
    is >> realNumber;
    cout << "The real is: " << realNumber << endl;
    cout << "The integer is: " << number << endl;

    askInput("Enter one integer and one real number: ", text);
    is = istringstream(text);
    is >> realNumber;
    is >> number;
    cout << "The real is: " << realNumber << endl;
    cout << "The integer is: " << number << endl;

    askInput("Enter a character: ", text);
    is = istringstream(text);
    is >> letter;
    cout << "You entered: " << letter << endl;

    askInput("Enter a word: ", text);
    is = istringstream(text);
    is >> text;
    cout << "The word '" << text << "' has " << text.length() << " character(s)." << endl;

    askInput("Enter an integer and a word: ", text);
    is = istringstream(text);
    is >> number;
    is >> text;
    cout << "You entered '" << number << "' and '" << text << "'." << endl;

    askInput("Enter an character and a word: ", text);
    is = istringstream(text);
    is >> letter;
    is >> text;
    cout << "You entered the string '" << text << "' and the character '" << letter << "'." << endl;

    askInput("Enter a word and real number: ", text);
    is = istringstream(text);
    is >> text;
    is >> realNumber;
    cout << "You entered '" << text << "' and '" << realNumber << "'." << endl;

    askInput("Enter a text-line: ", text);
    is = istringstream(text);
    is.getline(&text[0], is.tellg());
    cout << "You entered: " << text << endl;

    askInput("Enter a second line of text: ", text);
    is = istringstream(text);
    is.getline(&text[0], is.tellg());
    cout << "You entered: " << text << endl;

    askInput("Enter three words: ", text);
    is = istringstream(text);
    cout << "You entered: '";
    printExtractedWord(is, text);
    printExtractedWord(is, text);
    printExtractedWord(is, text);
    cout << "'" << endl;

    return 0;
}