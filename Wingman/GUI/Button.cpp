#include "Button.hpp"

#include<iostream>

namespace gui
{
	Button::Button() : Button("")
	{
		
	}

	Button::Button(const sf::String& str, WidgetSize size)
	:	Widget(size)
	{
		setText(str);
	}

	void Button::mouseMoved(sf::Event e)
	{
		Widget::mouseMoved(e);

		if (isEntered)
		{
			if (isClicked)
				state = WidgetState::notActive;
			else
				state = WidgetState::selected;
		}
		else
		{
			state = WidgetState::active;
		}
	}

	void Button::mouseButtonPressed(sf::Event e)
	{
		if (e.mouseButton.button == sf::Mouse::Left)
		{
			if (isEntered)
			{
				state = WidgetState::notActive;
				isClicked = true;
			}
		}
	}

	void Button::mouseButtonReleased(sf::Event e)
	{
		if (e.mouseButton.button == sf::Mouse::Left)
		{
			if (isEntered && isClicked)
			{
				state = WidgetState::selected;

				event(this, WidgetEvent("", 0, isActive));
			}

			isClicked = false;
		}
	}

	void Button::updateText()
	{
		m_text.setOrigin(m_text.getGlobalBounds().width / 2,
			m_text.getGlobalBounds().height / 2);

		m_text.setPosition(m_rect.getGlobalBounds().width / 2.0f,
			m_rect.getGlobalBounds().height / 2.5f);
	}

	void Button::notActiveState()
	{
		if (m_rect.getTexture() != nullptr)
			m_rect.setTextureRect(sf::IntRect(0, 0, 200, 20));
		else
			m_rect.setFillColor(sf::Color(22, 192, 82));

		m_text.setFillColor(sf::Color::White);
	}

	void Button::activeState()
	{
		if (m_rect.getTexture() != nullptr)
			m_rect.setTextureRect(sf::IntRect(0, 20, 200, 20));
		else
			m_rect.setFillColor(sf::Color(52, 152, 219));

		m_text.setFillColor(sf::Color::White);
	}

	void Button::selectedState()
	{
		if (m_rect.getTexture() != nullptr)
			m_rect.setTextureRect(sf::IntRect(0, 40, 200, 20));
		else
			m_rect.setFillColor(sf::Color(45, 107, 236));

		m_text.setFillColor(sf::Color(255, 255, 130));
	}
}
