/*
 * Notifications.h
 *
 *  Created on: Jan 24, 2015
 *      Author: dawid
 */

#pragma once

#include <component/ComponentManager.h>
#include <eventbus/EventCollector.h>
#include <functional>
#include <predeclare.h>
#include <type_traits>

namespace Dexode
{
    namespace Component
    {

        struct TouchBegan
        {
            cocos2d::CCTouch* touch;
        };
        struct TouchMoved
        {
            cocos2d::CCTouch* touch;
        };
        struct TouchEnded
        {
            cocos2d::CCTouch* touch;
        };

        template<typename T>
        struct has_onTouchBegan
        {
        private:
            template<typename U>
            static auto test(int, cocos2d::CCTouch* touch)
                -> decltype(std::declval<U>().onTouchBegan(touch), std::true_type{});

            template<typename>
            static std::false_type test(...);

        public:
            static const bool value = std::is_same<decltype(test<T>(0, nullptr)), std::true_type>::value;
        };

        template<typename T>
        typename std::enable_if<has_onTouchBegan<T>::value,
                                std::function<void(const Dexode::Component::TouchBegan&)>>::type
        get_onTouchBegan(T* value)
        {
            return [=](const Dexode::Component::TouchBegan& event) { value->onTouchBegan(event.touch); };
        }

        template<typename T>
        typename std::enable_if<has_onTouchBegan<T>::value == false,
                                std::function<void(const Dexode::Component::TouchBegan&)>>::type
        get_onTouchBegan(T* value)
        {
            return {};
        }
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        template<typename T>
        struct has_onTouchEnded
        {
        private:
            template<typename U>
            static auto test(int, cocos2d::CCTouch* touch)
                -> decltype(std::declval<U>().onTouchEnded(touch), std::true_type{});

            template<typename>
            static std::false_type test(...);

        public:
            static const bool value = std::is_same<decltype(test<T>(0, nullptr)), std::true_type>::value;
        };

        template<typename T>
        typename std::enable_if<has_onTouchEnded<T>::value,
                                std::function<void(const Dexode::Component::TouchEnded&)>>::type
        get_onTouchEnded(T* value)
        {
            return [=](const Dexode::Component::TouchEnded& event) { value->onTouchEnded(event.touch); };
        }

        template<typename T>
        typename std::enable_if<has_onTouchEnded<T>::value == false, std::function<void(cocos2d::CCTouch* touch)>>::type
        get_onTouchEnded(T* value)
        {
            return {};
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        template<typename T>
        struct has_onTouchMoved
        {
        private:
            template<typename U>
            static auto test(int, cocos2d::CCTouch* touch)
                -> decltype(std::declval<U>().onTouchMoved(touch), std::true_type{});

            template<typename>
            static std::false_type test(...);

        public:
            static const bool value = std::is_same<decltype(test<T>(0, nullptr)), std::true_type>::value;
        };

        template<typename T>
        typename std::enable_if<has_onTouchMoved<T>::value,
                                std::function<void(const Dexode::Component::TouchMoved&)>>::type
        get_onTouchMoved(T* value)
        {
            return [=](const Dexode::Component::TouchMoved& event) { value->onTouchMoved(event.touch); };
        }

        template<typename T>
        typename std::enable_if<has_onTouchMoved<T>::value == false,
                                std::function<void(const Dexode::Component::TouchMoved&)>>::type
        get_onTouchMoved(T* value)
        {
            return {};
        }
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        template<class T>
        EventCollector listenForTouches(T* component)
        {
            static_assert(std::is_base_of<Base, T>::value, "T must inherit from Base component");
            EventCollector collector{ component->getOwner()->getBus() };
            collector.listen<TouchBegan>(get_onTouchBegan(component));
            collector.listen<TouchMoved>(get_onTouchMoved(component));
            collector.listen<TouchEnded>(get_onTouchEnded(component));

            return collector;
        }

    } // namespace Component
} // namespace Dexode
