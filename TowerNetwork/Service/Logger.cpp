#include "Logger.h"

#include <ostream>
#include <sstream>

#include "Signal.h"

using namespace ntw::serv;

std::ostream* Logger::outStream = nullptr;

Logger& Logger::log()
{
	return *this;
}

void Logger::logPrint(const std::string& str, int towNum)
{
	if (!outStream) return;

	if (towNum >= 0) (*outStream) << "Tower " << towNum << ": ";
	(*outStream) << str << std::endl;
}

void Logger::logPrint(const Signal& signal, int towNum)
{
	if (!outStream) return;

	(*outStream) << "Tower " << towNum << " recieve " << signal << std::endl;
}

void Logger::logError(const std::string& msg, int towNum)
{
	if (!outStream) return;

	if (towNum >= 0) (*outStream) << "Tower " << towNum << ": ";
	(*outStream) << "Error! " << msg << std::endl;
}

void Logger::setOutStream(std::ostream& stream)
{
	outStream = &stream;
}

void Logger::resetOutStream()
{
	outStream = nullptr;
}
