#include "Tower.h"

#include <sstream>

#include "Signal.h"

//bool ntw::Tower::isOutStreamSetted = false;
std::ostream* ntw::Tower::outStream = nullptr;

ntw::Tower::Tower(int number) :
	TowerNumber(number)
{
	//Listeners = new std::vector<Tower*>;
	if (outStream)
		(*outStream) << "Created tower " << int(this) << " num " << TowerNumber << std::endl;
}

//ntw::Tower::~Tower()
//{
//	delete Listeners;
//}

void ntw::Tower::sendToListeners(const Signal& signal)
{
	for (auto each : Listeners) {
		each->Recieve(signal);
	}
}

int ntw::Tower::getTowerNumber() const noexcept
{
	return TowerNumber;
}

bool ntw::Tower::isHaveAnswer() const noexcept
{
	return IsNeedSendAnswer;
}

int ntw::Tower::getAnswer() const noexcept
{
	return TypeAnswer;
}

void ntw::Tower::printLog(const std::string& str)
{
	if (!outStream) return;

	(*outStream) << "Tower " << TowerNumber << " " << str << std::endl;
}

void ntw::Tower::setAnswer(int tAns) noexcept
{
	IsNeedSendAnswer = true;
	TypeAnswer = tAns;
}

void ntw::Tower::ConnectWith(Tower* pTower)
{
	if (pTower == this) {
		printLog("cannot self-connect");
		return;
	}
	Listeners.push_back(pTower);
	std::stringstream ss;
	ss << "connected with Tower " << pTower->getTowerNumber();
	printLog(ss.str());
}

int ntw::Tower::getConnectedCount() const noexcept
{
	return Listeners.size();
}

ntw::Tower* ntw::Tower::getConnected(int numConnected) const
{
	return Listeners[numConnected];
}

void ntw::Tower::Send(int data, bool resend)
{
	Signal sig(this, data);
	if (resend) sig.Type = SignalType::Resend;
	sendToListeners(sig);
}

void ntw::Tower::Recieve(const Signal& signal)
{
	std::stringstream ss;
	ss << "recive " << signal;
	printLog(ss.str());

	if (signal.Sender && IsNeedSendAnswer && signal.Type != SignalType::Answer) {
		Signal answer(SignalType::Answer, this, TypeAnswer);
		signal.Sender->Recieve(answer);
	}

	if (signal.Type == SignalType::Resend) {
		sendToListeners(signal);
		Signal answer(SignalType::Answer, this, Listeners.size());
		signal.Sender->Recieve(answer);
	}
}

void ntw::Tower::setOutStream(std::ostream& stream)
{
	//isOutStreamSetted = true;
	outStream = &stream;
}

std::string ntw::SubStructure(const Tower* pNode, int step)
{
	std::stringstream ss;

	for (int i = 0; i < step; ++i) ss << "\t";
	ss << "Tower:" << int(pNode) << " num:" << pNode->getTowerNumber();
	if (pNode->isHaveAnswer()) ss << " ans:" << pNode->getAnswer();

	int nSubs = pNode->getConnectedCount();
	if (nSubs) {
		ss << " subs:" << nSubs;
	}

	ss << '\n';

	if (nSubs) {
		for (int i = 0; i < nSubs; ++i) {
			ss << SubStructure(pNode->getConnected(i), step + 1);
		}
	}

	return ss.str();
}
