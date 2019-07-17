#pragma once

template<typename EventParam>
class Event
{
	template <typename T>
	friend class EventHandler;
private:
	std::function<void(Object, EventParam)> func;
	int id;

private:
	void SetID(int id) { this->id = id; }

public:
	__declspec(property(get = GetID, put = SetID)) int ID;

	int GetID() { return id; }

public:
	Event(std::function<void(Object, EventParam)> func) : func(func)
	{

	}

public:
	void Call(Object sender, EventParam param)
	{
		func(sender, param);
	}

};

template<typename EventParam>
class EventHandler
{
private:
	map<int, Event<EventParam>*> eventHandler;

public:
	void AddListener(Event<EventParam>* e)
	{
		eventHandler.insert(make_pair((int)e, e));
		e->ID = (int)e;
	}

	bool Remove(Event<EventParam>* e)
	{
		auto iter = eventHandler.find((int)e);

		if (iter == eventHandler.end())
			return false;

		SAFE_DELETE(iter->second);
		eventHandler.erase(iter);

		return true;
	}

	void operator +=(Event<EventParam>* e)
	{
		AddListener(e);
	}

	void operator() (Object sender, EventParam param)
	{
		for (auto iter : eventHandler)
		{
			iter.second->Call(sender, param);
		}
	}

	void operator -=(Event<EventParam>* e)
	{
		Remove(e);
	}
};
