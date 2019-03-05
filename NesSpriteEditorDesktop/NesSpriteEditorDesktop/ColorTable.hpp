#pragma once
#include <Siv3D.hpp>
#include "IDrawable.hpp"
#include "PaletteCode.hpp"

namespace nes
{
	class ColorTable : public IDrawable
	{
		s3d::Size patchSize;

	public:
		
		// コンストラクタ ---------------------------------------------------

		ColorTable(const s3d::Size& patchSize = s3d::Size(24, 24)) : patchSize(patchSize) {}

		// メソッド ---------------------------------------------------

		void Draw(const s3d::Point& position) override
		{
			for (int i = 0; i < 4; ++i)
			{
				for (int j = 0; j < 16; ++j)
				{
					const int index = (i << 4) | j;
					const auto& color = PaletteCode::GetColor((PCode)index);

					Rect(patchSize).setSize(patchSize).setPos(Point(patchSize.x * i, patchSize.y * j) + Point(position)).draw(color).drawFrame(1, Palette::Ivory);
				}
			}
		}
	};
}