#pragma once

#include <string>
#include "types.h"

namespace oct
{
#define OCT_OBJECT(type_name, base_type_name) \
	public: \
	using ClassName = type_name; \
	using BaseClassName = base_type_name; \
	virtual std::string type() const override { return #type_name; } \
	virtual std::string base_type() const override { return #base_type_name; } \


	class Object
	{
	public:
		Object();
		virtual ~Object();

		virtual void onGUI();

		virtual std::string type() const = 0;
		virtual std::string base_type() const = 0;

		void set_name(std::string name);
		std::string getName() const;

		uint32 getId() const;

	protected:
		std::string uiText(std::string label);

	private:
		std::string name;
		uint32		id;
	};
}