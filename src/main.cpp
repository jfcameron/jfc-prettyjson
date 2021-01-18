// © 2021 Joseph Cameron - All Rights Reserved

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>

#include <unistd.h> 

#include <nlohmann/json.hpp>

#include <prettyjson/buildinfo.h>

int main(int argc, char **argv)
{
    int indent_size_in_spaces(4);

    if (argc == 2)
    {
        std::string first(argv[1]);

        if (first == "-h" || first == "--help")
        {
            std::cout
                << "=== " << prettyjson_BuildInfo_ProjectName << " ===" << "\n" 
                << "Linux filter program for pretty printing and validating JSON.\n"
                << "If the JSON is well-formed, pretty prints, otherwise prints an error.\n"
                << "E.g: `curl https://some.json/api | " << prettyjson_BuildInfo_ProjectName << "`\n"
                << "You can also specify indent size in space by providing an integer parameter" << "\n"
                << "E.g: `curl https://some.json/api | " << prettyjson_BuildInfo_ProjectName << " 2`" << "\n"
                << "=== build info ===\n"
                << "project remote: " << prettyjson_BuildInfo_Git_Remote_URL << "\n"
                << "git hash: " << prettyjson_BuildInfo_Git_Commit << "\n"
                << "build date: " << prettyjson_BuildInfo_Git_Date << "\n";

            return EXIT_SUCCESS;
        }

        try
        {
            auto i = std::stoi(first);

            indent_size_in_spaces = i;
        }
        catch(std::invalid_argument)
        {
            std::cerr << "indent size param must be convertible to an integer. Using default value\n";
        }
        catch(std::out_of_range)
        {
            std::cerr << "indent size param out of range. Using default value\n";
        }
    }
    
    try
    {
        if (!isatty(0)) // I assume stdin is from a pipe if not a tty
        {
            std::stringstream stdin_content;

            for (std::string current_line; std::getline(std::cin, current_line);) 
                stdin_content << current_line << std::endl;

            using namespace nlohmann;

            const json root = json::parse(stdin_content.str());

            std::cout << root.dump(indent_size_in_spaces);
        }
        /*else {operate on file instead?}*/
    }
    catch (nlohmann::detail::parse_error e)
    {
        std::cout << "JSON Malformed: " << e.what() << "\n";
    }

    return EXIT_SUCCESS;
}

