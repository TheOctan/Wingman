#pragma once

#ifndef DELEGATE_H
#define DELEGATE_H

#include <vector>
#include <memory>
#include <algorithm>

template<class Listener, typename Result, typename... Args>
using Handler = Result(Listener::*)(Args...);

template<typename Result, typename... Args>
class DelegateCallbackBase
{
public:
	virtual ~DelegateCallbackBase() = default;

	virtual Result notify(const Args&... args) const = 0;
	virtual bool compare(const DelegateCallbackBase<Result, Args...>& other) const = 0;
};

template<typename Result, typename... Args>
bool operator == (const DelegateCallbackBase<Result, Args...>& left, const DelegateCallbackBase<Result, Args...>& right)
{
	return left.compare(right);
}

template<typename Result, typename... Args>
bool operator != (const DelegateCallbackBase<Result, Args...>& left, const DelegateCallbackBase<Result, Args...>& right)
{
	return !(left == right);
}

//=========================================================================================================================================

template<class Listener, typename Result, typename... Args>
class DelegateCallback : public DelegateCallbackBase<Result, Args...>
{
public:
	DelegateCallback(Listener* object, Handler<Listener, Result, Args...> member)
	{
		_object = object;
		_member = member;
	}
	Result notify(const Args&... args) const override
	{
		return (_object->*_member)(args...);
	}
	bool compare(const DelegateCallbackBase<Result, Args...>& other) const override
	{
		if (const auto* ptr = dynamic_cast<const DelegateCallback<Listener, Result, Args...>*>(&other))
		{
			return this->_member == ptr->_member;
		}

		return false;
	}

private:
	Listener* _object;
	Handler<Listener, Result, Args...>	_member;
};

//=========================================================================================================================================

template<typename Result, typename... Args>
class Delegate
{
public:
	template<class Listener>
	void connect(Listener *object, Handler<Listener, Result, Args...> member)
	{
		_delegates.push_back(std::make_shared<DelegateCallback<Listener, Result, Args...>>(object, member));
	}
	Result invoke(const Args&... args) const
	{
		if (!_delegates.empty())
		{
			for (size_t i = 0; i < _delegates.size() - 1; i++)
			{
				_delegates.at(i)->notify(args...);
			}
			return _delegates.back()->notify(args...);
		}
		return Result();
	}

	Result operator()(const Args&... args) const
	{
		return invoke(args...);
	}
	Delegate<Result, Args...>& operator += (const Delegate<Result, Args...>& other)
	{
		auto size = this->_delegates.size();
		this->_delegates.resize(size + other._delegates.size());

		std::copy(other._delegates.begin(), other._delegates.end(), this->_delegates.begin() + size);

		return *this;
	}

	template<typename Result, typename... Args>
	friend Delegate<Result, Args...> operator + (const Delegate<Result, Args...>& left, const Delegate<Result, Args...>& right);

	template<typename Result, typename... Args>
	friend bool operator == (const Delegate<Result, Args...>& left, const Delegate<Result, Args...>& right);

private:
	std::vector<std::shared_ptr<DelegateCallbackBase<Result, Args...>>> _delegates;
};

template<typename... Args>
class Delegate<bool, Args...>
{
public:
	template<class Listener>
	void connect(Listener *object, Handler<Listener, bool, Args...> member)
	{
		_delegates.push_back(std::make_shared<DelegateCallback<Listener, bool, Args...>>(object, member));
	}
	bool invoke(const Args&... args) const
	{
		auto status = true;

		for (size_t i = 0; i < _delegates.size(); i++)
		{
			status = status && _delegates.at(i)->notify(args...);
		}

		return status;
	}

	bool operator()(const Args&... args) const
	{
		return  invoke(args...);
	}
	Delegate<bool, Args...>& operator += (const Delegate<bool, Args...>& other)
	{
		auto size = this->_delegates.size();
		this->_delegates.resize(size + other._delegates.size());

		std::copy(other._delegates.begin(), other._delegates.end(), this->_delegates.begin() + size);

		return *this;
	}

	template<typename Result, typename... Args>
	friend Delegate<Result, Args...> operator + (const Delegate<Result, Args...>& left, const Delegate<Result, Args...>& right);

	template<typename Result, typename... Args>
	friend bool operator == (const Delegate<Result, Args...>& left, const Delegate<Result, Args...>& right);

private:
	std::vector<std::shared_ptr<DelegateCallbackBase<bool, Args...>>> _delegates;
};

template<typename Result, typename... Args>
Delegate<Result, Args...> operator + (const Delegate<Result, Args...>& left, const Delegate<Result, Args...>& right)
{
	Delegate<Result, Args...> temp;
	temp._delegates.resize(left._delegates.size() + right._delegates.size());

	std::copy(left._delegates.begin(), left._delegates.end(), temp._delegates.begin());
	std::copy(right._delegates.begin(), right._delegates.end(), temp._delegates.begin() + left._delegates.size());

	return temp;
}

template<typename T>
class PtrComparer
{
public:
	bool operator()(const T& left, const T& right)
	{
		return *left == *right;
	}
};

template<typename Result, typename... Args>
bool operator == (const Delegate<Result, Args...>& left, const Delegate<Result, Args...>& right)
{
	if (left._delegates.size() == right._delegates.size())
	{
		return std::is_permutation(
			left._delegates.begin(),
			left._delegates.end(),
			right._delegates.begin(),
			PtrComparer<std::shared_ptr<DelegateCallbackBase<Result, Args...>>>()
		);
	}

	return false;
}

template<typename Result, typename... Args>
bool operator != (const Delegate<Result, Args...>& left, const Delegate<Result, Args...>& right)
{
	return !(left == right);
}

//=========================================================================================================================================

template<typename... Args>
using Action = Delegate<void, Args...>;

template<typename... Args>
using Predicate = Delegate<bool, Args...>;

typedef Delegate<void> Delegate_t;
typedef Action<> Action_t;
typedef Predicate<> Predicate_t;

#endif
