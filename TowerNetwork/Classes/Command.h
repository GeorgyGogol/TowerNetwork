#pragma once

/// @file Command.h
/// @brief Файл управляющих команд
/// @details Содержит информацию по управлению приложением

/// @brief Пространство имен проекта
namespace ntw {

    /// @brief Перечисление типов управляющих команд
    enum class CommandType : short
    {
        InptError = -2, ///< Ошибка ввода
        NoComand = -1,  ///< Нет команды
        Exit = 0,       ///< Выход
        SetTower,       ///< Выбрать башню
        SetAnswer,      ///< Установить ответ башни
        SendBy,         ///< Отправить по номеру соединения
        SendToAll,      ///< Отправить всем подписчикам
        Connect,        ///< Соединить башни
        Create,         ///< Создать башню(и)
        PrintNetwork,   ///< Напечатать сеть
        PrintInfo,      ///< Напечатать информацию о башне
        Disconnect      ///< Разъединить башни
    };

    /**
     * @brief Класс управляющей команды
     * @details Содержит такую важную информацию по управлению
     * приложением, как:
     * - Тип команды, т.е. что нужно сделать
     * - Аргументы команды
     * З.Ы. Через выделение памяти сделал специально. В велосипедных
     * целях изучения перемещения. Не осуждайте
     * @tparam TyValue Тип аргументов команды
    */
    template<typename TyValue>
    class Command
    {
    public:
        Command();
        Command(int nAgruments);
        Command(CommandType type, TyValue arg);
        
        Command(const Command& src);
        Command(Command&& from) noexcept;

        ~Command() noexcept;

        Command& operator=(const Command& src);
		Command& operator=(Command&& src) noexcept;

        TyValue& operator[](int index);

    private:
        TyValue* VArg = nullptr; ///< Указатель на массив агрументов
        int NArgs = 0; ///< Кол-во аргументов

    public:
        /// @brief Тип команды
        CommandType Type = CommandType::NoComand;

        /// @brief Единичный аргумент (как открытое свойство)
        TyValue Arg = 0;

        /// @brief Метод для установки кол-ва аргументов
        /// @param nAgruments Число аргументов команды
        void setArgCount(int nAgruments);

        /// @brief Метод для установки количества аргументов со значеним
        /// по-умолчанию
        /// @param nAgruments Число аргументов команды
        /// @param defValue Присваемое значение
        void setArgCount(int nAgruments, TyValue defValue);

        /// @brief Метод, возвращающий кол-во аргументов
        /// @return Число аргументов команды
        int getArgCount() const;

    };

    /// @brief Определение команды с целочисленными аргументами
    typedef Command<int> IntCom;
}

