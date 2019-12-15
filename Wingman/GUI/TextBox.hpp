#pragma once

#ifndef __TEXTBOX_HPP__
#define __TEXTBOX_HPP__

#include <functional>

#include "Widget.hpp"

namespace gui
{
	class TextBox : public Widget
	{
	public:
		TextBox();
		TextBox(const sf::String& str);

	private:
		void mouseButtonPressed	(sf::Event e)	override;
		void KeyPressed			(sf::Event e)	override;
		void TextEntered		(sf::Event e)	override;

		void reset()		override;
		void updateText()	override;

		void notActiveState	() override;
		void activeState	() override;
		void selectedState	() override;

		bool isValidCharacter(sf::Uint32 keyCode);
		bool isBackspace(sf::Uint32 keyCode);

		sf::String			m_ModString;
	};

	//inline std::unique_ptr<TextBox> makeTextBox(std::string modStr) { return std::make_unique<TextBox>(modStr); }

} // namesapce gui

#endif // !__TEXTBOX_HPP__
