#include"Lock.hpp"
#include<iostream>

namespace gui
{
	Lock::Lock() : Lock("")
	{

	}

	Lock::Lock(const sf::String& str, WidgetSize size)
		: Widget(size)
	{
		m_lock.setSize(sf::Vector2f(40, 40));
		m_lock.setFillColor(sf::Color(52, 152, 219));
		m_lock.setOutlineColor(sf::Color::Black);
		m_lock.setOutlineThickness(outlineThickness);

		setText(str);
	}

	void Lock::setTexture(const sf::Texture& texture)
	{
		reset();

		m_lock.setTexture(&texture);
		m_rect.setTexture(&texture);
		m_rect.setTextureRect(sf::IntRect(0, 20 * 3, 200, 20));

		updateState();
	}

	void Lock::drawResource(sf::RenderTarget & target, sf::RenderStates states) const
	{
		target.draw(m_lock, states);
	}

	void Lock::mouseMoved(sf::Event e)
	{
		Widget::mouseMoved(e);

		if (isEntered)
		{
			state = WidgetState::selected;
		}
		else
		{
			state = WidgetState::active;
		}
	}

	void Lock::mouseButtonPressed(sf::Event e)
	{
		if (e.mouseButton.button == sf::Mouse::Left)
		{
			if (isEntered)
			{
				isLocked = isLocked ? false : true;
				event(this, WidgetEvent("", isLocked, isActive));
			}
		}
	}

	void Lock::reset()
	{
		m_lock.setFillColor(sf::Color::White);
		m_rect.setFillColor(sf::Color::White);
	}

	void Lock::updateText()
	{
		m_text.setOrigin(0, m_text.getGlobalBounds().height / 2);
		m_text.setPosition(m_lock.getGlobalBounds().width + 15, m_lock.getGlobalBounds().height / 2.5f);
	}

	void Lock::notActiveState()
	{
		if (m_lock.getTexture() != nullptr)
			m_lock.setTextureRect(sf::IntRect(20 * (int)isLocked, 0, 20, 20));
		else
			m_lock.setFillColor(isLocked ? sf::Color::Red : sf::Color(244, 183, 19));

		m_text.setFillColor(sf::Color::White);
	}

	void Lock::activeState()
	{
		if (m_lock.getTexture() != nullptr)
			m_lock.setTextureRect(sf::IntRect(20 * (int)isLocked, 20, 20, 20));
		else
			m_lock.setFillColor(isLocked ? sf::Color(22, 192, 82) : sf::Color(52, 152, 219));

		m_text.setFillColor(sf::Color::White);
	}

	void Lock::selectedState()
	{
		if (m_lock.getTexture() != nullptr)
			m_lock.setTextureRect(sf::IntRect(20 * (int)isLocked, 40, 20, 20));
		else
			m_lock.setFillColor(isLocked ? sf::Color(50, 196, 19) : sf::Color(45, 107, 236));

		m_text.setFillColor(sf::Color(255, 255, 130));
	}
}
