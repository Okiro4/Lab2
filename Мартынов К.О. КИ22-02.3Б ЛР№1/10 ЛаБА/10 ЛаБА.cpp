#include <iostream>
#include <string>
#include <fstream>
//#include <vector>
#include <regex>
//#include <iomanip>  // для setprecision
using namespace std;

class atmospheric_pressure {
public:
    string type;
    string date;
    double height;
    int meaning;

    atmospheric_pressure(string p_type1, string p_date, double p_height, int p_meaning)
    {
        type = p_type1;
        date = p_date;
        height = p_height;
        meaning = p_meaning;
    }

    void print()
    {
        cout << "Dannye po atmosfernomu davleniyu:\n"<<"Type: " <<type<< "\nData: " << date << "\nVysota: " << height << "\nZnachenie: " << meaning << "\n\n";
    }
    void write_to_file(ofstream& file) 
    {
        file << date << " " << height << " " << meaning << " " << type << "\n";
    }
};

class underwater_pressure {
public:
    string type;
    string date;
    double height;
    int meaning;
    string salinity;

    underwater_pressure(string p_type1,string p_date, double p_height, int p_meaning, string p_salinity)
    {
        type = p_type1;
        date = p_date;
        height = p_height;
        meaning = p_meaning;
        salinity = p_salinity;
    }

    void print()
    {
        cout << "Dannye po podvodnomu davleniyu:\n" << "Type: " << type << "\nData: " << date << "\nVysota: " << height << "\nZnachenie: " << meaning << "\nSolenost': " << salinity << "\n\n";

    }
    void write_to_file(ofstream& file) {
        file << date << " " << height << " " << meaning << " " << salinity << " " << type << "\n";
    }
};


void func(string& input,  smatch& match, regex& date_re, regex& height_re, regex& meaning_re, regex& salinity_re, string& date, double& height,int& meaning, string& salinity)
{


    if (regex_search(input, match, date_re))
    {
        date = match.str(0);
        input = regex_replace(input, date_re, "");
    }


    if (regex_search(input, match, height_re)) {
        height = stod(match.str(0));
        input = regex_replace(input, height_re, "");
    }

    if (regex_search(input, match, meaning_re)) {
        meaning = stoi(match.str(1));
    }

    if (regex_search(input, match, salinity_re))
    {
        salinity = match.str(1);
    }

    //return date;
}

void funf(string& input, smatch& match, regex& date_re, regex& height_re, regex& meaning_re, string& date, double& height, int& meaning)
{


    if (regex_search(input, match, date_re))
    {
        date = match.str(0);
        input = regex_replace(input, date_re, "");
    }


    if (regex_search(input, match, height_re)) {
        height = stod(match.str(0));
        input = regex_replace(input, height_re, "");
    }

    if (regex_search(input, match, meaning_re)) {
        meaning = stoi(match.str(1));
    }



    //return date;
}

int main()
{
    // Чтение данных из файла
    // поток для ввода (чтения из файла).
    ifstream file("pressure.txt");

    vector<atmospheric_pressure> atm;
    vector<underwater_pressure> und;
    //setlocale(LC_ALL, "Russian");
    int povtor = 1;
    regex type_re(R"(\b(atm|under)\b)");
    regex date_re(R"((\d{4}\.\d{2}\.\d{2}))");
    regex height_re(R"([-+]?\d+\.\d+)");
    regex meaning_re(R"(\b(\d+)\b)");
    regex salinity_re(R"(['"]\s*([^'"]+)\s*['"])");

    string line;
    while (getline(file, line))
    {
        smatch match;
        string date, salinity, type;
        double height = 0.0;
        int meaning = 0;

        if (regex_search(line, match, type_re))
        {
            type = match.str(1);
            line = regex_replace(line, type_re, "");
        }

        if (type == "atm")
        {
            funf(line, match, date_re, height_re, meaning_re, date, height, meaning);
            atm.emplace_back(date, type, height, meaning);
        }

        if (type == "under")
        {

            func(line, match, date_re, height_re, meaning_re, salinity_re, date, height, meaning, salinity);
            und.emplace_back(type, date, height, meaning, salinity);
        }
    }

    file.close();

    // Выводим данные из файла
    for (auto obj : atm) obj.print();
    for (auto obj : und) obj.print();

    while (povtor == 1)
    {
        cout << "Vvedite dannye ob'ekta v lybom porydke (naprimer: 2024.09.23 1025 100.489 atm  ili   2024.09.23 100.43 1025 under 'Min')" << endl;
        cout << "Dly vixoda vvedite exit\n";

        string input;
        getline(cin, input);

        if (input == "exit")
        {
            break;
        }

        smatch match;
        string date, salinity, type;
        double height = 0.0;
        int meaning = 0;

        if (regex_search(input, match, type_re))
        {
            type = match.str(1);
            input = regex_replace(input, type_re, "");

            if (type == "atm")
            {
                funf(input, match, date_re, height_re, meaning_re, date, height, meaning);

                atm.emplace_back(type, date, height, meaning);
                cout << "Obyekt atmosfernogo davleniya sozdan.\n\n";

                ofstream outFile("pressure.txt", ios::app);
                atm.back().write_to_file(outFile);
                outFile.close();
            }

            if (type == "under")
            {
                func(input, match, date_re, height_re, meaning_re, salinity_re, date, height, meaning, salinity);

                und.push_back(underwater_pressure(date, type, height, meaning, salinity));
                cout << "Obyekt podvodnogo davleniya sozdan?\n\n";

                ofstream outFile("pressure.txt", ios::app);
                und.back().write_to_file(outFile);
                outFile.close();
            }

            // Выводим данные после добавления объекта
            for (auto obj : atm) obj.print();
            for (auto obj : und) obj.print();
        }
    }

    return 0;
}
