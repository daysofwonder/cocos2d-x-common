//
// Created by Dawid Drozd aka Gelldur on 8/17/16.
//

#pragma once

namespace ESport
{

template<class T>
class Size
{
public:
	T width;
	T height;

	Size(T width = 0, T height = 0)
			: width(width)
			, height(height)
	{
	}
};

template<class T>
bool operator<(const ESport::Size<T>& left, const ESport::Size<T>& right)
{
	return left.width < right.width || left.height < right.height;
}

template<class T>
bool operator==(const ESport::Size<T>& left, const ESport::Size<T>& right)
{
	return left.width == right.width && left.height == right.height;
}
}