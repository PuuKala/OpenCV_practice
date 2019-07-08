// Utility functions used in OpenCV_practice utility.cpp

#include <string.h>
#include <string>
#include <array>
#include <memory>
#include <iostream>

#include "utility.h"

/**
 * @brief Execute a command line command and get the stdout
 */
std::string Exec(const char *cmd)
{
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe)
    {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr)
    {
        result += buffer.data();
    }
    return result;
}

/**
 * @brief Handle the user input from the given parameters argc and argv
 */
std::string UserInput(int argc, char const *argv[]){
    if (argc == 2)
    {
        if (strcmp(argv[1], "--crop") == 0)
        {
            return "crop";
        }
        else if (strcmp(argv[1], "-h") == 0 | strcmp(argv[1], "--help") == 0)
        {
            std::cout << "Help:" << std::endl
                      << " Commands:" << std::endl
                      << "   --crop" << std::endl
                      << "     Crops the image, so that only the middle part is shown" << std::endl
                      << "   -h --help" << std::endl
                      << "     Print this help" << std::endl
                      << std::endl;
            return "";
        }
        else
        {
            std::cout << "Unknown command. Give -h or --help for help." << std::endl;
            return "";
        }
    }
    else if (argc > 2)
    {
        std::cout << "Incorrect amount of commands. Give -h or --help for help." << std::endl;
        return "";
    }
    return "";
}