#pragma once
#include "Animation.h"





Animation::Animation()
{
}

Animation::~Animation()
{
}

Animation& Animation::instance()
{
	static Animation inst;
	return inst;
}
