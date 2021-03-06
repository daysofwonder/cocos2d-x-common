/*
 * Builder.cpp
 *
 *  Created on: Jan 21, 2015
 *      Author: dawid
 */

#include "Builder.h"

#include <component/ComponentManager.h>
#include <component/touch/Touchable.h>
#include <component/touch/click/Clickable.h>
#include <component/touch/drag/Draggable.h>

#include <component/complex/model/Counter.h>

#include <cocos2d.h>

namespace Dexode
{
namespace Component
{

Builder::Builder(cocos2d::CCNode* node)
		: _node(node)
		, _manager(ComponentManager::create(node))
{
	_node->setUserObject(_manager);
}

template<class T>
T* addComponent(ComponentManager* manager)
{
	auto component = manager->getComponent<T>();
	if (component == nullptr)
	{
		//We want only 1 such component
		manager->addComponent<T>(std::unique_ptr<T>(new T()));
	}
	return manager->getComponent<T>();
}

ComponentManager* Builder::getComponentManager() const
{
	return _manager;
}

Builder& Builder::addTouchable(cocos2d::CCNode* node)
{
	using ComponentType = Touchable;

	auto component = addComponent<ComponentType>(_manager);

	if (node == nullptr)
	{
		node = _node;
	}

	component->addTouchable(node);

	return *this;
}

Builder& Builder::setDraggable(int flags)
{
	using ComponentType = Draggable;
	auto component = addComponent<ComponentType>(_manager);

	component->setFlags(flags);

	return *this;
}

Builder& Builder::setDraggable(const OnTouch& onTouchBegan, const OnTouch& onTouchMoved, const OnTouch& onTouchEnded)
{
	using ComponentType = Draggable;
	setDraggable();

	auto component = _manager->getComponent<ComponentType>();
	component->setListeners(onTouchBegan, onTouchMoved, onTouchEnded);

	return *this;
}

Builder& Builder::setDraggableOnTouchBegan(const OnTouch& onTouchBegan)
{
	using ComponentType = Draggable;
	setDraggable();

	auto component = _manager->getComponent<ComponentType>();
	component->setListenerTouchBegan(onTouchBegan);
	return *this;
}

Builder& Builder::setDraggableOnTouchMoved(const OnTouch& onTouchMoved)
{
	using ComponentType = Draggable;
	setDraggable();

	auto component = _manager->getComponent<ComponentType>();
	component->setListenerTouchMoved(onTouchMoved);
	return *this;
}

Builder& Builder::setDraggableOnTouchEnded(const OnTouch& onTouchEnded)
{
	using ComponentType = Draggable;
	setDraggable();

	auto component = _manager->getComponent<ComponentType>();
	component->setListenerTouchEnded(onTouchEnded);
	return *this;
}

Builder& Builder::setClickable(const OnClick& onClick)
{
	using ComponentType = Clickable;
	//We want only 1 such component
	if (_manager->hasComponent<ComponentType>())
	{
		return *this;
	}

	auto component = new ComponentType(onClick);
	_manager->addComponent(std::unique_ptr<ComponentType>(component));

	return *this;
}

Builder& Builder::setCounter(const int count)
{
	using ComponentType = Counter;
	auto component = addComponent<ComponentType>(_manager);

	component->set(count);

	return *this;
}

} /* namespace Component */
} /* namespace Dexode */
