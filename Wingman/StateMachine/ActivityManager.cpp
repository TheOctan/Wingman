#include "ActivityManager.h"
#include "StateAdapter.h"

namespace oct
{
	ActivityManager::ActivityManager(StateStack& stack)
		: stateStack(&stack)
	{

	}

	bool ActivityManager::handleEvent(const sf::Event& event)
	{
		return stateStack->foreach([&event](const ActivityRef& state) {
			return state->handleEvent(event);
		});
	}

	bool ActivityManager::preUpdate()
	{
		return stateStack->foreach([](const ActivityRef& state) {
			return state->preUpdate();
		});
	}

	bool ActivityManager::update(sf::Time dt)
	{
		return stateStack->foreach([&dt](const ActivityRef& state) {
			return state->update(dt);
		});
	}

	bool ActivityManager::postUpdate()
	{
		return stateStack->foreach([](const ActivityRef& state) {
			return state->postUpdate();
		});
	}

	void ActivityManager::renderPreUpdate()
	{
		stateStack->foreach([](const ActivityRef& state) {
			state->renderPreUpdate();
			return true;
		});
	}

	void ActivityManager::renderUpdate()
	{
		stateStack->foreach([](const ActivityRef& state) {
			state->renderPreUpdate();
			return true;
		});
	}

	void ActivityManager::renderPostUpdate()
	{
		stateStack->foreach([](const ActivityRef& state) {
			state->renderPreUpdate();
			return true;
		});
	}
}
