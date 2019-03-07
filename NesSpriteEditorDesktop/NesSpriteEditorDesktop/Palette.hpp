#pragma once
#include "PaletteCode.hpp"
#include "DrawableObject.hpp"

namespace nes
{
	/**
	* 4色セットのパレット
	*/
	class Palette : public DrawableObject
	{
		std::array<PaletteCode, 4> codes;
		s3d::Size patchSize = s3d::Size(24, 24);

	public:
		// コンストラクタ ---------------------------------------------------
		
		Palette(const PCode p1, const PCode p2, const PCode p3, const PCode p4)
			: codes({ PaletteCode(p1), PaletteCode(p2), PaletteCode(p3), PaletteCode(p4)}) {}

		Palette(const PaletteCode& p1, const PaletteCode& p2, const PaletteCode& p3, const PaletteCode& p4)
			: codes({ p1, p2, p3, p4}) {}

		Palette(const std::array<PCode, 4>& codes)
			: codes({ PaletteCode(codes[0]), PaletteCode(codes[1]), PaletteCode(codes[2]), PaletteCode(codes[3]) }) {}

		Palette(const std::array<PaletteCode, 4>& codes)
			: codes(codes) {}

		Palette()
			: codes({ PaletteCode(0), PaletteCode(0), PaletteCode(0), PaletteCode(0)}), DrawableObject() {}


		// アクセサ ---------------------------------------------------

		const PaletteCode& GetCode(const int index) const { return codes[index]; }

		void SetCode(const int index, const PCode p) { codes[index] = PaletteCode(p); }

		void SetCode(const int index, const PaletteCode& p) { codes[index] = p; }

		void SetSize(const s3d::Size& size) { patchSize = size; }

		// メソッド ---------------------------------------------------

		void Draw() override
		{
			for (int i = 0; i < 4; ++i)
			{
				Rect(position.x + patchSize.x * i, position.y, patchSize)
					.draw(codes[i].GetColor())
					.drawFrame(1, s3d::Palette::Darkgray);
			}
		}
	};
}