#include <iostream>
#include <vector>
#include <string>
#include <windows.h>

using namespace std;

struct Token {
    string type;
    string value;
};

vector<Token> tokens = {

    {"KEYWORD", "int"},
    {"IDENTIFIER", "main"},
    {"DELIMITER", "("},
    {"DELIMITER", ")"},
    {"DELIMITER", "{"},

    {"KEYWORD", "int"},
    {"IDENTIFIER", "a"},
    {"OPERATOR", "="},
    {"CONSTANT_INT", "5"},
    {"DELIMITER", ";"},

    {"KEYWORD", "return"},
    {"CONSTANT_INT", "0"},
    {"DELIMITER", ";"},

    {"DELIMITER", "}"}
};

int current = 0;

Token currentToken() {
    return tokens[current];
}

bool match(string type, string value = "") {

    if (current >= tokens.size())
        return false;

    if (tokens[current].type == type) {

        if (value == "" || tokens[current].value == value) {
            current++;
            return true;
        }
    }

    return false;
}

void error(string msg) {
    cout << "Синтаксическая ошибка: "
        << msg << endl;
    exit(1);
}

void parseProgram() {

    cout << "Program" << endl;

    if (!match("KEYWORD", "int"))
        error("ожидался int");

    if (!match("IDENTIFIER"))
        error("ожидалось имя функции");

    if (!match("DELIMITER", "("))
        error("ожидалась (");

    if (!match("DELIMITER", ")"))
        error("ожидалась )");

    if (!match("DELIMITER", "{"))
        error("ожидалась {");

    cout << "|-- Function main" << endl;

    while (current < tokens.size() &&
        tokens[current].value != "}") {

        if (tokens[current].value == "int") {

            match("KEYWORD", "int");

            string name = tokens[current].value;

            if (!match("IDENTIFIER"))
                error("ожидался идентификатор");

            cout << "|-- VarDecl: "
                << name << endl;

            if (match("OPERATOR", "=")) {

                string value = tokens[current].value;

                if (!match("CONSTANT_INT"))
                    error("ожидалось число");

                cout << "|   |-- value: "
                    << value << endl;
            }

            if (!match("DELIMITER", ";"))
                error("ожидалась ;");
        }

        else if (tokens[current].value == "return") {

            match("KEYWORD", "return");

            string value = tokens[current].value;

            if (!match("CONSTANT_INT"))
                error("ожидалось число");

            if (!match("DELIMITER", ";"))
                error("ожидалась ;");

            cout << "|-- ReturnStmt: "
                << value << endl;
        }

        else {
            error("неожиданный токен: "
                + tokens[current].value);
        }
    }

    if (!match("DELIMITER", "}"))
        error("ожидалась }");

    cout << endl;
    cout << "Синтаксический анализ завершён успешно."
        << endl;
}

int main() {

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");

    parseProgram();

    return 0;
}