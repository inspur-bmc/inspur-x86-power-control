#include "argument.hpp"

#include <algorithm>
#include <iostream>
#include <string>

namespace argument
{
using namespace std::string_literals;

const std::string ArgumentParser::emptyString = ""s;
const std::string ArgumentParser::trueString = "true"s;

const char* ArgumentParser::optionStr = "";

const option ArgumentParser::options[] = {
    {"power_out", required_argument, nullptr, '0'},
    {"pgood_keycode", required_argument, nullptr, '1'},
    {"pgood_path", required_argument, nullptr, '2'},
    {"post_complete_keycode", required_argument, nullptr, '3'},
    {"post_complete_path", required_argument, nullptr, '4'},
    {"help", no_argument, nullptr, 'h'},
    {0, 0, 0, 0}};

ArgumentParser::ArgumentParser(int argc, char** argv)
{
    int option = 0;
    while (-1 !=
           (option = getopt_long(argc, argv, optionStr, options, nullptr)))
    {
        if (option == 'h' || option == '?')
        {
            usage(argv);
            exit(-1);
        }
        auto i = &options[0];
        while (i->val != option && i->val != 0)
        {
            i++;
        }
        if (i->val)
        {
            auto arg = (optarg == nullptr ? "" : optarg);
            arguments[i->name] = (i->has_arg ? arg : trueString);
        }
    }
}

const std::string& ArgumentParser::operator[](const std::string& opt)
{
    auto i = arguments.find(opt);
    if (i == arguments.end())
    {
        return emptyString;
    }
    else
    {
        return i->second;
    }
}

// clang-format off
void ArgumentParser::usage(char** argv)
{
    std::cerr << "Usage: " << argv[0] << " [options]" << std::endl;
    std::cerr << "Options:" << std::endl;
    std::cerr << "  --help                         print this menu"
              << std::endl;
    std::cerr << "  --power_out=<pin number>       power out pin number"
              << std::endl;
    std::cerr << "  --pgood_keycode=<key>          pgood GPIO key number"
              << std::endl;
    std::cerr << "  --pgood_path=<path>            path of pgood input device"
              << std::endl;
    std::cerr << "  --post_complete_keycode=<key>  post_complete GPIO key number"
              << std::endl;
    std::cerr << "  --post_complete_path=<path>    path of post_complete input device"
              << std::endl;
}
// clang-format on

} // namespace argument
