#include "StructPrinter.h"

#include "Tower.h"

using namespace ntw::serv;

std::string StructPrinter::SubStructure(Tower* pNode, int step, int nSub)
{
    std::string out = "";

    for (int i = 0; i < step * 2; ++i) out += " ";
    /// @todo Вывод типа связи
    if (nSub) out += std::to_string(nSub) + ":";

    out += " Tower:" + std::to_string(int(pNode));
    out += " Num:" + std::to_string(pNode->getTowerNumber());

    if (isPrinted(pNode)) {
        out += " (printed)\n";
        return out;
    }

    if (pNode->isHaveAnswer())
        out += " Ans:" + std::to_string(pNode->getAnswer());

    int nSubs = pNode->getConnectedCount();
    if (nSubs)
        out += " SubsCnt:" + std::to_string(nSubs);

    out += "\n";
    AlreadyPrinted.insert(pNode);

    for (int i = 0; i < nSubs; ++i) {
        out += SubStructure(static_cast<Tower*>(pNode->getAt(i)), step + 1, i + 1);
    }

    return out;
}

std::string StructPrinter::SubStructure(Tower* pNode)
{
    StructPrinter sp;
    return sp.SubStructure(pNode, 0, 0);
}
