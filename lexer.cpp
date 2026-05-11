#include <iostream>
#include <fstream>
#include <vector>
#include <regex>
#include <string>
#include <windows.h>

using namespace std;

struct Token {
    string type;
    string value;
};

bool isKeyword(const string& word) {
    vector<string> keywords = {
        "int", "return", "if", "else",
        "for", "using", "namespace"
    };

    for (string k : keywords) {
        if (word == k)
            return true;
    }

    return false;
}

int main() {

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");

    ifstream input("cleaned.cpp");

    if (!input.is_open()) {
        cout << "Ошибка открытия файла!" << endl;
        return 1;
    }

    string code((istreambuf_iterator<char>(input)),
        istreambuf_iterator<char>());

    vector<Token> tokens;

    regex tokenPattern(
        R"([a-zA-Z_][a-zA-Z0-9_]*|\d+|&&|\+\+|<<|[+\-*/=<>;(),{}])"
    );

    auto words_begin =
        sregex_iterator(code.begin(), code.end(), tokenPattern);

    auto words_end = sregex_iterator();

    for (sregex_iterator i = words_begin; i != words_end; ++i) {

        string token = (*i).str();

        if (isKeyword(token)) {
            tokens.push_back({ "KEYWORD", token });
        }
        else if (regex_match(token, regex(R"(\d+)"))) {
            tokens.push_back({ "CONSTANT_INT", token });
        }
        else if (regex_match(token,
            regex(R"([a-zA-Z_][a-zA-Z0-9_]*)"))) {

            tokens.push_back({ "IDENTIFIER", token });
        }
        else if (regex_match(token,
            regex(R"(&&|\+\+|<<|[+\-*/=<>])"))) {

            tokens.push_back({ "OPERATOR", token });
        }
        else {
            tokens.push_back({ "DELIMITER", token });
        }
    }

    cout << "Лексема\t\tТип" << endl;
    cout << "-----------------------------" << endl;

    for (Token t : tokens) {
        cout << t.value << "\t\t" << t.type << endl;
    }

    cout << endl;

    cout << "Последовательность токенов:" << endl;

    cout << "[";

    for (size_t i = 0; i < tokens.size(); i++) {

        cout << "(" << tokens[i].type
            << ", " << tokens[i].value << ")";

        if (i != tokens.size() - 1)
            cout << ", ";
    }

    cout << "]" << endl << endl;

    cout << "Лексический анализ завершён успешно." << endl;
    cout << "Обнаружено " << tokens.size()
        << " токенов. Ошибок не найдено." << endl;

    return 0;
}