#pragma once

#include "Signal.h"
#include "Tower.h"
#include "TowerNetwork.h"
#include "Command.h"

namespace ntw {

	class App
	{
	public:
		~App();

	private:
		
	private:
		TowerNetwork* network;
		Tower* pCurrentSelection = nullptr;
		int curTower = -1;

		bool init();

		IntCom inputComand();		
		void completeCommand(IntCom& com);

	public:
		int Run();

	};

}



