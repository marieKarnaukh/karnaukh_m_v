#include <argParser/argParser.hpp>

namespace ArgumentParser {

    ArgParser::ArgParser(const std::string& name) : name_(name) {}

    Argument<std::string>& ArgParser::AddStringArgument(const std::string& name) {

        auto arg = std::make_shared<Argument<std::string>>();
        arg->type = ArgType::String;
        arg->name = name;
        argumentsString_[name] = arg;

        return *arg;
    }

    Argument<std::string>& ArgParser::AddStringArgument(char shortName, const std::string& name) {

        auto arg = std::make_shared<Argument<std::string>>();
        arg->type = ArgType::String;
        arg->name = name;
        arg->shortName = shortName;
        argumentsString_[name] = arg;
        argumentsString_[std::string(1, shortName)] = arg;

        return *arg;
    }

    Argument<int>& ArgParser::AddIntArgument(const std::string& name) {

        auto arg = std::make_shared<Argument<int>>();
        arg->type = ArgType::Integer;
        arg->name = name;
        argumentsInt_[name] = arg;

        return *arg;
    }

    Argument<int>& ArgParser::AddIntArgument(char shortName, const std::string& name) {

        auto arg = std::make_shared<Argument<int>>();
        arg->type = ArgType::Integer;
        arg->name = name;
        arg->shortName = shortName;
        argumentsInt_[name] = arg;
        argumentsInt_[std::string(1, shortName)] = arg;
        return *arg;
    }

    Argument<bool>& ArgParser::AddFlag(char shortName, const std::string& name) {

        auto arg = std::make_shared<Argument<bool>>();
        arg->type = ArgType::Boolean;
        arg->name = name;
        arg->shortName = shortName;
        argumentsFlag_[name] = arg;
        argumentsFlag_[std::string(1, shortName)] = arg;
        return *arg;
    }

    ArgParser& ArgParser::AddIntPositional(size_t posCount) {
        positionalCount = posCount;
        positionalInt = true;
        return *this;
    }

    ArgParser& ArgParser::AddStringPositional(size_t posCount) {
        positionalCount = posCount;
        positionalString = true;
        return *this;
    }

    ArgParser& ArgParser::Store(std::vector<std::string>& var) {
        posStore = true;
        storeString_values = &var;
        return *this;
    }

    ArgParser& ArgParser::Store(std::vector<int>& var) {
        posStore = true;
        storeInt_values = &var;
        return *this;
    }

    ArgType ArgParser::Find(const std::string& name) const {
        std::string argName;
        if (name.find("--") == 0) {
            argName = name.substr(2);
        }
        else if (name.find("-") == 0) {
            argName = name.substr(1);
        }
        else argName = name;
        if (argumentsInt_.count(argName) != 0) {
            return ArgType::Integer;
        }
        else if (argumentsString_.count(argName) != 0) {
            return ArgType::String;
        }
        else if (argumentsFlag_.count(argName) != 0) {
            return ArgType::Boolean;
        }
        else {
            return ArgType::NotFind;
        }
    }

