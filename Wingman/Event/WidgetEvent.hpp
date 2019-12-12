#pragma once

#ifndef __WIDGETEVENT_HPP__
#define __WIDGETEVENT_HPP__

struct WidgetEvent
{
	WidgetEvent() : WidgetEvent("", 0, false)
	{
	}

	WidgetEvent(const sf::String& message, int value, bool isActive)
	:	message(message),
		value(value),
		isActive(isActive)
	{
	}

	sf::String message;
	int value;
	bool isActive;
};

#endif // !__WIDGETEVENT_HPP__
