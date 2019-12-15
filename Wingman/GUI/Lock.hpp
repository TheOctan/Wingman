#pragma once

#ifndef __LOCK_HPP__
#define __LOCK_HPP__

#include"Widget.hpp"

namespace gui
{
	class Lock : public Widget
	{
	public:
		Lock();
		Lock(const sf::String& str, WidgetSize size = WidgetSize::Wide);

		void setTexture	(const sf::Texture& texture)	override;

		bool isLocked = false;

	private:
		void drawResource(sf::RenderTarget& target, sf::RenderStates states) const;

		void mouseMoved			(sf::Event e)			override;
		void mouseButtonPressed	(sf::Event e)			override;

		void reset			() override;
		void updateText		() override;

		void notActiveState	() override;
		void activeState	() override;
		void selectedState	() override;

		sf::RectangleShape	m_lock;
	};

} // namespace gui

#endif // !__LOCK_HPP__
