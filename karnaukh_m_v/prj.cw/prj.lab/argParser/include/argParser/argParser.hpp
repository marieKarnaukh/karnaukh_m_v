#ifndef ARG_PARSER_HPP
#define ARG_PARSER_HPP

#include <iostream>
#include <map>
#include <string>
#include <memory>
#include <vector>

namespace ArgumentParser {

    enum class ArgType {
        String,
        Integer,
        Boolean,
        NotFind
    };

    /**
     * \brief �����, �������������� ��������.
     */
    // ����� ��� �������� ���������� �� ����������
    template <typename T>
    class Argument {
    public:
        ArgType type = ArgType::NotFind;        /**< ��� ��������� */
        std::string name = "";                  /**< ������ ��� ��������� */
        std::string shortName = "";             /**< �������� ��� ��������� */
        std::string description = "";           /**< �������� ��������� */
        T value{};                              /**< �������� ��������� */
        std::vector<T> values{};                /**< �������� ������-��������� */
        bool valueProvided = false;             /**< ������� �� �������� ��������/�������� */
        bool flag = false;                      /**< �������� ����� */
        bool defaultValue = false;              /**< ���� �� ��������� �������� */
        size_t minArgsCount = 0;                /**< ���������� ���������� �������� ��� ������-��������� */
        bool multi_value = false;               /**< �������� �� ������-���������� */
        bool store = false;                     /**< ���� �� ��������� */
        T* store_value = &value;                /**< ��������� */
        std::vector<T>* store_values = &values; /**< ��������� ��� ������-��������� */
        bool print = false;                     /**< ���� �� �������� ���������� � PrintHelp */
        
    public:
        /**
         * \brief ������������� �������� �� ��������� ��� ����� ������������ ���������.
         * \param val �������� ��������� �� ���������.
         * \return ������ �� ������ Argparser.
         */
        Argument<T>& Default(const T& val);

        /**
         * \brief ������������� �������� �� ��������� ��� ����� ������������ ���������.
         * \param val �������� ��������� �� ���������.
         * \return ������ �� ������ Argparser.
         */
        Argument<T>& Default(const std::vector<T>& val);

        /**
         * \brief ������ ����������� ���������� ���������� ��� ����� ������������ ������-���������.
         * \param minArgsCount ����������� ���������� ����������.
         * \return ������ �� ������ Argparser.
         */
        Argument<T>& MultiValue(size_t minArgsCounter = 1);
 
        /**
         * \brief ��������� �������� ����� ������������ ��������� � ��������� ����������.
         * \param variable ����������, � ������� ����� ��������� ��������.
         * \return ������ �� ������ Argparser.
         */
        Argument<T>& StoreValue(T& variable);

        /**
         * \brief ��������� �������� ����� ������������ ��������� � ��������� ����������.
         * \param variable ����������, � ������� ����� ��������� ��������.
         * \return ������ �� ������ Argparser.
         */
        Argument<T>& StoreValues(std::vector<T>& variable);

        /**
         * \brief ��������� �������� ����� ������������ ���������.
         * \param descr �������� ���������.
         * \return ������ �� ������ Argparser.
         */
        Argument<T>& AddDescription(const std::string& descr);

        /**
         * \brief ������ �������� ������������ ���������.
         * \param value �������� ���������.
         */
        void SetValue(const T& value);
    };

    /**
     * \brief �����, �������������� ���������� ���������� ��������� ������.
     */
    class ArgParser {
    public:
        /**
         * \brief ������� ������ ArgParser � �������� ������ ���������.
         * \param name �������� ���������.
         */
        explicit ArgParser(const std::string& name);

        /**
         * \brief ��������� ��������� �������� � ��������� ������.
         * \param name ��� ���������.
         * \return ������ �� ������ Argparser.
         */
        Argument<std::string>& AddStringArgument(const std::string& name);

