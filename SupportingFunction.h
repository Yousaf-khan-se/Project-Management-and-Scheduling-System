// Muhammad_Yousaf_22i8797_F
#ifndef SUPPORTINGFUNCTION_H
#define SUPPORTINGFUNCTION_H

#include <iostream>
#include <limits>
#undef max

using namespace std;

void IntInputAndValidation(short int &choice, int lowerLimit, int upperLimit)
{
    while (true)
        if (cin >> choice)
        {
            if (choice < lowerLimit || choice > upperLimit)
            {
                std::cout << "Invalid input! (" << lowerLimit << " >= input >= " << upperLimit << ")" << endl;
                std::cout << "Enter again: ";
            }
            else
                break;
        }
        else
        {
            cin.clear();
            cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "invalid input! Enter an integer value!" << endl;
            std::cout << "Enter again: ";
        }
}
void IntInputAndValidation(int &choice, int lowerLimit, int upperLimit, int notEqualTo = -1000000)
{
    while (true)
        if (cin >> choice)
        {
            if (choice < lowerLimit || choice > upperLimit)
            {
                std::cout << "Invalid input! (" << lowerLimit << " >= input >= " << upperLimit << ")" << endl;
                std::cout << "Enter again: ";
            }
            else if (choice == notEqualTo)
            {
                std::cout << "Input must not be equat to " << notEqualTo << endl;
                std::cout << "Enter again: ";
            }
            else
                break;
        }
        else
        {
            cin.clear();
            cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "invalid input! Enter an integer value!" << endl;
            std::cout << "Enter again: ";
        }
}
void floatInputAndValidation(float &choice, int lowerLimit, int upperLimit, int notEqualTo = -1000000.0)
{
    while (true)
        if (cin >> choice)
        {
            if (choice < lowerLimit || choice > upperLimit)
            {
                std::cout << "Invalid input! (" << lowerLimit << " >= input >= " << upperLimit << ")" << endl;
                std::cout << "Enter again: ";
            }
            else if (choice == notEqualTo)
            {
                std::cout << "Input must not be equat to " << notEqualTo << endl;
                std::cout << "Enter again: ";
            }
            else
                break;
        }
        else
        {
            cin.clear();
            cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "invalid input! Enter a float value!" << endl;
            std::cout << "Enter again: ";
        }
}

#endif /* SUPPORTINGFUNCTION_H */