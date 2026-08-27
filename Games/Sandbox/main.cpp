#include "Core/Engine.h"

#include <iostream>

int main()
{
    std::string version = Engine::GetVersionString();
    std::cout << version << std::endl;
    return 0;
}
