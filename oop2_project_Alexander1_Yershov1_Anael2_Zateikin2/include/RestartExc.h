#pragma once
#include <exception>
#include <stdexcept>


//Exception for end of fight
class RestartExc : public std::exception
{
public:
	RestartExc(bool);
	~RestartExc();

private:
	bool m_exitReason; // TRUE if willingly exited
};

