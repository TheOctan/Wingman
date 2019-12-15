
namespace oct
{
	template<typename T, typename... Param>
	inline void StateMachine::registerState(States::ID stateID, Param&&... arg)
	{
		mFactories[stateID] = [this, &arg...]()
		{
			return StateRef(new T(this, mContext, std::forward<Param>(arg)...));
		};
	}
}