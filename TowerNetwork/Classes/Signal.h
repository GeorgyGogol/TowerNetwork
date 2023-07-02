#pragma once

#include <iosfwd>

namespace ntw {

	class Tower;

	enum class SignalType : unsigned short 
	{
		Default,
		Answer,
		Resend
	};

	class Signal
	{
	public:
		Signal();
		Signal(SignalType type, Tower* sender, int data);
		Signal(Tower* sender, int data);

	private:
		bool IsHaveData = false;
		int Data;

	public:
		SignalType Type = SignalType::Default;
		Tower* Sender;

		bool isHaveData() const noexcept;
		int getData() const noexcept;
		void setData(int data) noexcept;

	};

}

std::ostream& operator<<(std::ostream& outStream, const ntw::Signal& signal);

