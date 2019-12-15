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
		return stateStack->foreach_if([&event](const ActivityRef& state) {
			return state->handleEvent(event);
		});
	}

	bool ActivityManager::preUpdate(sf::Time dt)
	{
		return stateStack->foreach_if([dt](const ActivityRef& state) {
			return state->preUpdate(dt);
		});
	}

	bool ActivityManager::update(sf::Time dt)
	{
		return stateStack->foreach_if([dt](const ActivityRef& state) {
			return state->update(dt);
		});
	}

	bool ActivityManager::postUpdate(sf::Time dt)
	{
		return stateStack->foreach_if([dt](const ActivityRef& state) {
			return state->postUpdate(dt);
		});
	}

	void ActivityManager::renderPreUpdate()
	{
		stateStack->foreach([](const ActivityRef& state) {
			state->renderPreUpdate();
		});
	}

	void ActivityManager::renderUpdate()
	{
		stateStack->foreach([](const ActivityRef& state) {
			state->renderUpdate();
		});
	}

	void ActivityManager::renderPostUpdate()
	{
		stateStack->foreach([](const ActivityRef& state) {
			state->renderPostUpdate();
		});
	}
}
