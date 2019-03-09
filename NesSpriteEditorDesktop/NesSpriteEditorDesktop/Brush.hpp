#pragma once
#include "SingletonProvider.hpp"
#include "ColorCode.hpp"

namespace nes
{
	class Brush
	{
		friend SingletonProvider<Brush>;

		ColorCode selectedCode;

	public:
		void SetBrush(const ColorCode& code)
		{
			selectedCode = code;
		}
	};

	class BrushProvider : public SingletonProvider<Brush> {};
}