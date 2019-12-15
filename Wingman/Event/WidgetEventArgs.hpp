#pragma once

#ifndef __WIDGETEVENTARGS_HPP__
#define __WIDGETEVENTARGS_HPP__

#include<SFML/System/String.hpp>
#include"EventArgs.hpp"
#include"WidgetEvent.hpp"

class WidgetEventArgs : public EventArgs
{
public:
	WidgetEventArgs(const WidgetEvent& e)
	:	message	(e.message),
		value	(e.value),
		isActive(e.isActive)
	{
	}

	sf::String message;
	int value;
	bool isActive;
};

#endif // !__WIDGETEVENTARGS_HPP__
