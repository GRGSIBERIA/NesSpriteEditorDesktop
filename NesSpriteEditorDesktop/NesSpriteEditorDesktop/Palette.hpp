#pragma once
#include <Siv3D.hpp>
#include "PaletteCode.hpp"

namespace nes
{
	// 4色セットのパレット
	class Palette
	{
		std::array<PaletteCode, 4> codes;

	public:
		/*
		* コンストラクタ
		*/

		Palette(const PCode p1, const PCode p2, const PCode p3, const PCode p4)
			: codes({ PaletteCode(p1), PaletteCode(p2), PaletteCode(p3), PaletteCode(p4)}) {}

		Palette(const PaletteCode& p1, const PaletteCode& p2, const PaletteCode& p3, const PaletteCode& p4)
			: codes({ p1, p2, p3, p4}) {}

		Palette(const std::array<PCode, 4>& codes)
			: codes({ PaletteCode(codes[0]), PaletteCode(codes[1]), PaletteCode(codes[2]), PaletteCode(codes[3]) }) {}

		Palette(const std::array<PaletteCode, 4>& codes)
			: codes(codes) {}


		/*
		* アクセサ
		*/

		const PaletteCode& GetCode(const int index) const { return codes[index]; }

		void SetCode(const int index, const PCode p) { codes[index] = PaletteCode(p); }

		void SetCode(const int index, const PaletteCode& p) { codes[index] = p; }
	};
}