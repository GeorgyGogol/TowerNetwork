#pragma once

/// @file TowerSize.h
/// @brief Файл с параметрами размеров башни

/// @brief Пространство имен проекта
namespace ntw {

    /// @brief Размер башни
    enum class TowerSize : unsigned short
    {
        Small = 4,          ///< Маленькая
        Medium = 6,         ///< Средняя
        Big = 8,            ///< Большая
        Large = 10,         ///< Огромная
        Default = Medium    ///< По-умолчанию (средняя)
    };

    /// @brief Метод преобразования размера в целое число
    /// @param size Размер (перечисление)
    /// @return Размер (целочисленный тип)
    int to_int(const TowerSize& size) noexcept;

    /// @brief Метод преобразования размера в строку
    /// @param size Размер (перечисление)
    /// @return Размер словом
    const char* to_char(const TowerSize& size) noexcept;

}

