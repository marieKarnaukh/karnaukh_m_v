#include <iostream>
#include <fstream>
#include <argParser/argParser.hpp>

int main(int argc, char** argv) {
    ArgumentParser::ArgParser parser("argParserTest");

    // Adding a positional argument for the file name
    parser.AddStringPositional(1);

    // Adding an argument to write a value to a file
    parser.AddStringArgument('w', "write").MultiValue(1).AddDescription("Write a value to a file");

    // Adding an argument to output the contents of the file
    parser.AddFlag('p', "print").AddDescription("Print the content of the file");
    

    if (parser.Parse(argc, argv)) {

        // Getting the value of a positional argument (file name)
        if (parser.GetPositionalCount() > 0) {
            std::string fileName = parser.GetStringPositional(0);

            // Checking the "--write" argument for writing to a file
            if (parser.GetArgumentCount("write") > 0) {
                std::string value = "";
                for (int i = 0; i < parser.GetArgumentCount("write"); i++) {
                    value += parser.GetStringValue("write", i) + " ";
                }
                value.resize(value.size() - 1);
                std::cout << "Writing value '" << value << "' to file: " << fileName << std::endl;

                // Writing a value to a file
                std::ofstream outputFile(fileName);
                if (outputFile.is_open()) {
                    outputFile << value;
                    outputFile.close();
                }
                else {
                    std::cout << "Failed to write to file: " << fileName << std::endl;
                }
            }
            
            // Checking the "--print" argument to output the contents of the file
            if (parser.GetFlag("print")) {
                std::cout << "Printing content of file: " << fileName << std::endl;

                // Opening and printing file contents
                std::ifstream inputFile(fileName);
                if (inputFile.is_open()) {
                    std::string line;
                    while (std::getline(inputFile, line)) {
                        std::cout << line << std::endl;
                    }
                    inputFile.close();
                }
                else {
                    std::cout << "Failed to open file: " << fileName << std::endl;
                }
            }

            
        }
    }

    return 0;
}

