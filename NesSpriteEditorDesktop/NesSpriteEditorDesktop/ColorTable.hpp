#pragma once
#include <Siv3D.hpp>
#include "DrawableObject.hpp"
#include "ColorCode.hpp"
#include "SingletonProvider.hpp"
#include "PaletteTable.hpp"

namespace nes
{
	/**
	* 色のテーブルクラス
	*/
	class ColorTable : public DrawableObject
	{
		friend SingletonProvider<ColorTable>;

		s3d::Size patchSize;
		std::array<Rect, 0x40> colorRects;
		

		// コンストラクタ ---------------------------------------------------

		ColorTable(const s3d::Size& patchSize = s3d::Size(24, 24)) 
			: patchSize(patchSize), DrawableObject() { }

	public:

		// メソッド ---------------------------------------------------

		void Draw() override
		{
			for (CCode i = 0; i < 4; ++i)
			{
				for (CCode j = 0; j < 16; ++j)
				{
					const CCode index = (i << 4) | j;
					const auto& color = ColorCode::GetColor(index);

					colorRects[index]
						.setPos(Point(patchSize.x * j, patchSize.y * i) + Point(position))
						.setSize(patchSize)
						.draw(color)
						.drawFrame(1, s3d::Palette::Gray);
				}
			}
		}

		void Update()
		{
			for (CCode i = 0; i < 0x40; ++i)
			{
				if (colorRects[i].leftClicked())
				{
					// 選択中のパレットに対してメッセージを通知
					Logger << U"Message: leftClicked -> palette";
					PaletteTableProvider::GetInstance().SetColor(ColorCode(i));
				}
			}
		}
	};

	/**
	* 色のテーブルを提供するクラス
	*/
	class ColorTableProvider : public SingletonProvider<ColorTable>	{};
}