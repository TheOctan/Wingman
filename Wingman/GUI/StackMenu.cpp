#include "StackMenu.hpp"
#include<iostream>

namespace gui
{
	StackMenu::StackMenu()
	:	m_basePosition	(75, 50),
		m_nextPosition	(m_basePosition),
		m_baseSize		(m_basePosition.x * 2, m_basePosition.y * 2),
		interval		(10.f),
		offset			(16.f)
	{
		m_background.setSize(m_baseSize);
		m_background.setFillColor(sf::Color(174, 184, 219));
		m_background.setOutlineColor(sf::Color::Black);
		m_background.setOutlineThickness(-2);

		m_titleText.setPosition(0, m_basePosition.y - 40);
		m_titleText.setOutlineThickness(1);
		m_titleText.setCharacterSize(30);
		m_titleText.setFillColor(sf::Color::White);
		m_titleText.setOutlineColor(sf::Color::Black);

		for (auto& obj : rect)
		{
			obj.setSize(sf::Vector2f(75, 50));
			obj.setFillColor(sf::Color::Red);
		}
	}

	StackMenu::~StackMenu()
	{
		for (auto ptr : m_widgets)
			delete ptr;
	}

	void StackMenu::addWidget(Widget* widget, bool rightSide)
	{
		initWidget			(widget, rightSide);
		m_widgets.push_back	(widget);
	}

	void StackMenu::setTitle(const sf::String& title)
	{
		m_titleText.setString(title);
	}

	void StackMenu::setTexture(const sf::Texture & texture)
	{
		reset();
		m_background.setTexture(&texture);
		//m_background.setFillColor(sf::Color(0, 0, 0, 150));
	}

	void StackMenu::setFont(const sf::Font& font)
	{
		m_titleText.setFont(font);
	}

	const sf::Vector2f& StackMenu::getSize() const
	{
		return m_background.getSize();
	}

	void StackMenu::handleEvent(sf::Event e)
	{
		for (size_t i = 0; i < m_widgets.size(); i++)
		{
			m_widgets.at(i)->handleEvent(e);
		}
	}

	void StackMenu::draw(sf::RenderTarget & target, sf::RenderStates states) const
	{
		states.transform *= getTransform();

		target.draw(m_background, states);
		target.draw(m_titleText, states);
		for (auto widget : m_widgets)
		{
			target.draw(*widget, states);
		}
		for (auto& obj : rect)
		{
			//target.draw(obj, states);
		}
	}

	void StackMenu::initWidget(Widget* widget, bool rightSide)
	{
		if (m_widgets.size() == 0)
		{
			smallWidth = widget->getGlobalBounds().width;

			m_baseSize.x += widget->getSize().x;
			m_baseSize.y += widget->getSize().y;

			widget->setPosition(m_basePosition);

			m_nextPosition.x += widget->getSize().x + offset;
			m_nextPosition.y += widget->getSize().y + interval;
		}
		else
		{
			smallWidth = std::min(smallWidth, widget->getGlobalBounds().width);

			if (rightSide)
			{
				widget->setPosition(m_nextPosition.x, m_basePosition.y);
				
				m_nextPosition.x += widget->getSize().x + offset;
			}
			else
			{
				widget->setPosition(m_basePosition.x, m_nextPosition.y);

				// reset
				m_basePosition.y = m_nextPosition.y;
				m_nextPosition.x = m_basePosition.x + widget->getSize().x + offset;

				m_nextPosition.y	+= widget->getSize().y + interval;
				m_baseSize.y		+= widget->getSize().y + interval;
			}
		}

		auto bounds = widget->getGlobalBounds();
		while (bounds.left + bounds.width >= m_baseSize.x)
		{
			m_baseSize.x += smallWidth + offset;
		}

		m_background.setSize(m_baseSize);

		rect[1].setPosition(getSize().x - rect[1].getSize().x, 0);
		rect[2].setPosition(0, getSize().y - rect[2].getSize().y);
		rect[3].setPosition(getSize().x - rect[3].getSize().x, getSize().y - rect[3].getSize().y);

		updateText();
	}

	void StackMenu::updateText()
	{
		m_titleText.setPosition(
			m_background.getGlobalBounds().width / 2 - m_titleText.getGlobalBounds().width / 2,
			m_titleText.getPosition().y
		);
	}

	void StackMenu::reset()
	{
		m_background.setFillColor(sf::Color::White);
		m_background.setOutlineColor(sf::Color::Transparent);
		m_background.setOutlineThickness(0);
	}
}
