#ifndef ARG_PARSER_HPP
#define ARG_PARSER_HPP

#include <iostream>
#include <map>
#include <string>
#include <memory>
#include <vector>

namespace ArgumentParser {

    /**
     * \brief Enumeration representing argument types.
     */
    enum class ArgType {
        String,    /**< String argument type */
        Integer,   /**< Integer argument type */
        Boolean,   /**< Boolean (flag) argument type */
        NotFind    /**< Value of argument */
    };

    /**
     * \brief Struct representing an argument.
     */
    // Struct to store argument information
    template <typename T>
    class Argument {
    public:
        ArgType type = ArgType::NotFind;        /**< Type of argument */
        std::string name = "";                  /**< Full name of the argument */
        std::string shortName = "";             /**< Short name of the argument */
        std::string description = "";           /**< Description of the argument */
        T value{};                              /**< The value of the argument */
        std::vector<T> values{};                /**< Multi-argument values */
        bool valueProvided = false;             /**< Did the argument get a value/values */
        bool flag = false;                      /**< Is it a flag */
        bool defaultValue = false;              /**< Is there a default value */
        size_t minArgsCount = 0;                /**< Minimum number of values for a multi-argument */
        bool multi_value = false;               /**< Is it a multi-argument */
        bool store = false;                     /**< Is there a storage */
        T* store_value = &value;                /**< Storage */
        std::vector<T>* store_values = &values; /**< Storage for multi-argument */
        bool print = false;                     /**< Is the information about the argument output in PrintHelp */
        
    public:
        /**
         * \brief Sets the default value for the previously added argument.
         * \param val The default value of the argument.
         * \return A reference to the ArgParser object.
         */
        Argument<T>& Default(const T& val);

        /**
         * \brief Sets the default values for the previously added argument.
         * \param val The default values of the argument.
         * \return A reference to the ArgParser object.
         */
        Argument<T>& Default(const std::vector<T>& val);

        /**
         * \brief Sets the minimum number of arguments for the previously added multi-value argument.
         * \param minArgsCount The minimum number of arguments.
         * \return A reference to the ArgParser object.
         */
        Argument<T>& MultiValue(size_t minArgsCounter = 1);
 
        /**
         * \brief Stores the value of the previously added argument in the specified variable.
         * \param variable The variable to store the value in.
         * \return A reference to the ArgParser object.
         */
        Argument<T>& StoreValue(T& variable);

        /**
         * \brief Stores the values of the previously added argument in the specified variable.
         * \param variable The variable to store the values in.
         * \return A reference to the ArgParser object.
         */
        Argument<T>& StoreValues(std::vector<T>& variable);

        /**
         * \brief Adds the description of the previously added argument.
         * \param descr The description of argument.
         * \return A reference to the ArgParser object.
         */
        Argument<T>& AddDescription(const std::string& descr);

        /**
         * \brief Sets the value of the added argument.
         * \param value The value of argument.
         */
        void SetValue(const T& value);
    };

    /**
     * \brief Class representing the command line argument parser.
     */
    class ArgParser {
    public:
        /**
         * \brief Constructs an ArgParser object with the given program name.
         * \param name The name of the program.
         */
        explicit ArgParser(const std::string& name);

        /**
         * \brief Adds a string argument with the specified name.
         * \param name The name of the argument.
         * \return A reference to the ArgParser object.
         */
        Argument<std::string>& AddStringArgument(const std::string& name);

        /**
         * \brief Adds a string argument with the specified short name and name.
         * \param shortName The short name of the argument.
         * \param name The name of the argument.
         * \return A reference to the ArgParser object.
         */
        Argument<std::string>& AddStringArgument(char shortName, const std::string& name);

        /**
         * \brief Adds an integer argument with the specified name.
         * \param name The name of the argument.
         * \return A reference to the ArgParser object.
         */
        Argument<int>& AddIntArgument(const std::string& name);

        /**
         * \brief Adds an integer argument with the specified short name and name.
         * \param shortName The short name of the argument.
         * \param name The name of the argument.
         * \return A reference to the ArgParser object.
         */
        Argument<int>& AddIntArgument(char shortName, const std::string& name);

        /**
         * \brief Adds a flag (boolean) argument with the specified short name and name.
         * \param shortName The short name of the argument.
         * \param name The name of the argument.
         * \return A reference to the ArgParser object.
         */
        Argument<bool>& AddFlag(char shortName, const std::string& name);

        /**
         * \brief Parses the command line arguments and populates the argument values.
         * \param args The command line arguments.
         * \return True if parsing is successful, false otherwise.
         */
        bool Parse(std::vector<std::string>& args);

        /**
         * \brief Parses the command line arguments and populates the argument values.
         * \param argc The command line argument.
         * \param argv The command line argument.
         * \return True if parsing is successful, false otherwise.
         */
        bool Parse(int argc, char** argv);

