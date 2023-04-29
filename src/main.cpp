#include "Application.h"
#include "Intro.h""

#include <iostream>

int main()
{
    //Intro start;

    Application app{ 1280, 720, 4, "Viking Quest: The Green Crusade" };

    app.start();

    return 0;
}