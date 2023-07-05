#include "Signal.h"

#include <sstream>
#include "Tower.h"

ntw::Signal::Signal()
{
}

ntw::Signal::Signal(SignalType type, Tower* sender, int data) :
    Type(type),
    Sender(sender),
    IsHaveData(true),
    Data(data)
{
}

ntw::Signal::Signal(Tower* sender, int data) :
    Sender(sender),
    IsHaveData(true),
    Data(data)
{
}

bool ntw::Signal::isHaveData() const noexcept
{
    return IsHaveData;
}

int ntw::Signal::getData() const noexcept
{
    return Data;
}

void ntw::Signal::setData(int data) noexcept
{
    IsHaveData = true;
    Data = data;
}

std::ostream& operator<<(std::ostream& outStream, const ntw::Signal& signal)
{
    std::stringstream ss;

    switch (signal.Type)
    {
    case ntw::SignalType::Answer:
        ss << "answer";
        break;

    case ntw::SignalType::Resend:
        ss << "resended signal";
        break;

    case ntw::SignalType::Default:
    default:
        ss << "signal";
        break;
    }

    if (signal.isHaveData()) {
        ss << " " << signal.getData();
    }
    else {
        ss << " without data";
    }

    if (signal.Sender) {
        ss << " from Tower " << signal.Sender->getTowerNumber();
    }

    outStream << ss.str();

    return outStream;
}

