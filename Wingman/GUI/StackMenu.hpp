#pragma once

#ifndef __STACKMENU_HPP__
#define __STACKMENU_HPP__

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

#include "Widget.hpp"

namespace gui
{
	//Texture -> getSize
	//Sprite -> getGloabalBounds
	//RectangleShape -> getSize, getGloabalBounds

	class StackMenu : public sf::Drawable, public sf::Transformable, sf::NonCopyable
	{
	public:
		StackMenu();
		~StackMenu();

		void addWidget(Widget* widget, bool rightSide = false);
		
		void setTitle	(const sf::String& title);
		void setTexture	(const sf::Texture& texture);
		void setFont	(const sf::Font& font);

		const sf::Vector2f& getSize()		const;

		void handleEvent(sf::Event e);

		Widget& operator[] (size_t i)
		{
			return *m_widgets.at(i);
		}
		const Widget& operator[] (size_t i) const
		{
			return *m_widgets.at(i);
		}

	protected:
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	private:
		void initWidget(Widget* widget, bool rightSide);
		void updateText();
		void reset();

		std::vector<Widget*>	m_widgets;
		sf::RectangleShape		m_background;

		sf::Vector2f m_basePosition;
		sf::Vector2f m_nextPosition;
		sf::Vector2f m_baseSize;		
		sf::Text m_titleText;

		sf::RectangleShape rect[4];

		float interval;
		float offset;
		float smallWidth;
	};

} // namespace gui

#endif // !__STACKMENU_HPP__
