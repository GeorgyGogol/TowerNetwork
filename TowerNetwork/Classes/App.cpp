#include "App.h"

#include <iostream>
#include "Logger.h"
#include "StructPrinter.h"
#include "TowerSize.h"
#include "InfoPrinter.h"

/// @brief Метод преобразования буквы в размер
/// @param letter Буква
/// @return Размер
ntw::TowerSize decideTowerSize(char letter);

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
			out.Type = CommandType::SetTower;
			cin >> out.Arg;
		}
		else if (buf == "answer" || buf == "ans") {
			out.Type = CommandType::SetAnswer;
			out.setArgCount(2);
			out[0] = curTower;
			cin >> out[1];
		}
	}
	else if (buf == "send")
	{
		out.Type = CommandType::SendToAll;
		out.setArgCount(3, 0);

        cin>>buf;

        if (buf == "subs") {
            out[-1] = 1;
            cin >> out[0];
        }
        else {
            out[0] = atoi(buf.c_str());
        }

        if (cin.peek() != '\n') {
            cin >> buf;
            if (buf == "by") {
                out.Type = CommandType::SendBy;
                cin >> out[1];
            }
        }
	}
	else if (buf.find("connect") != std::string::npos)
	{
        if (buf.substr(0, 3) == "dis")
            out.Type = CommandType::Disconnect;
        else
		    out.Type = CommandType::Connect;

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
		out.Type = CommandType::Create;
        out.setArgCount(2, 1);
        
        int nArg = 0;
        while (cin.peek() != '\n') {
            cin >> buf;

            if (isdigit(buf[0])) {
                out[0] = atoi(buf.c_str());
            }
            else {
                out[1] = int(buf[0]);
            }

            nArg++;
        }

        if (!nArg) {
            out.Arg = -1;
        }
	}
	else if (buf == "print")
	{
		cin >> buf;

		if (buf == "network") {
			out.Type = CommandType::PrintNetwork;
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
        else if (buf == "info") {
            out.Type = CommandType::PrintInfo;
            if (cin.peek() != '\n') {
                cin >> out.Arg;
            }
            else if (pCurrentSelection) {
                out.Arg = curTower;
            }
            else {
                out.Type = CommandType::InptError;
            }
        }
	}
	else if (buf == "exit") {
		out.Type = CommandType::Exit;
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
		case CommandType::SetTower:
			pCurrentSelection = network->GetTowerByNumber(com[0]);
			curTower = com[0];
			break;

		case CommandType::SetAnswer:
			network->GetTowerByNumber(com[0])->setAnswer(com[1]);
			break;

		case CommandType::SendToAll:
			pCurrentSelection->Send(com[0], bool(com[-1]));
			break;

		case CommandType::SendBy:
            pCurrentSelection->SendBy(com[0], com[1], bool(com[-1]));
			break;

		case CommandType::Connect:
			network->ConnectTowers(com[0], com[1]);
			break;

		case CommandType::Create:
            if (com.Arg == -1) {
                network->CreateTower();
            }
            else {
                for (int i = 0; i < com[0]; ++i) {
                    network->CreateTower(decideTowerSize(com[1]));
                }
            }
			break;

		case CommandType::PrintNetwork:
			std::cout << "Network Tower " << com.Arg << std::endl;
			std::cout << serv::StructPrinter::SubStructure(network->GetTowerByNumber(com.Arg)) << std::endl;
			break;

        case CommandType::PrintInfo:
            std::cout << "Information about Tower " << com.Arg << std::endl;
            std::cout << serv::InfoPrinter::InfoAbout(network->GetTowerByNumber(com.Arg)) << std::endl;
            break;

		case CommandType::Exit:
			break;

		case CommandType::NoComand:
			break;

        case CommandType::Disconnect:
            network->DisconnectTowers(com[0], com[1]);
            break;

        case CommandType::InptError:
            std::cout << "Input error" << std::endl;
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
	} while (com.Type != CommandType::Exit);

    return 0;
}

ntw::TowerSize decideTowerSize(char letter)
{
    using namespace ntw;
    TowerSize out = TowerSize::Default;

    switch (letter)
    {
    case 's':
        out = TowerSize::Small;
        break;

    case 'm':
        out = TowerSize::Medium;
        break;

    case 'b':
        out = TowerSize::Big;
        break;

    case 'l':
        out = TowerSize::Large;
        break;

    default:
        break;
    }

    return out;
}
