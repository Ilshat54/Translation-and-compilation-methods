#include <iostream>
#include <fstream>
#include <regex>
#include <string>
#include <windows.h>

using namespace std;

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    ifstream input("test.cpp");
    ofstream output("cleaned.cpp");

    if (!input.is_open()) {
        cout << "ќшибка открыти€ файла!" << endl;
        return 1;
    }

    string code((istreambuf_iterator<char>(input)),
        istreambuf_iterator<char>());

    regex multiLineComments(R"(/\*[\s\S]*?\*/)");
    code = regex_replace(code, multiLineComments, "");

    if (regex_search(code, regex(R"(/\*[\s\S]*$)"))) {
        cout << "ќшибка: незакрытый многострочный комментарий!" << endl;
    }

    regex singleLineComments(R"(//.*)");
    code = regex_replace(code, singleLineComments, "");

    regex trim(R"(^\s+|\s+$)");
    code = regex_replace(code, trim, "");

    regex emptyLines(R"(\n\s*\n)");
    code = regex_replace(code, emptyLines, "\n");

    output << code;

    cout << "ќчистка завершена. ќшибок не вы€влено." << endl;

    return 0;
}