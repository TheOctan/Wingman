#pragma once

#ifndef __BUTTON_HPP__
#define __BUTTON_HPP__

#include"Widget.hpp"

namespace gui
{
	class Button : public Widget
	{
	public:
		Button();
		Button(const sf::String& str, WidgetSize size = WidgetSize::Wide);

	private:
		void mouseMoved				(sf::Event e)	override;
		void mouseButtonPressed		(sf::Event e)	override;
		void mouseButtonReleased	(sf::Event e)	override;

		void updateText() override;

		void notActiveState	() override;
		void activeState	() override;
		void selectedState	() override;
	};

	//inline std::unique_ptr<Button> makeButton(const sf::String& str = "", Widget::WidgetSize size = Widget::WidgetSize::Wide) { return std::make_unique<Button>(str, size); }

} // namespace gui

#endif // !__BUTTON_HPP__
