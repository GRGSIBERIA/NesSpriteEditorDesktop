#pragma once
#include <Siv3D.hpp>
#include "DrawableObject.hpp"
#include "PaletteCode.hpp"
#include "SingletonProvider.hpp"

namespace nes
{
	/**
	* 色のテーブルクラス
	*/
	class ColorTable : public DrawableObject
	{
		friend SingletonProvider<ColorTable>;

		s3d::Size patchSize;
		std::array<Rect, 0x40> paletteRects;

		// コンストラクタ ---------------------------------------------------

		ColorTable(const s3d::Size& patchSize = s3d::Size(24, 24)) : patchSize(patchSize), DrawableObject()
		{
			for (PCode i = 0; i < 4; ++i)
			{
				for (PCode j = 0; j < 16; ++j)
				{
					const PCode index = (i << 4) | j;
					paletteRects[index] = Rect();
				}
			}
		}

	public:

		// メソッド ---------------------------------------------------

		void Draw() override
		{
			for (PCode i = 0; i < 4; ++i)
			{
				for (PCode j = 0; j < 16; ++j)
				{
					const PCode index = (i << 4) | j;
					const auto& color = PaletteCode::GetColor(index);
					auto& palette = paletteRects[index];

					palette
						.setPos(Point(patchSize.x * j, patchSize.y * i) + Point(position))
						.setSize(patchSize)
						.draw(color)
						.drawFrame(1, s3d::Palette::Gray);
				}
			}

			Rect(position, s3d::Size(patchSize.x * 5, patchSize.y))
				.drawFrame(1, s3d::Palette::Darkgray);
		}

		void Update()
		{
			for each (const auto& palette in paletteRects)
			{
				if (palette.leftClicked())
				{
					// 選択中のパレットに対してメッセージを通知
					Logger << U"Message: leftClicked -> palette";
				}
			}
		}
	};

	/**
	* 色のテーブルを提供するクラス
	*/
	class ColorTableProvider : public SingletonProvider<ColorTable>	{};
}