#include "App.h"

#include <iostream>
#include "Logger.h"
#include "StructPrinter.h"

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
	serv::Logger::setOutStream(std::cout);
	network->CreateTower();

	return true;
}

ntw::IntCom ntw::App::inputComand()
{
	using namespace std;
	IntCom out;

	string buf;
	if (pCurrentSelection)
		cout << "Tower " << curTower << " ";
	cout << "Enter command>";
	cin >> buf;

	if (buf == "set")
	{
		if (pCurrentSelection)
			cin >> buf;

		if (!pCurrentSelection || buf == "tower") {
			out.Type = ComandType::SetTower;
			cin >> out.Arg;
		}
		else if (buf == "answer" || buf == "ans") {
			out.Type = ComandType::SetAnswer;
			out.setArgCount(2);
			out[0] = curTower;
			cin >> out[1];
		}
	}
	else if (buf == "send")
	{
		out.Type = ComandType::SendToAll;
		out.setArgCount(2);

		int nArgs;
		for (nArgs = 0; nArgs < 2 && cin.peek() != '\n'; ++nArgs) {
			cin >> out[nArgs];
		}
		out.setArgCount(nArgs);
		if (nArgs > 1) out.Type = ComandType::Send;
	}
	else if (buf == "connect")
	{
		out.Type = ComandType::Connect;
		out.setArgCount(2);
		if (!pCurrentSelection) {
			cin >> out[0] >> out[1];
		}
		else {
			out[0] = curTower;
			cin >> out[1];
		}
	}
	else if (buf == "create")
	{
		out.Type = ComandType::Create;
		out.Arg = 1;
		if (cin.peek() != '\n') {
			cin >> out.Arg;
		}
	}
	else if (buf == "print")
	{
		cin >> buf;

		if (buf == "network") {
			out.Type = ComandType::PrintNetwork;
			if (cin.peek() != '\n') {
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

	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	return out;
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
			std::cout << serv::StructPrinter::SubStructure(network->GetTowerByNumber(com.Arg)) << std::endl;
			break;

		case ComandType::Exit:
			break;

		case ComandType::NoComand:
			break;

		default:
			std::cout << "Unknown command!" << std::endl;
			break;
		}
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}
}

int ntw::App::Run()
{
	bool inited = init();

	if (!inited) return 1;

	IntCom com;
	do {
		com = inputComand();
		completeCommand(com);
	} while (com.Type != ComandType::Exit);

    return 0;
}
