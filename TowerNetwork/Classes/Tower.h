#pragma once

/// @file Tower.h
/// @brief Файл с классом башни

#include "TowerNode.h"
#include "Logger.h"

/**
 * @brief Пространство имен проекта
 * @details Содержит всё, что касается проекта
*/
namespace ntw
{
    class Signal;

    /**
     * @brief Башня
     * @details Эммитер сообщения. Объект рассылает сообщение своим
     * подписчикам или принимает сообщение и "реагирует" на него.
     * 
     * Для упрощения восприятия каждая башния имеет свой номер.
    */
    class Tower : 
        protected serv::Logger, 
        public abstr::TowerNode
    {
    public:
        /// @brief Конструктор башни
        /// @param number Уникальный номер башни
        Tower(int number);

        ~Tower() = default;

    private:
        int TowerNumber; ///< Уникальный номер в сети

        /// @brief Должна ли башня давать ответ
        bool IsNeedSendAnswer = false;

        /// @brief Ответная информация
        int AnswerData = -1;

        //void init()

        /// @brief Служебный метод рассылки подписчикам
        /// @param signal Рассылаемый сигнал
        void sendToListeners(const Signal& signal);

    protected:

    public:
        /// @brief Получить номер башни
        /// @return Уникальный номер башни
        int getTowerNumber() const noexcept;

        /**
         * @name Ответ на сигнал
         * @brief Группировка методов для работы с ответной реакцией на
         * полученный сигнал
         * @{ 
        */
        /// @brief Метод получения наличия ответа
        /// @return Есть ответ или нет
        bool isHaveAnswer() const noexcept;

        /// @brief Метод получения ответа
        /// @details Информация помещается в ответный сигнал
        /// @return Ответная информация
        int getAnswer() const noexcept;

        /// @brief Метод установки ответа
        /// @param tAns Что будет передаваться в ответе
        void setAnswer(int tAns) noexcept;
        /** @} */


        /**
         * @name Соединения
         * @brief Группировка методов для установки соединения.
         * @details Отвечают за соединение текущей башни с выбранной,
         * управление подсоединенными башнаями.
         * @{
        */
        /// @brief Соеденить с
        /// @param pTower Башня, с которой соединяем
        void ConnectWith(Tower* pTower);
        
        /// @brief Метод для установления двусторонней связи с целевой башней
        /// @param pTower Башня, с которой соединяем
        void ConnectTwoWayWith(Tower* pTower);
        /** @} */


        /**
         * @name Отправка
         * @brief Методы для отправки/получения сигналов
         * @{
        */
        /// @brief Метод отправки сигнала
        /// @param data Отправляемая информация в сигнале
        /// @param resend Флаг о том, что сигнал нужно переслать своим подписчикам
        void Send(int data, bool resend = false);

        /// @brief Метод получения сигнала
        /// @param signal Сигнал :)
        void Recieve(const Signal& signal);

        //void SendToConnected(const Signal& signal, int nListener);
        /** @} */

    };

    /// @brief Метод для соединения башен (внешний)
    /// @param pTow1 Башня - источник
    /// @param pTow2 Башня - слушатель
    /// @param twoWayCommun Флаг о построении двусторонней связи
    void ConnectTowers(Tower* pTow1, Tower* pTow2, bool twoWayCommun = false);

}




