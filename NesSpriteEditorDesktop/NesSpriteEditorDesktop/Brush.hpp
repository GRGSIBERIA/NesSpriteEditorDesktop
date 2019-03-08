#pragma once
#include "SingletonProvider.hpp"
#include "PaletteCode.hpp"

namespace nes
{
	class Brush
	{
		friend SingletonProvider<Brush>;

		PaletteCode selectedCode;

	public:
		void SetBrush(const PaletteCode& code)
		{
			selectedCode = code;
		}
	};

	class BrushProvider : public SingletonProvider<Brush> {};
}