    bool ArgParser::Parse(std::vector<std::string>& args) {

        size_t count = 0;

        for (size_t i = 1; i < args.size(); i++) {
            if (args[i] == "--help") {
                this->PrintHelp();
                return false;
            }
        }
        for (size_t i = 1; i < args.size(); i++) {

            if (positionalInt == true && positionalFull == false) {
                while (i + count < args.size() && count < positionalCount) {
                    try {
                        storeInt_values->push_back(std::stoi(args[i + count]));
                    }
                    catch (const std::exception&) {
                        std::cerr << "Error: Invalid value for positional arguments. Integer expected.\n";
                        storeInt_values->clear();
                        return false;
                    }

                    ++count;
                }
                i += count - 1;

            }

            else if (positionalString == true && positionalFull == false) {
                while (i + count < args.size() && count < positionalCount) {

                    storeString_values->push_back(args[i + count]);
                    ++count;
                }
                i += count - 1;
            }

            positionalFull = true;
            if (count != positionalCount)
            {
                std::cerr << "Not enough positional values" << "\n";
                return false;
            }

            const std::string& arg = args[i];
            

            if (arg.find("-") == 0) {
                std::string argName;
                if (arg.find("--") == 0) {
                    argName = arg.substr(2);
                }
                else {
                    argName = arg.substr(1);
                    if (argName.size() != 1) {
                        std::cerr << "Short name -" << argName << " must be one letter \n";
                        return false;
                    }
                }
                ArgType type = Find(argName);
                if (type == ArgType::NotFind) {
                    std::cerr << "There is no '" << argName << "' argument \n";
                    return false;
                }
                if (type == ArgType::Boolean) {
                    std::shared_ptr<Argument<bool>> argumentFlag = argumentsFlag_[argName];
                    argumentFlag->flag = true;
                    continue;
                }

                if (type == ArgType::Integer) {
                    std::shared_ptr<Argument<int>> argumentInt = argumentsInt_[argName];
                    size_t counter = 1;
                    if (argumentInt->multi_value == true) {
                        while (i + counter < args.size() && Find(args[i + counter]) == ArgType::NotFind) {
                            try {
                                (*argumentInt).SetValue(std::stoi(args[i + counter]));
                            }
                            catch (const std::exception&) {
                                if (argName.size() != 1) {
                                    std::cerr << "Error: Invalid value " << " for argument '--"
                                        << argName << "'. Integer expected.\n";
                                }
                                else {
                                    std::cerr << "Error: Invalid value " << " for argument '-"
                                        << argName << "'. Integer expected.\n";
                                }
                                (*(argumentInt->store_values)).clear();
                                return false;
                            }
                            ++counter;
                        }
                        i += counter - 1;
                        if (counter - 1 < argumentInt->minArgsCount) {
                            if (argName.size() != 1) {
                                std::cerr << "Not enough values for --" << argName << " argument \n";
                            }
                            else {
                                std::cerr << "Not enough values for -" << argName << " argument \n";
                            }
                            (*(argumentInt->store_values)).clear();
                            return false;
                        }
                    }
                    else if (Find(args[i + counter]) == ArgType::NotFind) {
                        try {
                            (*argumentInt).SetValue(std::stoi(args[i + counter]));
                        }
                        catch (const std::exception&) {
                            if (argName.size() != 1) {
                                std::cerr << "Error: Invalid value '" << argumentInt->value << "' for argument '--"
                                    << argName << "'. Integer expected.\n";
                            }
                            else {
                                std::cerr << "Error: Invalid value '" << argumentInt->value << "' for argument '-"
                                    << argName << "'. Integer expected.\n";
                            }

                            return false;
                        }
                        argumentInt->valueProvided = true;
                        ++i;
                    }
                    
                }

                if (type == ArgType::String) {

                    std::shared_ptr<Argument<std::string>> argumentString = argumentsString_[argName];
                    size_t counter = 1;
                    if (argumentString->multi_value == true) {

                        while (i + counter < args.size() && Find(args[i + counter]) == ArgType::NotFind) {

                            (*argumentString).SetValue(args[i + counter]);

                            ++counter;
                        }
                        i += counter - 1;
                        if (counter - 1 < argumentString->minArgsCount) {
                            std::cerr << "Not enough values for '" << argName << "' argument \n";
                            (*(argumentString->store_values)).clear();
                            return false;
                        }

                    }
                    else if (Find(args[i + counter]) == ArgType::NotFind)
                    {
                        (*argumentString).SetValue(args[i + counter]);
                        argumentString->valueProvided = true;
                        ++i;
                    }
                }
              
            }
        }
        if (count != positionalCount)
        {
            std::cerr << "Not enough positional values" << "\n";
            return false;
        }
        return true;
    }

    bool ArgParser::Parse(int argc, char** argv) {
        std::vector<std::string> str(argc);
        for (int i = 0; i < argc; i++) {
            str[i] = static_cast<std::string>(argv[i]);
        }
        return Parse(str);
    }

    std::string ArgParser::GetStringValue(const std::string& name, const int index) const {
        if (argumentsString_.count(name) == 0) {
            std::cerr << "There is no '" << name << "' argument";
            throw std::invalid_argument("There is no such argument");
        }
        std::shared_ptr<Argument<std::string>> arg = argumentsString_.at(name);
        if (arg->multi_value) {
            return arg->store_values->at(index);
        }
        else {
            return *arg->store_value;
        }

    }

    int ArgParser::GetIntValue(const std::string& name, const int index) const {
        if (argumentsInt_.count(name) == 0) {
            std::cerr << "There is no '" <<name<< "' argument";
            throw std::invalid_argument("Tgere is no such argument");
        }
        std::shared_ptr<Argument<int>> arg = argumentsInt_.at(name);
        if (arg->multi_value) {
            return arg->store_values->at(index);
        }
        else {
            return *arg->store_value;
        }
    }

