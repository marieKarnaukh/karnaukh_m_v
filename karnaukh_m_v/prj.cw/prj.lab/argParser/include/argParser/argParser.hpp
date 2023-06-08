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
     * \brief Класс, представляющая аргумент.
     */
    // Класс для хранения информации об аргументах
    template <typename T>
    class Argument {
    public:
        ArgType type = ArgType::NotFind;        /**< Тип аргумента */
        std::string name = "";                  /**< Полное имя аргумента */
        std::string shortName = "";             /**< Короткое имя аргумента */
        std::string description = "";           /**< Описание аргумента */
        T value{};                              /**< Значение аргумента */
        std::vector<T> values{};                /**< Значения мульти-аргумента */
        bool valueProvided = false;             /**< Получил ли аргумент значение/значения */
        bool flag = false;                      /**< Значение флага */
        bool defaultValue = false;              /**< Есть ли дефолтное значение */
        size_t minArgsCount = 0;                /**< Минимально количество значений для мульти-аргумента */
        bool multi_value = false;               /**< Является ли мульти-аргументом */
        bool store = false;                     /**< Есть ли хранилище */
        T* store_value = &value;                /**< Хранилище */
        std::vector<T>* store_values = &values; /**< Хранилище для мульти-аргумента */
        bool print = false;                     /**< Была ли выведена информация в PrintHelp */
        
    public:
        /**
         * \brief Устанавливает значение по умолчанию для ранее добавленного аргумента.
         * \param val Значение аргумента по умолчанию.
         * \return Ссылка на объект Argparser.
         */
        Argument<T>& Default(const T& val);

        /**
         * \brief Устанавливает значения по умолчанию для ранее добавленного аргумента.
         * \param val Значения аргумента по умолчанию.
         * \return Ссылка на объект Argparser.
         */
        Argument<T>& Default(const std::vector<T>& val);

        /**
         * \brief Задает минимальное количество аргументов для ранее добавленного мульти-аргумента.
         * \param minArgsCount Минимальное количество аргументов.
         * \return Ссылка на объект Argparser.
         */
        Argument<T>& MultiValue(size_t minArgsCounter = 1);
 
        /**
         * \brief Сохраняет значение ранее добавленного аргумента в указанной переменной.
         * \param variable Переменная, в которой будет храниться значение.
         * \return Ссылка на объект Argparser.
         */
        Argument<T>& StoreValue(T& variable);

        /**
         * \brief Сохраняет значения ранее добавленного аргумента в указанной переменной.
         * \param variable Переменная, в которой будут храниться значения.
         * \return Ссылка на объект Argparser.
         */
        Argument<T>& StoreValues(std::vector<T>& variable);

        /**
         * \brief Добавляет описание ранее добавленного аргумента.
         * \param descr Описание аргумента.
         * \return Ссылка на объект Argparser.
         */
        Argument<T>& AddDescription(const std::string& descr);

        /**
         * \brief Задает значение добавленного аргумента.
         * \param value Значение аргумента.
         */
        void SetValue(const T& value);
    };

    /**
     * \brief Класс, представляющий анализатор аргументов командной строки.
     */
    class ArgParser {
    public:
        /**
         * \brief Создает объект ArgParser с заданным именем программы.
         * \param name Название программы.
         */
        explicit ArgParser(const std::string& name);

        /**
         * \brief Добавляет строковый аргумент с указанным именем.
         * \param name Имя аргумента.
         * \return Ссылка на объект Argparser.
         */
        Argument<std::string>& AddStringArgument(const std::string& name);

        /**
         * \brief Добавляет строковый аргумент с указанным коротким именем и полным именем.
         * \param shortName Короткое имя аргумента.
         * \param name Полное имя аргумента.
         * \return Ссылка на объект Argparser.
         */
        Argument<std::string>& AddStringArgument(char shortName, const std::string& name);

        /**
         * \brief Добавляет целочисленный аргумент с указанным именем.
         * \param name Имя аргумента.
         * \return Ссылка на объект Argparser.
         */
        Argument<int>& AddIntArgument(const std::string& name);

        /**
         * \brief Добавляет целочисленный аргумент с указанным коротким именем и полным именем.
         * \param shortName Короткое имя аргумента.
         * \param name Полное имя аргумента.
         * \return Ссылка на объект Argparser.
         */
        Argument<int>& AddIntArgument(char shortName, const std::string& name);

        /**
         * \brief Добавляет аргумент-флаг с указанным коротким именем и полным именем.
         * \param shortName Короткое имя аргумента.
         * \param name Полное имя аргумента.
         * \return Ссылка на объект Argparser.
         */
        Argument<bool>& AddFlag(char shortName, const std::string& name);

        /**
         * \brief Анализирует аргументы командной строки и заполняет значения аргументов.
         * \param args Аргументы командной строки.
         * \return True, если синтаксический анализ прошел успешно, false в противном случае.
         */
        bool Parse(std::vector<std::string>& args);

        /**
         * \brief Анализирует аргументы командной строки и заполняет значения аргументов.
         * \param argc Аргумент командной строки.
         * \param argv Аргумент командной строки.
         * \return True, если синтаксический анализ прошел успешно, false в противном случае.
         */
        bool Parse(int argc, char** argv);

        /**
         * \brief Выводит справочное сообщение со списком доступных аргументов.
         */
        void PrintHelp() const;

        /**
         * \brief Добавляет целочисленные позиционные аргументы.
         * \param posCount Количество позиционных аргументов.
         * \return Ссылка на объект Argparser.
         */
        ArgParser& AddIntPositional(size_t posCount = 1);

        /**
         * \brief Добавляет строковые позиционные аргументы.
         * \param posCount Количество позиционных аргументов.
         * \return Ссылка на объект Argparser.
         */
        ArgParser& AddStringPositional(size_t posCount = 1);

        ArgParser& Store(std::vector<std::string>& var);
        ArgParser& Store(std::vector<int>& var);

        /**
         * \brief Извлекает строковое значение указанного аргумента.
         * \param name Имя аргумента.
         * \param index Индекс возвращаемого аргумента (для мульти-аргумента).
         * \return Строковое значение аргумента.
         */
        std::string GetStringValue(const std::string& name, const int index = 0) const;

        /**
         * \brief Извлекает целочисленное значение указанного аргумента.
         * \param name Имя аргумента.
         * \param index Индекс возвращаемого аргумента (для мульти-аргумента).
         * \return Целочисленное значение аргумента.
         */
        int GetIntValue(const std::string& name, const int index = 0) const;

        /**
         * \brief Извлекает логическое значение указанного аргумента.
         * \param name Имя аргумента.
         * \return Логическое значение аргумента.
         */
        bool GetFlag(const std::string& name) const;

        /**
         * \brief Извлекает строковый позиционный аргумент указанного индекса.
         * \param index Индекс возвращаемого аргумента.
         * \return Строковое значение позиционного аргумента.
         */
        std::string GetStringPositional(const int index) const;

        /**
         * \brief Извлекает целочисленный позиционный аргумент указанного индекса.
         * \param index Индекс возвращаемого аргумента.
         * \return Целочисленное значение позиционного аргумента.
         */
        int GetIntPositional(const int index) const;

        /**
         * \brief Возвращает количество позиционных аргументов.
         * \return Количество позиционных аргументов.
         */
        size_t GetPositionalCount() const;

        /**
         * \brief Возвращает количество значений аргумента.
         * \param name Имя аргумента.
         * \return Количество значений аргумента.
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
