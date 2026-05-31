#include <iostream>
#include <fstream>
#include <string>

#include "Json.h"

int main()
{
    std::fstream file{"./file.json"};
    std::string content{};
    std::string line{};

    while (std::getline(file, line))
    {
        content += line + '\n';
    }

    Json::Parser jp{content};

    jp.parse();
    return 0;
}