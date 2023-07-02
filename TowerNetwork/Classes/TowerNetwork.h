#pragma once

#include <map>

namespace std {

}

namespace ntw {

	class Tower;

	class TowerNetwork
	{
	public:
		TowerNetwork();
		~TowerNetwork() = default;

	private:
		//int CurrentTowers = 0;
		static int NextTowerNumber;

		std::map<int, Tower*> Towers;

	public:
		Tower* CreateTower();
		Tower* GetTowerByNumber(int nTower);
		Tower* GetTower(int n);

		void ConnectTowers(int nSender, int nListener);

	};

}

