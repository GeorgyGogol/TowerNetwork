#include "TowerSize.h"

int ntw::to_int(const TowerSize &size) noexcept
{
    return int(size);
}

const char *ntw::to_char(const TowerSize &size) noexcept
{
    switch (size)
    {
    case ntw::TowerSize::Small:
        return "Small";
    case ntw::TowerSize::Medium:
        return "Medium";
    case ntw::TowerSize::Big:
        return "Big";
    case ntw::TowerSize::Large:
        return "Large";
    default:
        return "Not defined";
    }
}
