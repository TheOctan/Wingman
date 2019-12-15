#include "ScrollBar.hpp"
#include <iostream>

namespace gui
{
	ScrollBar::ScrollBar() : ScrollBar("")
	{
		
	}

	ScrollBar::ScrollBar(const sf::String& str, int min, int max, int step)
	:	Widget	(WidgetSize::Wide),
		value	(min*step),
		minValue(min),
		maxValue(max),
		step	(step)
	{
		m_bar.setSize(sf::Vector2f(16, 40));
		m_bar.setFillColor(sf::Color(255, 255, 255, 150));
		m_bar.setOutlineColor(sf::Color::Black);
		m_bar.setOutlineThickness(outlineThickness);

		setText(str);
	}

	void ScrollBar::setText(const sf::String & str)
	{
		m_message = str + " ";
		updateText();
	}

	void ScrollBar::setTexture(const sf::Texture& texture)
	{
		reset();
		
		m_bar.setTexture(&texture);
		m_rect.setTexture(&texture);
		m_rect.setTextureRect(sf::IntRect(16, 0, 200, 20));

		updateState();
	}

	void ScrollBar::setValue(int value)
	{
		if (value >= minValue && value <= maxValue)
			this->value = value;
	}

	int ScrollBar::getValue()
	{
		return value;
	}

	void ScrollBar::drawResource(sf::RenderTarget & target, sf::RenderStates states) const
	{
		target.draw(m_bar, states);
	}

	void ScrollBar::mouseMoved(sf::Event e)
	{
		Widget::mouseMoved(e);

		if (isEntered)
		{
			state = WidgetState::selected;
		}
		else
		{
			if (!isClicked)
				state = WidgetState::active;
		}
	}

	void ScrollBar::mouseButtonPressed(sf::Event e)
	{
		if (e.mouseButton.button == sf::Mouse::Left)
		{
			if (isEntered)
			{
				isClicked = true;
			}
		}
	}

	void ScrollBar::mouseButtonReleased(sf::Event e)
	{
		if (e.mouseButton.button == sf::Mouse::Left)
		{
			if (isClicked)
			{
				if (isEntered)
				{
					state = WidgetState::selected;
				}

				event(this, WidgetEvent("", value, isActive));
			}

			isClicked = false;
		}
	}

	void ScrollBar::reset()
	{
		m_bar.setFillColor(sf::Color::White);
		m_rect.setFillColor(sf::Color::White);
	}

	void ScrollBar::updateText()
	{
		m_text.setString(m_message + std::to_string(value) + "/" + std::to_string(maxValue * step));

		m_text.setOrigin(m_text.getGlobalBounds().width / 2.f,
						 m_text.getGlobalBounds().height / 2.f);

		m_text.setPosition(m_rect.getGlobalBounds().width / 2.0f,
						   m_rect.getGlobalBounds().height / 2.5f);
	}

	void ScrollBar::updateState()
	{
		Widget::updateState();

		updateBar();
		updateText();
	}

	void ScrollBar::updateBar()
	{
		float length = m_rect.getGlobalBounds().width - m_bar.getGlobalBounds().width;
		float range = float(maxValue - minValue);

		if (isClicked)
		{
			m_bar.setPosition(localMousePos.x - m_bar.getGlobalBounds().width / 2, 0);

			if (m_bar.getPosition().x < 0)
			{
				m_bar.setPosition(0, 0);
			}
			else if (m_bar.getPosition().x + m_bar.getGlobalBounds().width > m_rect.getGlobalBounds().width)
			{
				m_bar.setPosition(m_rect.getGlobalBounds().width - m_bar.getGlobalBounds().width, 0);
			}

			float offset = length / range;
			value = (int((m_bar.getPosition().x + offset / 2.f) * range / length) + minValue) * step;
		}
		else
		{
			m_bar.setPosition((value / step - minValue) * length / range, 0);
		}
	}

	void ScrollBar::activeState()
	{
		if (m_bar.getTexture() != nullptr)
			m_bar.setTextureRect(sf::IntRect(0, 0, 8, 20));
		else
			m_bar.setFillColor(sf::Color(255, 255, 255, 150));

		m_text.setFillColor(sf::Color::White);
	}

	void ScrollBar::selectedState()
	{
		if (m_bar.getTexture() != nullptr)
			m_bar.setTextureRect(sf::IntRect(8, 0, 8, 20));
		else
			m_bar.setFillColor(sf::Color(45, 107, 236));

		m_text.setFillColor(sf::Color(255, 255, 130));
	}
}
