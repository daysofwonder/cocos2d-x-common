/*
 * Clickable.cpp
 *
 *  Created on: Jan 21, 2015
 *      Author: dawid
 */

#include "Clickable.h"

#include <Touch.h>

#include <component/ComponentManager.h>
#include <component/touch/TouchableEvents.h>

namespace Dexode
{
namespace Component
{

Clickable::Clickable(const OnClick& onClick)
		: _onClick(onClick)
		, _collector{nullptr}
{
}

void Clickable::onTouchEnded(cocos2d::CCTouch* touch)
{
	_onClick(touch);
}

void Clickable::onAttach()
{
	inherited::onAttach();
	_collector = listenForTouches(this);
}

void Clickable::onDetach()
{
	_collector.unlistenAll();
	inherited::onDetach();
}

} /* namespace Component */
} /* namespace Dexode */
