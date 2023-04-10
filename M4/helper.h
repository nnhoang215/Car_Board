#ifndef HELPER_H
#define HELPER_H

#include <iostream>
#include <string>
#include <cassert>
#include <sstream>
#include <vector>
#include <iostream>
#include <string.h>
#include <random>
#include <cmath>

class Helper
{
private:
    Helper();

public:

    /**
     * @brief Check whether the given string is an integer or a float 
     * 
     * @param s The given string
     * @return true if the string is an integer or a float 
     * @return false if the string is neither an integer nor a float 
     */
    static bool isNumber(std::string s);

    /**
     * @brief Split the given string given a delimeter. For instance, given the string "1,2,3" and the delimeter ",", 
     *        This string will be splited into "1","2","3", and they will be put into the vector.  
     * 
     * @param s The given string
     * @param tokens The vector containing the results
     * @param delimeter the string based on which splitting is performed
     */
    static void splitString(std::string s, std::vector<std::string>& tokens, std::string delimeter);

    /**
     * @brief Read the user input (a line) from keyboard
     * 
     * @return the user input.
     */
    static std::string readInput();

    static void printInvalidInput();
    
    /**
     * @brief return true or false based on probability
     * 
     * @param p the given probability as double from 0 -> 1
     * @return true or false based on probability
     */
    static bool probTrue(double p);

    /**
     * @brief Check whether the provided Size is valid
     * 
     * @param s The given string
     * @return true if the size is in range and is integer
     * @return false if the size is out of range or not integer
     */
    static bool isValidSize(std::string s);

    /**
     * @brief Check whether the provided probability is valid
     * 
     * @param s The given string
     * @return true if the probability is in range
     * @return false if the size is out of range
     */
    static bool isValidProbability(std::string s);
};
#endif