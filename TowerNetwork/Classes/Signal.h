#pragma once

/// @file Signal.h
/// @brief Файл включения класса сигнала

#include <iosfwd>

/// @brief Пространство имен проекта
namespace ntw {

    class Tower;

    /** 
     * @enum Тип сигнала
     * @details Рассылаемые сигналы различаются по типам.
    */
    enum class SignalType : unsigned short 
    {
        Default,	///< Простой сигнал
        Answer,		///< Сигнал ответа
        Resend		///< Сигнал, который необходимо переслать своим подписщикам
    };

    /**
     * @brief Сообщение
     * @details Класс, изначально структура, а до этого куча 
     * принимаемых агрументов в методе. Отражает посылаемое или
     * принимаемое сообщение, содержит информацию, которая 
     * передается.
     * 
     * Минимальный набор:
     * - Тип сигнала
     * - Кто отправил (не обязательный)
     * - Что отправлено (не обязательный)
     * 
     * @todo Перемещающий конструктор
     * @todo Копирующий конструктор
    */
    class Signal
    {
    public:
        /// @brief Базовый конструктор "пустого" сигнала
        Signal();

        /// @brief Конструктор с минимальным набором
        /// @param type Тип сообщения
        /// @param sender Кто отправляет
        /// @param data Что отправляет
        Signal(SignalType type, Tower* sender, int data);

        /// @brief Конструктор обычного сообщения с информацией
        /// @param sender Кто отправляет
        /// @param data Что отправляет
        Signal(Tower* sender, int data);

        //Signal(Signal&&);

    private:
        /// @brief Есть ли у сигнала информационная нагрузка
        bool IsHaveData = false;

        /// @brief Передаваемое сообщение
        int Data;

    public:
        /// @brief Тип передаваемого сообщения
        SignalType Type = SignalType::Default;

        /// @brief Источник (кто отправил)
        Tower* Sender;

        /// @brief Метод для проверки пустоты
        /// @return Имеется ли сообщение в сигнале
        bool isHaveData() const noexcept;

        /// @brief Метод получения сообщения
        /// @return Передаваемая информация
        int getData() const noexcept;

        /// @brief Метод установки передоваемое сообщение
        /// @details Дополнительно устанавливает флаг, что внутри
        // сигнала имеется информация
        /// @param data Передаваемое сообщение
        void setData(int data) noexcept;

    };

}

/**
 * @brief Функция вывода сообщения в поток
 * @details Генерирует строку сигнала и помещает его в выходной поток.
 * С помощью этого происходит логирование
 * @param outStream Поток вывода
 * @param signal Выводимый сигнал
*/
std::ostream& operator<<(std::ostream& outStream, const ntw::Signal& signal);

