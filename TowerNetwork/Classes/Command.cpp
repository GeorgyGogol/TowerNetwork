#include "Command.h"

#include <stdexcept>

template<typename TyValue>
ntw::Command<TyValue>::Command()
{
}

template<typename TyValue>
ntw::Command<TyValue>::Command(int nAgruments) :
	NArgs(nAgruments),
	VArg(new TyValue[nAgruments])
{
}

template<typename TyValue>
ntw::Command<TyValue>::Command(ComandType type, TyValue arg) :
	Type(type),
	Arg(arg)
{
}

template<typename TyValue>
ntw::Command<TyValue>::Command(const Command& src) :
	Command(src.Type, src.Arg)
{
	NArgs = src.NArgs;
	VArg = new int[NArgs];
	for (int i = 0; i < NArgs; ++i)
		VArg[i] = src.VArg[i];
}

template<typename TyValue>
ntw::Command<TyValue>::Command(Command&& from) noexcept :
	Command(from.Type, from.Arg)
{
	NArgs = from.NArgs;
	VArg = from.VArg;

	from.NArgs = 0;
	from.VArg = nullptr;
}

template<typename TyValue>
ntw::Command<TyValue>::~Command() noexcept
{
	if (VArg) {
		delete[] VArg;
		VArg = nullptr;
	}
}

template<typename TyValue>
ntw::Command<TyValue>& ntw::Command<TyValue>::operator=(const Command& src)
{
	if (this != &src) {
		if (VArg) {
			delete[] VArg;
			VArg = nullptr;
		}

		Type = src.Type;
		Arg = src.Arg;
		NArgs = src.NArgs;
		VArg = new int[NArgs];
		for (int i = 0; i < NArgs; ++i)
			VArg[i] = src.VArg[i];
	}
	return *this;
}

template<typename TyValue>
ntw::Command<TyValue>& ntw::Command<TyValue>::operator=(Command&& src) noexcept
{
	if (this != &src) {
		if (VArg) delete[] VArg;

		Type = src.Type;
		Arg = src.Arg;
		NArgs = src.NArgs;
		VArg = src.VArg;

		src.NArgs = 0;
		src.VArg = nullptr;
	}
	return *this;
}

template<typename TyValue>
TyValue& ntw::Command<TyValue>::operator[](int index)
{
	if (!NArgs && index == 0) {
		return Arg;
	}
	//else throw std::invalid_argument("Command have only one argument");

	if (index < 0 || index >= NArgs) throw std::out_of_range("command index");

	return VArg[index];
}

template<typename TyValue>
void ntw::Command<TyValue>::setArgCount(int nAgruments)
{
	if (VArg) {
		if (nAgruments <= NArgs) NArgs = nAgruments;
		else throw std::bad_array_new_length();
	}
	else {
		VArg = new TyValue[nAgruments];
		NArgs = nAgruments;
	}
}

template<typename TyValue>
int ntw::Command<TyValue>::getArgCount() const
{
	if (VArg) return NArgs;
	return 1;
}

template class ntw::Command<int>;

