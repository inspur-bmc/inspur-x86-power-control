#pragma once

#include <getopt.h>

#include <map>
#include <string>

namespace argument
{
class ArgumentParser
{
  public:
    ArgumentParser() = delete;
    ArgumentParser(const ArgumentParser&) = delete;
    ArgumentParser& operator=(const ArgumentParser&) = delete;
    ArgumentParser(ArgumentParser&&) = default;
    ArgumentParser& operator=(ArgumentParser&&) = default;

    ArgumentParser(int argc, char** argv);

    const std::string& operator[](const std::string& opt);

    static void usage(char** argv);

    static const std::string trueString;
    static const std::string emptyString;

  private:
    std::map<const std::string, std::string> arguments;
    static const char *optionStr;
    static const option options[];
};
} // namespace argument
