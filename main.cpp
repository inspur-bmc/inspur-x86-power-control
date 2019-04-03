#include "argument.hpp"

#include <iostream>

int main(int argc, char** argv)
{
    argument::ArgumentParser argumentParser(argc, argv);

    std::cout << "power_out: " << argumentParser["power_out"] << std::endl;
}
