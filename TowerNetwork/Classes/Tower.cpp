#include "Tower.h"

//#include <sstream>
#include <string>
#include "Signal.h"

ntw::Tower::Tower(int number) : 
	abstr::TowerNode(),
	TowerNumber(number)
{
	log() << "Created Default tower " << int(this) << " num " << TowerNumber << "\n";
}

ntw::Tower::Tower(int number, TowerSize towerSize) :
    abstr::TowerNode(towerSize),
    TowerNumber(number)
{
    log() << "Created "<< to_char(towerSize) <<" tower " << int(this) << " num " << TowerNumber << "\n";
}

//ntw::Tower::~Tower()
//{
//	delete Listeners;
//}

void ntw::Tower::sendToListeners(const Signal& signal)
{
	Tower* pTower;
	for (Iterator it = Begin(); it != End(); ++it) {
		pTower = static_cast<Tower*>(*it);
		pTower->Recieve(signal);
	}
}

int ntw::Tower::getTowerNumber() const noexcept
{
    return TowerNumber;
}

ntw::TowerSize ntw::Tower::getTowerSize() const noexcept
{
    return ConnMaxCount;
}

bool ntw::Tower::isHaveAnswer() const noexcept
{
    return IsNeedSendAnswer;
}

int ntw::Tower::getAnswer() const noexcept
{
    return AnswerData;
}

void ntw::Tower::setAnswer(int tAns) noexcept
{
    IsNeedSendAnswer = true;
    AnswerData = tAns;
}

void ntw::Tower::ConnectWith(Tower* pTower)
{
    std::string message;
    int error = addConnect(pTower);
    switch (error)
    {
    case 1:
        message = "Cannot self-connect";
        break;

    case 2:
        message = 
            "Cannot connect with already connected tower " 
            + std::to_string(pTower->getTowerNumber());
        break;
    
    case 0:
        message = "Connected with "
            + std::to_string(pTower->getTowerNumber());
        break;

    case 4:
        message = "Connection slots is full, cannot connect";
        break;

    default:
        message = "Not register error catched";
        break;
    }

    if(error)
        logError(message, TowerNumber);
    else
        logPrint(message, TowerNumber);

}

//ntw::Tower* ntw::Tower::getConnected(int numConnected) const
//{
//    return Listeners[numConnected];
//}

void ntw::Tower::ConnectTwoWayWith(Tower* pTower)
{
    std::string message;
    int error1, error2;

    error1 = addConnect(pTower);

    if(!error1) {
        error2 = pTower->addConnect(this);

		switch (error2)
		{
		case 2:
			message =
				"Tower " + std::to_string(pTower->getTowerNumber())
				+" already connected with "
				+ "Tower " + std::to_string(TowerNumber);
			break;

        case 4:
            message =
                "Tower " + std::to_string(pTower->getTowerNumber())
                + " reached connection limit";
            removeLastConnect();
			break;

		default:
			break;
		}
    }
    else {
        switch (error1)
        {
        case 1:
            message = "Cannot self-connect";
            break;

        case 2:
			message = 
				"Tower " + std::to_string(TowerNumber)
				+ " already connected with "
				+ "Tower " + std::to_string(pTower->getTowerNumber());
            break;

        case 4:
            message =
                "On Tower " + std::to_string(TowerNumber)
                + " reached connection limit";
            break;
        
        default:
            break;
        }
    }

    if(error1 || error2)
        logError(message);
    else {
		message =
			"Sucssesful two-way connect towers "
			+ std::to_string(TowerNumber)
			+ " and "
			+ std::to_string(pTower->getTowerNumber());
        logPrint(message);
    }
}

void ntw::Tower::DisconnectWith(Tower* pTower)
{
    std::string message;
    int error = removeConnect(pTower);

    switch (error)
    {
    case 0:
        message = "Disconnected with " +
            std::to_string(pTower->getTowerNumber());
        break;

    case 3:
        message = "Connection is not defined";
        break;

    default:
        break;
    }

    if (error)
        logError(message, TowerNumber);
    else
        logPrint(message, TowerNumber);
}

void ntw::Tower::DisconnectOn(int connectNumber)
{
    std::string message;
    int error = removeConnect(connectNumber);

    switch (error)
    {
    case 0:
        message = "Connection " +
            std::to_string(connectNumber) +
            " was removed. Numbering updated";
        break;

    case 3:
        message = "Connection is not defined";
        break;

    default:
        break;
    }

    if (error)
        logError(message, TowerNumber);
    else
        logPrint(message, TowerNumber);
}

void ntw::Tower::Send(int data, bool resend)
{
    Signal sig(this, data);
    if (resend) sig.Type = SignalType::Resend;
    sendToListeners(sig);
}

void ntw::Tower::SendBy(int data, int numConnection, bool resend)
{
    //std::string errorMessage = "";

    if (numConnection < 0 || numConnection >= getConnectedCount()) {
        logError("Connection is not exists", TowerNumber);
        return;
    }

    Tower* pReciver = static_cast<Tower*>(getAt(numConnection));
    Signal sig(this, data);
    if (resend) sig.Type = SignalType::Resend;
    pReciver->Recieve(sig);

}

void ntw::Tower::Recieve(const Signal& signal)
{
	logPrint(signal, TowerNumber);

    if (signal.Sender && IsNeedSendAnswer && signal.Type != SignalType::Answer) {
        Signal answer(SignalType::Answer, this, AnswerData);
        signal.Sender->Recieve(answer);
    }

    if (signal.Type == SignalType::Resend) {
        Signal sigToListeners = signal;
        sigToListeners.Sender = this;
        sendToListeners(sigToListeners);
        Signal answer(SignalType::Answer, this, getConnectedCount());
        signal.Sender->Recieve(answer);
    }
}

void ntw::ConnectTowers(Tower* pTow1, Tower* pTow2, bool twoWayCommun)
{
	if (!twoWayCommun) {
		pTow1->ConnectWith(pTow2);
	}
	else {
		pTow1->ConnectTwoWayWith(pTow2);
	}
}

