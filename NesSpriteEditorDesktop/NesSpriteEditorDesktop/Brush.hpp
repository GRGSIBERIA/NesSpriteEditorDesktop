#pragma once
#include "SingletonProvider.hpp"
#include "ColorCode.hpp"
#include "Definition.hpp"

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

		const ColorCode& GetBrush() const
		{
			return selectedCode;
		}

		/**
		* @return 選択しているパレットの色のIDを返す
		*/
		const ColorID GetSelectedColorID() const 
		{ 
			const auto selected = PaletteTableProvider::GetInstance().GetSelected();
			return PaletteTableProvider::GetInstance().GetPalette(selected).GetSelected();
		}
	};

	class BrushProvider : public SingletonProvider<Brush> {};
}