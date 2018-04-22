#pragma once
#include <functional>
#include "NS.h"

NS_COMMON_BEGIN
template<typename R, typename ...Types>
class IDelegate
{
protected:
	std::function<R(Types...)> _target;
public:
	bool operator != (const IDelegate& d) const;
	bool operator != (nullptr_t) const;
	bool operator == (const IDelegate& d) const;
	bool operator == (nullptr_t) const;
	void operator = (nullptr_t);
};
template<typename R, typename ...Types>
bool IDelegate<R, Types...>::operator != (nullptr_t) const
{
	return _target != nullptr || _target != NULL;
}

template<typename R, typename ...Types>
bool IDelegate<R, Types...>::operator != (const IDelegate& d) const
{
	return this != &d;
}

template<typename R, typename ...Types>
bool IDelegate<R, Types...>::operator == (nullptr_t) const
{
	return _target == nullptr || _target == NULL;
}

template<typename R, typename ...Types>
bool IDelegate<R, Types...>::operator == (const IDelegate& d) const
{
	return this == &d;
}

template<typename R, typename ...Types>
void IDelegate<R, Types...>::operator = (nullptr_t)
{
	_target = nullptr;
}

template<typename T1, typename T2 = void, typename T3 = void, typename T4 = void, typename T5 = void>
class Delegate : public IDelegate<void, T1, T2, T3, T4, T5>
{
public:
	Delegate()
	{
		_target = nullptr;
	}
	Delegate(std::function<void(T1, T2, T3, T4, T5)> target)
	{
		_target = target;
	}
	virtual ~Delegate() {}
public:
	void operator () (T1, T2, T3, T4, T5);
	void operator = (std::function<void(T1, T2, T3, T4, T5)> func);
};

template<typename T1, typename T2, typename T3, typename T4, typename T5>
inline void Delegate<T1, T2, T3, T4, T5>::operator = (std::function<void(T1, T2, T3, T4, T5)> target)
{
	_target = target;
}
template<typename T1, typename T2, typename T3, typename T4, typename T5>
inline void Delegate<T1, T2, T3, T4, T5>::operator() (T1 param1, T2 param2, T3 param3, T4 param4, T5 param5)
{
	_target(param1, param2, param3, param4, param5);
}

template<typename T1, typename T2, typename T3, typename T4>
class Delegate<T1, T2, T3, T4, void> : public IDelegate<void, T1, T2, T3, T4>
{
public:
	Delegate()
	{
		_target = nullptr;
	}
	Delegate(std::function<void(T1, T2, T3, T4)> target)
	{
		_target = target;
	}
	virtual ~Delegate() {}
public:
	void operator () (T1, T2, T3, T4);
	void operator = (std::function<void(T1, T2, T3, T4)> func);
};

template<typename T1, typename T2, typename T3, typename T4>
inline void Delegate<T1, T2, T3, T4>::operator = (std::function<void(T1, T2, T3, T4)> target)
{
	_target = target;
}

template<typename T1, typename T2, typename T3, typename T4>
inline void Delegate<T1, T2, T3, T4>::operator() (T1 param1, T2 param2, T3 param3, T4 param4)
{
	_target(param1, param2, param3, param4);
}

template<typename T1, typename T2, typename T3>
class Delegate<T1, T2, T3, void, void> : public IDelegate<void, T1, T2, T3>
{
public:
	Delegate()
	{
		_target = nullptr;
	}
	Delegate(std::function<void(T1, T2, T3)> target)
	{
		_target = target;
	}
	virtual ~Delegate() {}
public:
	void operator () (T1, T2, T3);
	void operator = (std::function<void(T1, T2, T3)> func);
};

template<typename T1, typename T2, typename T3>
inline void Delegate<T1, T2, T3>::operator = (std::function<void(T1, T2, T3)> target)
{
	_target = target;
}
template<typename T1, typename T2, typename T3>
inline void Delegate<T1, T2, T3>::operator() (T1 param1, T2 param2, T3 param3)
{
	_target(param1, param2, param3);
}

template<typename T1, typename T2>
class Delegate<T1, T2, void, void, void> : public IDelegate<void, T1, T2>
{
public:
	Delegate()
	{
		_target = nullptr;
	}
	Delegate(std::function<void(T1, T2)> target)
	{
		_target = target;
	}
	virtual ~Delegate() {}
public:
	void operator () (T1, T2);
	void operator = (std::function<void(T1, T2)> func);
};

template<typename T1, typename T2>
inline void Delegate<T1, T2>::operator = (std::function<void(T1, T2)> target)
{
	_target = target;
}
template<typename T1, typename T2>
inline void Delegate<T1, T2>::operator() (T1 param1, T2 param2)
{
	_target(param1, param2);
}

template<typename T>
class Delegate <T, void, void, void, void> : public IDelegate<void, T>
{
public:
	Delegate()
	{
		_target = nullptr;
	}
	Delegate(std::function<void(T)> target)
	{
		_target = target;
	}
	~Delegate() {}
public:
	void operator () (T);
	void operator = (std::function<void(T)> func);
};

