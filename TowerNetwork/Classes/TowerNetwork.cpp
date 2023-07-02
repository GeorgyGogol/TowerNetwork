#include "TowerNetwork.h"

#include "Tower.h"

int ntw::TowerNetwork::NextTowerNumber = 0;

ntw::TowerNetwork::TowerNetwork()
{
	//Towers = new std::vector<Tower*>;
}

//ntw::TowerNetwork::~TowerNetwork()
//{
//	delete Towers;
//}

ntw::Tower* ntw::TowerNetwork::CreateTower()
{
	Tower* pTow = new Tower(NextTowerNumber);
	Towers[NextTowerNumber] = pTow;
	
	NextTowerNumber++;

	return pTow;
}

ntw::Tower* ntw::TowerNetwork::GetTowerByNumber(int nTower)
{
	return Towers.at(nTower);
}

ntw::Tower* ntw::TowerNetwork::GetTower(int n)
{
	Tower* out = nullptr;
	std::map<int, Tower*>::iterator it = Towers.begin();
	for (int i = 0; i < n; ++i) ++it;

	if (it != Towers.end()) out = it->second;

	return out;
}

void ntw::TowerNetwork::ConnectTowers(int nSender, int nReciver)
{
	Tower* sen;
	Tower* rec;

	sen = Towers.at(nSender);
	rec = Towers.at(nReciver);

	sen->ConnectWith(rec);

}