    bool ArgParser::GetFlag(const std::string& name) const {
        if (argumentsFlag_.count(name) == 0) {
            std::cerr << "There is no '" << name << "' argument";
            throw std::invalid_argument("There is no such argument");
        }
        std::shared_ptr<Argument<bool>> arg = argumentsFlag_.at(name);
        return arg->flag;
    }

    std::string ArgParser::GetStringPositional(const int index) const {
        return positionalStringArguments_.at(index);
    }

    int ArgParser::GetIntPositional(const int index) const {
        return positionalIntArguments_.at(index);
    }

    size_t ArgParser::GetPositionalCount() const {
        return positionalCount;
    }

    size_t ArgParser::GetArgumentCount(const std::string& name) const {
        ArgType type = Find(name);
        if (type == ArgType::NotFind) {
            std::cerr << "There is no '" << name << "' argument";
            throw std::invalid_argument("There is no such argument");
        }
        else if (type == ArgType::Boolean) {
            std::cerr << "There is no values for flag";
            throw std::invalid_argument("There is no values for flag");
        }
        else if (type == ArgType::Integer) {
            std::shared_ptr<Argument<int>> arg = argumentsInt_.at(name);
            if (arg->multi_value) {
                return arg->store_values->size();
            }
            else {
                if (arg->valueProvided == true) {
                    return 1;
                }
                else return 0;
            }
        }
        else if (type == ArgType::String) {
            std::shared_ptr<Argument<std::string>> arg = argumentsString_.at(name);
            if (arg->multi_value) {
                return arg->store_values->size();
            }
            else {
                if (arg->valueProvided == true) {
                    return 1;
                }
                else return 0;
            }
        }
        return 0;
    }

    void ArgParser::PrintHelp() const {
        std::cout << name_ << "\n";
        for (const auto& pair : argumentsInt_) {
            Argument<int>& argument = *(pair.second);
            if (!argument.print) {
                if (!argument.shortName.empty()) {
                    std::cout << "-" << argument.shortName << ", ";
                }
                std::cout << "--" << argument.name << " <";
                std::cout << "Integer";
                std::cout << ">";
                if (argument.minArgsCount >= 1) {
                    std::cout << " [repeated, min args = " << argument.minArgsCount << "]";
                }
                if (argument.defaultValue) {
                    std::cout << " [default = ";
                    if (argument.multi_value) {
                        for (int i = 0; i < argument.store_values->size(); i++) {
                            std::cout << argument.store_values->at(i) << " ";
                        }
                    }
                    else {
                        std::cout << argument.value;
                    }
                    std::cout << "]";
                }
                if (argument.description.size() != 0) {
                    std::cout << " Description : " << argument.description << " ";
                }
                argument.print = true;
                std::cout << "\n";
            }
        }

        for (const auto& pair : argumentsString_) {
            Argument<std::string>& argument = *(pair.second);
            if (!argument.print) {
                if (!argument.shortName.empty()) {
                    std::cout << "-" << argument.shortName << ", ";
                }
                std::cout << "--" << argument.name << " <";
                std::cout << "String";
                std::cout << ">";
                if (argument.multi_value) {
                    std::cout << " [repeated, min args = " << argument.minArgsCount << "]";
                }
                if (argument.defaultValue) {
                    std::cout << " [default = ";
                    if (argument.multi_value) {
                        for (int i = 0; i < argument.store_values->size(); i++) {
                            std::cout << argument.store_values->at(i) << " ";
                        }
                    }
                    else {
                        std::cout << argument.value;
                    }
                    std::cout << "]";
                }
                if (argument.description.size() != 0) {
                    std::cout << " Description : " << argument.description << " ";
                }
                argument.print = true;
                std::cout << "\n";
            }
        }

        for (const auto& pair : argumentsFlag_) {
            Argument<bool>& argument = *(pair.second);
            if (!argument.print) {
                if (!argument.shortName.empty()) {
                    std::cout << "-" << argument.shortName << ", ";
                }
                std::cout << "--" << argument.name << " <";
                std::cout << "Boolean";
                std::cout << ">";
                if (argument.description.size() != 0) {
                    std::cout << " Description : " << argument.description << " ";
                }
                argument.print = true;
                std::cout << "\n";
            }
        }
    }

}
