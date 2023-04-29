#include "Application.h"

#include <iostream>

int main()
{
    /*std::string userName;
    std::cout << "Greetings Traveler. What is your name?" << std::endl;
    std::cin >> userName;*/

    Application app{ 1280, 720, 4, "Viking Hacks 2" };

    app.start();

    return 0;
}