template<typename T>
inline void Delegate<T>::operator = (std::function<void(T)> target)
{
	_target = target;
}
template<typename T>
inline void Delegate<T>::operator () (T param)
{
	_target(param);
}

template<typename R, typename T1, typename T2 = void, typename T3 = void, typename T4 = void, typename T5 = void>
class MulticastDelegate : public IDelegate<R, T1, T2, T3, T4, T5>
{
public:
	MulticastDelegate()
	{
		_target = nullptr;
	}
	MulticastDelegate(std::function<R(T1, T2, T3, T4, T5)> target)
	{
		_target = target;
	}
	virtual ~MulticastDelegate() {}
public:
	R operator () (T1, T2, T3, T4, T5);
	void operator = (std::function<R(T1, T2, T3, T4, T5)> func);
};

template<typename R, typename T1, typename T2, typename T3, typename T4, typename T5>
inline void MulticastDelegate<R, T1, T2, T3, T4, T5>::operator = (std::function<R(T1, T2, T3, T4, T5)> target)
{
	_target = target;
}
template<typename R, typename T1, typename T2, typename T3, typename T4, typename T5>
inline R MulticastDelegate<R, T1, T2, T3, T4, T5>::operator() (T1 param1, T2 param2, T3 param3, T4 param4, T5 param5)
{
	return _target(param1, param2, param3, param4, param5);
}


template<typename R, typename T1, typename T2, typename T3, typename T4>
class MulticastDelegate<R, T1, T2, T3, T4, void> : public IDelegate<R, T1, T2, T3, T4>
{
public:
	MulticastDelegate()
	{
		_target = nullptr;
	}
	MulticastDelegate(std::function<R(T1, T2, T3, T4)> target)
	{
		_target = target;
	}
	virtual ~MulticastDelegate() {}
public:
	R operator () (T1, T2, T3, T4);
	void operator = (std::function<R(T1, T2, T3, T4)> func);
};

template<typename R, typename T1, typename T2, typename T3, typename T4>
inline void MulticastDelegate<R, T1, T2, T3, T4>::operator = (std::function<R(T1, T2, T3, T4)> target)
{
	_target = target;
}
template<typename R, typename T1, typename T2, typename T3, typename T4>
inline R MulticastDelegate<R, T1, T2, T3, T4>::operator() (T1 param1, T2 param2, T3 param3, T4 param4)
{
	return _target(param1, param2, param3, param4);
}

template<typename R, typename T1, typename T2, typename T3>
class MulticastDelegate<R, T1, T2, T3, void, void> : public IDelegate<R, T1, T2, T3>
{
public:
	MulticastDelegate()
	{
		_target = nullptr;
	}
	MulticastDelegate(std::function<R(T1, T2, T3)> target)
	{
		_target = target;
	}
	virtual ~MulticastDelegate() {}
public:
	R operator () (T1, T2, T3);
	void operator = (std::function<R(T1, T2, T3)> func);
};

template<typename R, typename T1, typename T2, typename T3>
inline void MulticastDelegate<R, T1, T2, T3>::operator = (std::function<R(T1, T2, T3)> target)
{
	_target = target;
}
template<typename R, typename T1, typename T2, typename T3>
inline R MulticastDelegate<R, T1, T2, T3>::operator() (T1 param1, T2 param2, T3 param3)
{
	return _target(param1, param2, param3);
}

template<typename R, typename T1, typename T2>
class MulticastDelegate<R, T1, T2, void, void, void> : public IDelegate<R, T1, T2>
{
public:
	MulticastDelegate()
	{
		_target = nullptr;
	}
	MulticastDelegate(std::function<R(T1, T2)> target)
	{
		_target = target;
	}
	virtual ~MulticastDelegate() {}
public:
	R operator () (T1, T2);
	void operator = (std::function<R(T1, T2)> func);
};

template<typename R, typename T1, typename T2>
inline void MulticastDelegate<R, T1, T2>::operator = (std::function<R(T1, T2)> target)
{
	_target = target;
}
template<typename R, typename T1, typename T2>
inline R MulticastDelegate<R, T1, T2>::operator() (T1 param1, T2 param2)
{
	return _target(param1, param2);
}

template<typename R, typename T>
class MulticastDelegate<R, T, void, void, void, void> : public IDelegate<R, T>
{
public:
	MulticastDelegate()
	{
		_target = nullptr;
	}
	MulticastDelegate(std::function<R(T)> target)
	{
		_target = target;
	}
	virtual ~MulticastDelegate() {}
public:
	R operator () (T);
	void operator = (std::function<R(T)> func);
};

template<typename R, typename T>
inline void MulticastDelegate<R, T>::operator = (std::function<R(T)> target)
{
	_target = target;
}
template<typename R, typename T>
inline R MulticastDelegate<R, T>::operator() (T param)
{
	return _target(param);
}

NS_COMMON_END