#pragma once

#include<iostream>
#include<fstream>

class Logger
{   public:
    Logger(std::string file)
    {
        this->file = file;
    }

    void createFile()
    {
        std::ofstream n(file);
        n.close();
    }

    void writeToFile(std::string text)
    {
        std::ofstream n(file, std::ios::app);
        n << text << "\n";
        n.close();
    }

    void clearFile()
    {
        std::ofstream n(file);
        n << "";
        n.close();
    }

    private:
    std::string file;
};