#include <iostream>
#include <vector>
#include <string>
#include <map>
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

    {"KEYWORD", "int"},
    {"IDENTIFIER", "b"},
    {"OPERATOR", "="},
    {"CONSTANT_INT", "3"},
    {"DELIMITER", ";"},

    {"IDENTIFIER", "a"},
    {"OPERATOR", "="},
    {"IDENTIFIER", "b"},
    {"DELIMITER", ";"},

    {"KEYWORD", "return"},
    {"CONSTANT_INT", "0"},
    {"DELIMITER", ";"},

    {"DELIMITER", "}"}
};

map<string, string> symbolTable;

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

    cout << "Семантическая ошибка: "
        << msg << endl;

    exit(1);
}

void declareVariable(string name, string type) {

    if (symbolTable.count(name)) {
        error("повторное объявление переменной " + name);
    }

    symbolTable[name] = type;

    cout << "Объявлена переменная: "
        << name << " : " << type << endl;
}

void checkVariable(string name) {

    if (!symbolTable.count(name)) {
        error("необъявленная переменная " + name);
    }
}

void semanticAnalysis() {

    cout << "Семантический анализ..." << endl;
    cout << endl;

    while (current < tokens.size()) {

        if (tokens[current].value == "int") {

            // пропуск функции main()
            if (tokens[current + 1].value == "main") {

                current += 5;
                continue;
            }

            match("KEYWORD", "int");

            string name = tokens[current].value;

            if (!match("IDENTIFIER"))
                error("ожидался идентификатор");

            declareVariable(name, "int");

            if (match("OPERATOR", "=")) {

                if (tokens[current].type == "CONSTANT_INT") {

                    match("CONSTANT_INT");
                }
                else if (tokens[current].type ==
                    "IDENTIFIER") {

                    checkVariable(tokens[current].value);

                    match("IDENTIFIER");
                }
                else {
                    error("некорректное присваивание");
                }
            }

            if (!match("DELIMITER", ";"))
                error("ожидалась ;");
        }

        else if (tokens[current].type ==
            "IDENTIFIER") {

            string name = tokens[current].value;

            checkVariable(name);

            match("IDENTIFIER");

            if (!match("OPERATOR", "="))
                error("ожидался оператор =");

            if (tokens[current].type ==
                "IDENTIFIER") {

                checkVariable(tokens[current].value);

                match("IDENTIFIER");
            }
            else if (tokens[current].type ==
                "CONSTANT_INT") {

                match("CONSTANT_INT");
            }
            else {
                error("некорректное выражение");
            }

            if (!match("DELIMITER", ";"))
                error("ожидалась ;");

            cout << "Проверено присваивание: "
                << name << endl;
        }

        else if (tokens[current].value ==
            "return") {

            match("KEYWORD", "return");

            if (tokens[current].type ==
                "CONSTANT_INT") {

                match("CONSTANT_INT");
            }
            else {
                error("некорректный return");
            }

            if (!match("DELIMITER", ";"))
                error("ожидалась ;");

            cout << "Проверен return"
                << endl;
        }

        else {
            current++;
        }
    }

    cout << endl;

    cout << "Семантический анализ завершён успешно."
        << endl;

    cout << "Ошибок не найдено."
        << endl;
}

int main() {

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");

    semanticAnalysis();

    return 0;
}