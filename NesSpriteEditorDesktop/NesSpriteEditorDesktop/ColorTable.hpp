#pragma once
#include <Siv3D.hpp>
#include "IDrawable.hpp"
#include "PaletteCode.hpp"
#include "SingletonProvider.hpp"

namespace nes
{
	/// シングルトンのためのプロトタイプ宣言
	class ColorTableProvider;

	/**
	* 色のテーブルクラス
	*/
	class ColorTable : public IDrawable
	{
		friend SingletonProvider<ColorTable>;

		s3d::Size patchSize;
		std::array<Rect, 0x40> paletteRects;

		// コンストラクタ ---------------------------------------------------

		ColorTable(const s3d::Size& patchSize = s3d::Size(24, 24)) : patchSize(patchSize)
		{
			for (PCode i = 0; i < 4; ++i)
			{
				for (PCode j = 0; j < 16; ++j)
				{
					const PCode index = (i << 4) | j;
					paletteRects[index] = Rect(patchSize);
				}
			}
		}

	public:

		// メソッド ---------------------------------------------------

		void Draw(const s3d::Point& position) override
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
						.draw(color)
						.drawFrame(1, Palette::Gray);

					if (palette.leftClicked())
					{
						// 選択中のパレットに対してメッセージを通知
						Logger << U"Message: leftClicked -> palette" << index;
					}
				}
			}
		}
	};

	/**
	* 色のテーブルを提供するクラス
	*/
	class ColorTableProvider : public SingletonProvider<ColorTable>	{};
}