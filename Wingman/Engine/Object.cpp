#include "Object.h"

namespace oct
{
	oct::Object::Object()
	{
		static uint32 id = 0;
		this->id = id++;
		this->name = "Object";
	}

	oct::Object::~Object()
	{
	}

	void oct::Object::onGUI()
	{
	}

	void oct::Object::set_name(std::string name)
	{
		this->name = name;
	}

	std::string Object::getName() const
	{
		return name;
	}

	uint32 Object::getId() const
	{
		return id;
	}

	std::string Object::uiText(std::string label)
	{
		std::string id = std::to_string(this->id);
		std::string separator = "##";
		return (label + separator + id);
	}

}