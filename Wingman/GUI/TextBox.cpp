#include "TextBox.hpp"
#include <iostream>

namespace gui
{
	TextBox::TextBox() : TextBox("")
	{
		
	}

	TextBox::TextBox(const sf::String& str)
	:	Widget(WidgetSize::Wide)
	{
		m_rect.setSize(sf::Vector2f(dimensions[WidgetSize::Wide], 64));

		setText(str);
	}

	void TextBox::mouseButtonPressed(sf::Event e)
	{
		if (e.mouseButton.button == sf::Mouse::Left)
		{
			if (isEntered)
			{
				state = WidgetState::selected;
			}
			else
			{
				state = WidgetState::active;
			}
		}
	}

	void TextBox::KeyPressed(sf::Event e)
	{
		if (e.key.code == sf::Keyboard::Return)
			if (state == WidgetState::selected)
			{
				state = WidgetState::active;
				event(this, WidgetEvent(m_ModString, 0, isActive));
			}
	}

	void TextBox::TextEntered(sf::Event e)
	{
		if (state == WidgetState::selected)
		{
			sf::Uint32 keyCode = e.text.unicode;
			//std::cout << keyCode;

			if (isValidCharacter(keyCode))
			{
				if (m_text.getGlobalBounds().width + 50 <= m_rect.getGlobalBounds().width)
				{
					m_ModString.insert(m_ModString.getSize(), keyCode);
				}
			}
			else if (isBackspace(keyCode))
			{
				if (m_ModString.getSize() > 0)
					m_ModString.erase(m_ModString.getSize() - 1);
			}
			m_text.setString(m_ModString);
		}
	}

	void TextBox::reset()
	{
		m_rect.setFillColor(sf::Color::White);
		m_rect.setOutlineColor(sf::Color::Transparent);
		m_rect.setOutlineThickness(0);
	}

	void TextBox::updateText()
	{
		m_text.setPosition(15, m_rect.getGlobalBounds().height / 2.5f);
		m_ModString = m_text.getString();
	}

	void TextBox::notActiveState()
	{
		if (m_rect.getTexture() != nullptr)
			m_rect.setTextureRect(sf::IntRect(0, 0, 160, 32));
		else
			m_rect.setFillColor(sf::Color(22, 192, 82));

		m_text.setFillColor(sf::Color::Black);
	}

	void TextBox::activeState()
	{
		if (m_rect.getTexture() != nullptr)
			m_rect.setTextureRect(sf::IntRect(0, 32, 160, 32));
		else
			m_rect.setFillColor(sf::Color(52, 152, 219));

		m_text.setFillColor(sf::Color::White);
	}

	void TextBox::selectedState()
	{
		if (m_rect.getTexture() != nullptr)
			m_rect.setTextureRect(sf::IntRect(0, 64, 160, 32));
		else
			m_rect.setFillColor(sf::Color(45, 107, 236));

		m_text.setFillColor(sf::Color::White);
	}

	bool TextBox::isValidCharacter(sf::Uint32 keyCode)
	{
		return  keyCode >= 48 && keyCode <= 57 ||		// Numbers
				keyCode >= 65 && keyCode <= 90 ||		// Uppercase EN
				keyCode >= 97 && keyCode <= 122 ||		// Lowercase EN
				keyCode >= 1040 && keyCode <= 1171 ||	// Uppercase RU
				keyCode >= 1072 && keyCode <= 1103 ||	// Lowercase RU
				keyCode == 32 ||						// Space
				keyCode == 95 ||						// _
				keyCode == 40 || keyCode == 41			// ( )
			;
	}

	bool TextBox::isBackspace(sf::Uint32 keyCode)
	{
		return keyCode == 8;
	}
}
