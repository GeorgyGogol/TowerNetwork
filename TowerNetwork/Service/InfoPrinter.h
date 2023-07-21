#pragma once

/// @file StructPrinter.h
/// @brief Файл с классом, отвечающим за вывод связей

#include <string>

/// @brief Пространство имен проекта
namespace ntw {

    class Tower;

    /// @brief Сервисное пространство
    namespace serv {

        class InfoPrinter
        {
        public:
            /// @brief Метод вывода подробной информации
            /// @param pTower Башня, о которой выводится информация
            /// @return Строка с подробной инфой о башне
            static std::string InfoAbout(Tower* pTower);
        };

    }

}
