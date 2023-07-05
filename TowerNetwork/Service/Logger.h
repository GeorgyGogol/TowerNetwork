#pragma once

/// @file Logger.h
/// @brief Файл с классом логировщика

#include <iosfwd>
#include <string>

#include <ostream>

namespace ntw {

    class Signal;

    /**
     * @brief Сервисное пространство
     * @details Содержит классы и методы, которые обеспечивают
     * корректную работу и берут ответсвтвенность за какую-либо часть
     * или зону на себя.
    */
    namespace serv {

        /**
         * @brief Логировщик
         * @details Отвечает за вывод информации в единый поток
        */
        class Logger
        {
        public:
            Logger() = default;
            ~Logger() = default;

            /// @brief Оператор вывода в общий поток логирования
            /// @tparam TyMessage Тип передаваемого сообщения в лог
            /// @param message Сообщение для логирования
            /// @return Логировщик
            template<typename TyMessage>
            Logger& operator<<(const TyMessage& message)
            {
                if (outStream) (*outStream) << message;
                return *this;
            }

        private:
            /// @brief Указатель потока логирования
            static std::ostream* outStream;

        protected:
            /// @brief Получить ссылку на логировщика
            /// @details Нужен для явной записи сообщения в лог
            /// @return Ссылка на логировщика
            Logger& log();

        public:
            /// @brief Штатный метод логирования
            /// @param str Сообщение
            /// @param towNum Номер башни, с которой связано
            void logPrint(const std::string& str, int towNum = -1);

            /// @overload
            /// @brief Метод логирования сигнала
            /// @param sig Сигнал
            /// @param towNum Башня, с которой связано
            void logPrint(const Signal& sig, int towNum);

            /// @brief Метод логирования ошибки
            /// @param msg Сообщение об ошибке
            /// @param towNum Номер башни, с которой связано 
            void logError(const std::string& msg, int towNum = -1);

            //void logPrint();

            /// @brief Метод установки выходного потока для логирования
            /// @param stream Поток, куда будет помещатся сообщения
            static void setOutStream(std::ostream& stream);

            /// @brief Метод сброса потока (отключение)
            static void resetOutStream();

        };

    }

}




