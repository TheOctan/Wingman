#include"Widget.hpp"

namespace gui
{
	Widget::Widget(WidgetSize size)
	:	state			(WidgetState::active),
		globalMousePos	(0,0),
		localMousePos	(0,0),
		isActive		(true),
		isClicked		(false),
		isEntered		(false),
		outlineThickness(-2)
	{
		m_rect.setSize(sf::Vector2f(dimensions[size], 40));
		m_rect.setFillColor(sf::Color(52, 152, 219));
		m_rect.setOutlineColor(sf::Color::Black);
		m_rect.setOutlineThickness(outlineThickness);	

		m_text.setCharacterSize(25);
		m_text.setFillColor(sf::Color::White);
	}

	void Widget::setText(const sf::String& str)
	{
		m_text.setString(str);
		updateText();
	}

	void Widget::setTexture(const sf::Texture& texture)
	{
		reset();
		m_rect.setTexture(&texture);
		updateState();
	}

	void Widget::setFont(const sf::Font& font)
	{
		m_text.setFont(font);
	}

	void Widget::handleEvent(sf::Event e)
	{
		if (!isActive) return;

		switch (e.type)
		{
		case sf::Event::MouseMoved:				mouseMoved(e);			break;
		case sf::Event::MouseButtonPressed:		mouseButtonPressed(e);	break;
		case sf::Event::MouseButtonReleased:	mouseButtonReleased(e);	break;
		case sf::Event::KeyPressed:				KeyPressed(e);			break;
		case sf::Event::TextEntered:			TextEntered(e);			break;
		}

		updateState();
	}

	void Widget::setActive(bool active)
	{
		isActive = active;
		state = isActive ? WidgetState::active : WidgetState::notActive;
		updateState();
	}

	const sf::Vector2f & Widget::getSize() const
	{
		return m_rect.getSize();
	}

	sf::FloatRect Widget::getLocalBounds() const
	{
		return m_rect.getLocalBounds();
	}

	sf::FloatRect Widget::getGlobalBounds() const
	{
		return getTransform().transformRect(getLocalBounds());
	}

	void Widget::draw(sf::RenderTarget & target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		localMousePos = states.transform.getInverse().transformPoint(globalMousePos);

		target.draw(m_rect, states);
		drawResource(target, states);
		target.draw(m_text, states);
	}

	void Widget::drawResource(sf::RenderTarget & target, sf::RenderStates states) const
	{
	}

	void Widget::mouseMoved(sf::Event e)
	{
		globalMousePos = sf::Vector2f((float)e.mouseMove.x, (float)e.mouseMove.y);
		isEntered = m_rect.getGlobalBounds().contains(localMousePos);
	}

	void Widget::mouseButtonPressed(sf::Event e)
	{
	}

	void Widget::mouseButtonReleased(sf::Event e)
	{
	}

	void Widget::KeyPressed(sf::Event e)
	{
	}

	void Widget::TextEntered(sf::Event e)
	{
	}

	void Widget::reset()
	{
		m_rect.setFillColor(sf::Color::White);
		//m_rect.setOutlineColor(sf::Color::Transparent);
		//m_rect.setOutlineThickness(0);
	}

	void Widget::updateState()
	{
		switch (state)
		{
		case WidgetState::notActive:	notActiveState();	break;
		case WidgetState::active:		activeState();		break;
		case WidgetState::selected:		selectedState();	break;
		case WidgetState::warning:		warningState();		break;
		}
	}
}
