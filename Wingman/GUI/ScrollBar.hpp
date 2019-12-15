#pragma once

#ifndef __SCROLLBAR_HPP__
#define __SCROLLBAR_HPP__

#include"Widget.hpp"

namespace gui
{
	class ScrollBar : public Widget
	{
	public:
		ScrollBar();
		ScrollBar(const sf::String& str, int min = 0, int max = 100, int step = 1);

		void setText(const sf::String& str)			override;
		void setTexture(const sf::Texture& texture)	override;
		void setValue(int value);
		int  getValue();

	private:
		void drawResource(sf::RenderTarget& target, sf::RenderStates states) const;

		void mouseMoved				(sf::Event e)	override;
		void mouseButtonPressed		(sf::Event e)	override;
		void mouseButtonReleased	(sf::Event e)	override;

		void reset		() override;
		void updateText	() override;
		void updateState() override;
		void updateBar	();

		void activeState	() override;
		void selectedState	() override;

		sf::RectangleShape  m_bar;
		sf::String			m_message;

		int value;
		int minValue;
		int maxValue;
		int step;

	};

} // namespace gui

#endif // !__SCROLLBAR_HPP__


