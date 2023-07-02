#pragma once

namespace ntw {

	enum class ComandType : short
	{
		NoComand = -1,
		Exit = 0,
		SetTower, SetAnswer,
		Send, SendToAll,
		Connect,
		Create,
		PrintNetwork
	};

	template<typename TyValue>
	class Command
	{
	public:
		Command();
		Command(int nAgruments);
		Command(ComandType type, TyValue arg);
		
		Command(const Command& src);
		Command(Command&& from) noexcept;

		~Command();

		Command& operator=(const Command& src);
		TyValue& operator[](int index);


	private:
		TyValue* VArg = nullptr;
		int NArgs = 0;

	public:
		ComandType Type = ComandType::NoComand;
		TyValue Arg = 0;

		void setArgCount(int nAgruments);
		int getArgCount() const;
	};

	typedef Command<int> IntCom;
}

