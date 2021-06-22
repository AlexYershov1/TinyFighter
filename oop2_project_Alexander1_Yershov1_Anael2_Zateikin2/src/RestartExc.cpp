#pragma once
#include "RestartExc.h"


RestartExc::RestartExc(bool reason) : m_exitReason(reason)
{}

RestartExc::~RestartExc()
{
}