        /**
         * \brief ��������� ��������� �������� � ��������� �������� ������ � ������ ������.
         * \param shortName �������� ��� ���������.
         * \param name ������ ��� ���������.
         * \return ������ �� ������ Argparser.
         */
        Argument<std::string>& AddStringArgument(char shortName, const std::string& name);

        /**
         * \brief ��������� ������������� �������� � ��������� ������.
         * \param name ��� ���������.
         * \return ������ �� ������ Argparser.
         */
        Argument<int>& AddIntArgument(const std::string& name);

        /**
         * \brief ��������� ������������� �������� � ��������� �������� ������ � ������ ������.
         * \param shortName �������� ��� ���������.
         * \param name ������ ��� ���������.
         * \return ������ �� ������ Argparser.
         */
        Argument<int>& AddIntArgument(char shortName, const std::string& name);

        /**
         * \brief ��������� ��������-���� � ��������� �������� ������ � ������ ������.
         * \param shortName �������� ��� ���������.
         * \param name ������ ��� ���������.
         * \return ������ �� ������ Argparser.
         */
        Argument<bool>& AddFlag(char shortName, const std::string& name);

        /**
         * \brief ����������� ��������� ��������� ������ � ��������� �������� ����������.
         * \param args ��������� ��������� ������.
         * \return True, ���� �������������� ������ ������ �������, false � ��������� ������.
         */
        bool Parse(std::vector<std::string>& args);

        /**
         * \brief ����������� ��������� ��������� ������ � ��������� �������� ����������.
         * \param argc �������� ��������� ������.
         * \param argv �������� ��������� ������.
         * \return True, ���� �������������� ������ ������ �������, false � ��������� ������.
         */
        bool Parse(int argc, char** argv);

        /**
         * \brief ������� ���������� ��������� �� ������� ��������� ����������.
         */
        void PrintHelp() const;

        /**
         * \brief ��������� ������������� ����������� ���������.
         * \param posCount ���������� ����������� ����������.
         * \return ������ �� ������ Argparser.
         */
        ArgParser& AddIntPositional(size_t posCount = 1);

        /**
         * \brief ��������� ��������� ����������� ���������.
         * \param posCount ���������� ����������� ����������.
         * \return ������ �� ������ Argparser.
         */
        ArgParser& AddStringPositional(size_t posCount = 1);

        ArgParser& Store(std::vector<std::string>& var);
        ArgParser& Store(std::vector<int>& var);

        /**
         * \brief ��������� ��������� �������� ���������� ���������.
         * \param name ��� ���������.
         * \param index ������ ������������� ��������� (��� ������-���������).
         * \return ��������� �������� ���������.
         */
        std::string GetStringValue(const std::string& name, const int index = 0) const;

        /**
         * \brief ��������� ������������� �������� ���������� ���������.
         * \param name ��� ���������.
         * \param index ������ ������������� ��������� (��� ������-���������).
         * \return ������������� �������� ���������.
         */
        int GetIntValue(const std::string& name, const int index = 0) const;

        /**
         * \brief ��������� ���������� �������� ���������� ���������.
         * \param name ��� ���������.
         * \return ���������� �������� ���������.
         */
        bool GetFlag(const std::string& name) const;

        /**
         * \brief ��������� ��������� ����������� �������� ���������� �������.
         * \param index ������ ������������� ���������.
         * \return ��������� �������� ������������ ���������.
         */
        std::string GetStringPositional(const int index) const;

        /**
         * \brief ��������� ������������� ����������� �������� ���������� �������.
         * \param index ������ ������������� ���������.
         * \return ������������� �������� ������������ ���������.
         */
        int GetIntPositional(const int index) const;

        /**
         * \brief ���������� ���������� ����������� ����������.
         * \return ���������� ����������� ����������.
         */
        size_t GetPositionalCount() const;

        /**
         * \brief ���������� ���������� �������� ���������.
         * \param name ��� ���������.
         * \return ���������� �������� ���������.
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
