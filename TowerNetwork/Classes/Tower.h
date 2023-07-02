#pragma once

#include <string>
#include <vector>
#include <iosfwd>

namespace ntw
{
	class Signal;

	class Tower
	{
	public:
		Tower(int number);
		~Tower() = default;

	private:
		int TowerNumber;

		bool IsNeedSendAnswer = false;
		int TypeAnswer = -1;

		std::vector<Tower*> Listeners;

		static std::ostream* outStream;
		//static bool isOutStreamSetted;

		//void init()
		void sendToListeners(const Signal& signal);

		void printLog(const std::string& str);

	public:
		int getTowerNumber() const noexcept;

		bool isHaveAnswer() const noexcept;
		int getAnswer() const noexcept;
		void setAnswer(int tAns) noexcept;

		//void send(int data) noexcept;

		void ConnectWith(Tower* pTower);
		int getConnectedCount() const noexcept;
		Tower* getConnected(int numConnected) const;

		void Send(int data, bool resend = false);
		//void SendToConnected(const Signal& signal, int nListener);
		void Recieve(const Signal& signal);

		static void setOutStream(std::ostream& stream);
		static void resetOutStream();

	};

	std::string SubStructure(const Tower* pNode, int step = 0);

	//void Connect(Tower )

}