        /**
         * \brief Prints the help message with the list of available arguments.
         */
        void PrintHelp() const;

        /**
         * \brief Adds int positionals arguments.
         * \param posCount The number of positional arguments.
         * \return A reference to the ArgParser object.
         */
        ArgParser& AddIntPositional(size_t posCount = 1);

        /**
         * \brief Adds string positionals arguments.
         * \param posCount The number of positional arguments.
         * \return A reference to the ArgParser object.
         */
        ArgParser& AddStringPositional(size_t posCount = 1);

        ArgParser& Store(std::vector<std::string>& var);
        ArgParser& Store(std::vector<int>& var);

        /**
         * \brief Retrieves the string value of the specified argument.
         * \param name The name of the argument.
         * \param index The index of returned argument (for multy-value argument).
         * \return The string value of the argument.
         */
        std::string GetStringValue(const std::string& name, const int index = 0) const;

        /**
         * \brief Retrieves the integer value of the specified argument.
         * \param name The name of the argument.
         * \param index The index of returned argument (for multy-value argument).
         * \return The integer value of the argument.
         */
        int GetIntValue(const std::string& name, const int index = 0) const;

        /**
         * \brief Retrieves the bolean value of the specified argument.
         * \param name The name of the argument.
         * \return The boolean value of the argument.
         */
        bool GetFlag(const std::string& name) const;

        /**
         * \brief Retrieves the string positional argument of the specified argument.
         * \param index The index of returned argument.
         * \return The string value of the positional argument.
         */
        std::string GetStringPositional(const int index) const;

        /**
         * \brief Retrieves the integer positional argument of the specified argument.
         * \param index The index of returned argument.
         * \return The integer value of the positional argument.
         */
        int GetIntPositional(const int index) const;

        /**
         * \brief Return the count of positional arguments.
         * \return The count of positional arguments.
         */
        size_t GetPositionalCount() const;

        /**
         * \brief Return the count of values of argument.
         * \param name The name of argument.
         * \return The count of values of argument.
         */
        size_t GetArgumentCount(const std::string& name) const;

    private:
        std::string name_{};

        std::map<std::string, std::shared_ptr<Argument<int>>> argumentsInt_{};
        std::map<std::string, std::shared_ptr<Argument<std::string>>> argumentsString_{};
        std::map<std::string, std::shared_ptr<Argument<bool>>> argumentsFlag_{};

        ArgType Find(const std::string& name) const;

        size_t positionalCount = 0;
        bool positionalInt = false;
        bool positionalString = false;
        bool positionalFull = false;
        bool posStore = false;
        
        std::vector<int> positionalIntArguments_{};
        std::vector<std::string> positionalStringArguments_{};
        std::vector<int>* storeInt_values = &positionalIntArguments_;
        std::vector<std::string>* storeString_values = &positionalStringArguments_;
    };

    template <typename T>
    Argument<T>& Argument<T>::Default(const T& val) {
        if (multi_value) {
            throw std::invalid_argument("You can't store single value in multi-value argument");
        }
        if (store) {
            *store_value = val;
        }
        else {
            value = val;
        }
        defaultValue = true;
        valueProvided = true;
        return *this;
    }

    template <typename T>
    Argument<T>& Argument<T>::Default(const std::vector<T>& val) {
        if (!multi_value) {
            throw std::invalid_argument("You can't store multi-value value in single-value argument");
        }
        if (store) {
            *store_values = val;
        }
        else {
            values = val;
        }
        defaultValue = true;
        valueProvided = true;
        return *this;
    }

    template <typename T>
    Argument<T>& Argument<T>::MultiValue(size_t minArgsCounter) {
        multi_value = true;
        minArgsCount = minArgsCounter;
        return *this;
    }

    template <typename T>
    Argument<T>& Argument<T>::StoreValue(T& variable) {

        if (multi_value) {
            throw std::invalid_argument("You can't store single value in multi-value argument");
        }
        store = true;
        store_value = &variable;
        if (defaultValue) {
            *store_value = value;
        }
        return *this;
    }


    template <typename T>
    Argument<T>& Argument<T>::StoreValues(std::vector<T>& variable) {
        if (multi_value == false) {
            throw std::invalid_argument("You can't store multy values in single-value argument");
        }
        store = true;
        store_values = &variable;
        return *this;

    }

    template<typename T>
    Argument<T>& Argument<T>::AddDescription(const std::string& descr) {
        description = descr;
        return *this;
    }

    template<typename T>
    void Argument<T>::SetValue(const T& value) {

        if (multi_value) {
            store_values->push_back(value);
        }
        else {
            *store_value = value;
        }
    }

    

 }  // namespace ArgumentParser

#endif  // ARG_PARSER_HPP
