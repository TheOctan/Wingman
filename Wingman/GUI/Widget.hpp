#pragma once

#ifndef __WIDGET_HPP__
#define __WIDGET_HPP__

#include <SFML/Graphics.hpp>
#include <memory>
#include "WidgetEventArgs.hpp"

namespace gui
{
	class Widget : public sf::Drawable, public sf::Transformable
	{
	public:
		enum WidgetState
		{
			notActive = 0,
			active,
			selected,
			warning
		};
		enum WidgetSize
		{
			Narrow = 0,
			Small,
			Wide
		};

#pragma region Typedef

		using WidgetEventHandler = EventHandler<Widget, WidgetEventArgs>;
		template<class Listener>
		using Method = Handler<Listener, void, Widget*, const WidgetEventArgs&>;

		template<class Listener>
		void subscribe(Listener* obj, Method<Listener> member);

#pragma endregion

		Widget(WidgetSize size);
		virtual ~Widget() = default;

				
		virtual void setText		(const sf::String& str);
		virtual void setTexture		(const sf::Texture& texture);
				void setFont		(const sf::Font& font);
				void setActive		(bool active = true);

				void handleEvent	(sf::Event e);

		//virtual void setValue		(int value) = 0;
		
		const sf::Vector2f&	getSize			() const;
		sf::FloatRect		getLocalBounds	() const;
		sf::FloatRect		getGlobalBounds	() const;

	private:
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	protected:
		virtual void drawResource(sf::RenderTarget& target, sf::RenderStates states) const;

		virtual void mouseMoved				(sf::Event e);
		virtual void mouseButtonPressed		(sf::Event e);
		virtual void mouseButtonReleased	(sf::Event e);
		virtual void KeyPressed				(sf::Event e);
		virtual void TextEntered			(sf::Event e);
		
		virtual void reset		();
		virtual void updateState();
		virtual void updateText	() = 0;

		virtual void notActiveState	() {}
		virtual void activeState	() {}
		virtual void selectedState	() {}
		virtual void warningState	() {}

		WidgetEventHandler		event;

		mutable sf::Vector2f	localMousePos;					// final
		sf::Vector2f			globalMousePos;					// final
		sf::RectangleShape		m_rect;							// final
		sf::Text				m_text;							// final

		WidgetState				state;							// final

		bool isActive;
		bool isClicked;
		bool isEntered;

		float outlineThickness;

		float dimensions[3]{ 88, 192, 400 };
	};

	template<class Listener>
	inline void Widget::subscribe(Listener* obj, Method<Listener> member)
	{
		event.connect(obj, member);
	}

} // namespace gui

#endif // !__WIDGET_HPP__
