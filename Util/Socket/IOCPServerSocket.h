#pragma once
#include "NS.h"
#include "IOCPBaseServer.h"
#include "../Common/Trace.h"
NS_SOCKET_BEGIN
template<typename ProtocolType, typename ...Types>
class IOCPServerSocket : public IOCPBaseServer
{
protected:
	IOCPServerSocket();
public:
	virtual ~IOCPServerSocket();
protected:
	std::map<ProtocolType, Util::Common::MulticastDelegate<void, Util::Socket::StateObject&, Types...>> _funcMaps;
public:
	void BindCallback(ProtocolType protocol, std::function<void(Util::Socket::StateObject&, Types...)> callback);
	void OnCallback(ProtocolType protocol, Util::Socket::StateObject& stateObject, Types...);
};
template<typename ProtocolType, typename ...Types>
IOCPServerSocket<ProtocolType, Types...>::IOCPServerSocket()
{
}
template<typename ProtocolType, typename ...Types>
IOCPServerSocket<ProtocolType, Types...>::~IOCPServerSocket()
{
}
template<typename ProtocolType, typename ...Types>
inline void IOCPServerSocket<ProtocolType, Types...>::BindCallback(ProtocolType protocol, std::function<void(Util::Socket::StateObject&, Types...)> callback)
{
	if (_funcMaps.find(protocol) == _funcMaps.end())
		_funcMaps.insert(std::pair<ProtocolType, Util::Common::MulticastDelegate<void, Util::Socket::StateObject&, Types...>>(protocol, std::move(callback)));
	else
		throw std::exception("An item with the same key has already been Added");
}
template<typename ProtocolType, typename ...Types>
inline void IOCPServerSocket<ProtocolType, Types...>::OnCallback(ProtocolType protocol, Util::Socket::StateObject& stateObject, Types... params)
{
	try
	{
		auto it = _funcMaps.find(protocol);
		if (it != _funcMaps.end())
			it->second(std::forward<Util::Socket::StateObject&>(stateObject), std::forward<Types>(params)...);
		else
			throw std::exception("KeyNotFoundException");
	}
	catch (std::exception ex)
	{
		Util::Common::Trace::WriteLine(ex.what());
	}
	catch (...)
	{
		Util::Common::Trace::WriteLine("OnCallbackException");
	}
}
NS_SOCKET_END
