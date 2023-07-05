#pragma once

/// @file StructPrinter.h
/// @brief Файл с классом, отвечающим за вывод связей
/// @todo Убрать зависимость от include string

#include <set>
#include <string>

/// @brief Пространство имен проекта
namespace ntw {

    class Tower;

    /// @brief Сервисное пространство
    namespace serv {
    
        /**
         * @brief Класс для построения и вывода информации о структуре
         * связей определенной башни.
        */
        class StructPrinter
        {

        private:
            /// @brief Множество, информацию о чем мы вывели
            /// @details Необходимо для понимания раскрытия связей, чтобы не уходило
            /// в бесконечный рекурсивный вызов для 0 - 1 - 0
            std::set<Tower*> AlreadyPrinted;

            /// @brief Метод проверки вывода
            /// @details Проверяет, вывели ли мы информацию о башне или нет
            /// @param pNode Башня
            /// @return Был вывод или нет
            inline bool isPrinted(Tower* pNode) 
            {
                return AlreadyPrinted.find(pNode) != AlreadyPrinted.end();
            }

            /// @brief Рекурсивный метод построения связей для консоли
            /// @param pNode Верхний узел, чью сеть мы просматриваем
            /// @param step Уровень
            /// @param nSub Номер в списке связей
            /// @note Передача Уровня или номера равного нулю означает
            /// отсутствие аргумнта
            /// @return Строка с информацией об узле 
            std::string SubStructure(Tower* pNode, int step, int nSub);

        public:
            /// @brief Внешний метод для вывода структуры
            /// @details Собирает строку для вывода в консоль
            /// @param pNode Просматриваемая башня
            /// @return Строка с информацией о структуре
            static std::string SubStructure(Tower* pNode);

        };
    }
}

