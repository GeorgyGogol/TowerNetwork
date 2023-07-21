#include "InfoPrinter.h"

#include "Tower.h"

std::string ntw::serv::InfoPrinter::InfoAbout(Tower* pTower)
{
    using namespace std;

    string out = "";

    out += " Tower:" + std::to_string(pTower->getTowerNumber());
    out += " Size:" + string(to_char(pTower->getTowerSize()));
    out += " Connections:" + std::to_string(pTower->getConnectedCount()) +
        "/" + std::to_string(pTower->getConnectedLimit());

    double load = round(10000.0 * pTower->getConnectedCount() / pTower->getConnectedLimit());
    out += " LoadedOn:" + std::to_string(load / 100) + "%";

    return out;
}
