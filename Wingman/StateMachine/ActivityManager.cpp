#include "ActivityManager.h"
#include "StateAdapter.h"

namespace oct
{
	bool ActivityManager::handleEvent(const sf::Event& event)
	{
		return machine->foreach([&event](const ActivityRef& state) {
			return state->handleEvent(event);
		});
	}

	bool ActivityManager::preUpdate()
	{
		return machine->foreach([](const ActivityRef& state) {
			return state->preUpdate();
		});
	}

	bool ActivityManager::update(sf::Time dt)
	{
		return machine->foreach([&dt](const ActivityRef& state) {
			return state->update(dt);
		});
	}

	bool ActivityManager::postUpdate()
	{
		return machine->foreach([](const ActivityRef& state) {
			return state->postUpdate();
		});
	}

	void ActivityManager::renderPreUpdate()
	{
		machine->foreach([](const ActivityRef& state) {
			state->renderPreUpdate();
			return true;
		});
	}

	void ActivityManager::renderUpdate()
	{
		machine->foreach([](const ActivityRef& state) {
			state->renderPreUpdate();
			return true;
		});
	}

	void ActivityManager::renderPostUpdate()
	{
		machine->foreach([](const ActivityRef& state) {
			state->renderPreUpdate();
			return true;
		});
	}

	void ActivityManager::registerStates() const
	{
		machine->registerState<ConcreteState>(States::Test);
	}
}
