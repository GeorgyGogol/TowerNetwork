#include "App.h"

#include <iostream>

ntw::App::~App()
{
	if (network) {
		delete network;
		network = nullptr;
	}
}

bool ntw::App::init()
{
	network = new TowerNetwork;
	Tower::setOutStream(std::cout);

	return true;
}

void ntw::App::completeCommand(IntCom& com)
{
	try {

		switch (com.Type)
		{
		case ComandType::SetTower:
			pCurrentSelection = network->GetTowerByNumber(com[0]);
			curTower = com[0];
			break;

		case ComandType::SetAnswer:
			network->GetTowerByNumber(com[0])->setAnswer(com[1]);
			break;

		case ComandType::SendToAll:
			pCurrentSelection->Send(com[0]);
			break;

		case ComandType::Send:
			break;

		case ComandType::Connect:
			network->ConnectTowers(com[0], com[1]);
			break;

		case ComandType::Create:
			for (int i = 0; i < com.Arg; ++i)
				network->CreateTower();
			break;

		case ComandType::PrintNetwork:
			std::cout << "Network Tower " << com.Arg << std::endl;
			std::cout << SubStructure(network->GetTowerByNumber(com.Arg)) << std::endl;
			break;

		case ComandType::NoComand:
		case ComandType::Exit:
		default:
			break;
		}
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}
}

ntw::IntCom ntw::App::inputComand()
{
	using namespace std;
	IntCom out;

	std::string buf;
	if (pCurrentSelection)
		std::cout << "Tower " << curTower <<" ";
	std::cout << "Enter command>";
	std::cin >> buf;

	if (buf == "set")
	{
		if (pCurrentSelection)
			std::cin >> buf;

		if (!pCurrentSelection || buf == "tower") {
			out.Type = ComandType::SetTower;
			std::cin >> out.Arg;
		}
		else if (buf == "answer" || buf == "ans") {
			out.Type = ComandType::SetAnswer;
			out.setArgCount(2);
			out[0] = curTower;
			std::cin >> out[1];
		}
	}
	else if (buf == "send")
	{
		out.Type = ComandType::SendToAll;
		out.setArgCount(2);

		int nArgs;
		for (nArgs = 0; nArgs < 2 && std::cin.peek() != '\n'; ++nArgs) {
			std::cin >> out[nArgs];
		}
		out.setArgCount(nArgs);
		if (nArgs > 1) out.Type = ComandType::Send;
	}
	else if (buf == "connect")
	{
		out.Type = ComandType::Connect;
		out.setArgCount(2);
		if (!pCurrentSelection) {
			std::cin >> out[0] >> out[1];
		}
		else {
			out[0] = curTower;
			std::cin >> out[1];
		}
	}
	else if (buf == "create")
	{
		out.Type = ComandType::Create;
		out.Arg = 1;
		if (std::cin.peek() != '\n') {
			cin >> out.Arg;
		}
	}
	else if (buf == "print")
	{
		std::cin >> buf;

		if (buf == "network") {
			out.Type = ComandType::PrintNetwork;
			if (std::cin.peek() != '\n') {
				cin >> out.Arg;
			}
			else if (pCurrentSelection) {
				out.Arg = curTower;
			}
			else {
				out.Arg = 0;
			}
		}
	}
	else if (buf == "exit") {
		out.Type = ComandType::Exit;
	}

	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	return out;
}

int ntw::App::Run()
{
	bool inited = init();

	if (!inited) return 1;

	network->CreateTower();

	IntCom com;

	do {
		com = inputComand();
		completeCommand(com);
	} while (com.Type != ComandType::Exit);

    return 0;
}
