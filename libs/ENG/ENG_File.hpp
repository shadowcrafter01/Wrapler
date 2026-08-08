#ifndef ENG_FILE_HPP
#define ENG_FILE_HPP

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <json.hpp>

#include "ENG_Console.hpp"

using json = nlohmann::json;

class filestream
{
private:
    std::string path;
    std::ofstream fileOut;
    std::ifstream fileIn;
    std::vector<std::string> names;
    std::vector<std::string> values;
    json j;

public:
    filestream(std::string path) : path{path}
    {
        fileIn.open(path);
        try
        {
            j = json::parse(fileIn);
        }
        catch (json::parse_error &e)
        {
            std::cout << " -ERROR: Could not parse JSON -> " + std::to_string(*e.what()) << "\n";
        }
        fileIn.close();
    }

    template <class T>
    void readProperty(std::string name, T *value)
    {
        if (!j[name.c_str()].empty())
        {
            *value = j[name.c_str()];
            console.log("Read " + name + " -> " + std::to_string(*value) + " from file: "+path," -FILE : ");
            return;
        }
        console.warn("Tried to read a null JSON: "+path);
        writeProperty(name,0);
        *value = 0;
        return;
    }

    template <class T>
    void writeProperty(std::string name, T value)
    {
        fileOut.open(path);
        j[name] = value;
        fileOut << j.dump();
        fileOut.close();
        console.log("Write " + name + " <- " + std::to_string(value) + " to file: "+path," -FILE : ");
    }
};

#endif