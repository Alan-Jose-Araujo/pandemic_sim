#include <example/HelloWorld.hpp>
#include <iostream>
#include <string>

void HelloWorld::sayHello()
{
    std::string msg;
    msg = "Hello World!";
    std::cout << msg << std::endl;
}