#include "helper.h"

using std::string;
using std::vector;

Helper::Helper(){}

void Helper::printInvalidInput()
{
    std::cout << "Invalid input.\n" << std::endl;
}

bool Helper::isNumber(string s)
{
    string::const_iterator it = s.begin();
    char dot = '.';
    int nb_dots = 0;
    while (it != s.end()) 
    {
        if (*it == dot)
        {
            nb_dots++;
            if (nb_dots>1)
            {
                break;
            }
        }   
        else if (!isdigit(*it))
        {
            break;
        } 

        ++it;
    }
    return !s.empty() && s[0] != dot && it == s.end();
}

void Helper::splitString(string s, vector<string>& tokens, string delimeter)
{
    tokens.clear();
    char* _s = new char[s.length()+1];
    strcpy(_s, s.c_str());

    char * pch;
    pch = strtok (_s, delimeter.c_str());
    while (pch != NULL)
    {
        tokens.push_back(pch);
        pch = strtok (NULL, delimeter.c_str());
    }
    delete[] _s;
}

string Helper::readInput()
{
    string input;
    std::getline(std::cin, input);
    std::cout << std::endl;

    return input;
}

bool Helper::probTrue(double p) {
    return rand() < p * (RAND_MAX+1.0);
}

bool Helper::isValidSize (string s) {
    bool result = false;
    if (isNumber(s)) {
        int testInteger = std::stoi(s);
        int testDouble = std::stod(s);

        if (testInteger == testDouble) {
            if (testInteger <= 20 && testInteger >= 10) {
                result = true;
            }
        }
    }

    return result;
}

bool Helper::isValidProbability(std::string s) {
    bool result = false;
    if (isNumber(s)) {
        int testProb = std::stod(s);
        if (testProb >= 0 && testProb <= 1) {
            result = true;
        }
    }
    return result;
}