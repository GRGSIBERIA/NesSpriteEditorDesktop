#pragma once
#include <Siv3D\Rectangle.hpp>
#include "SingletonProvider.hpp"
#include "ColorCode.hpp"
#include "DrawableObject.hpp"
#include "FontProvider.hpp"
#include "Brush.hpp"

namespace nes
{
	class DrawArea : public DrawableObject
	{
		friend SingletonProvider<DrawArea>;

		const std::array<std::u32string, 16> coord = {
			U"0", U"1", U"2", U"3",
			U"4", U"5", U"6", U"7",
			U"8", U"9", U"A", U"B",
			U"C", U"D", U"E", U"F"
		};

		std::array<s3d::Rect, 64> rects;
		std::array<ColorCode, 64> codes;

		s3d::Size patchSize;

	public:
		DrawArea() : patchSize(24, 24), DrawableObject() {}

		void Draw() override
		{
			// 描画エリアの描画
			for (CCode h = 0; h < 8; ++h)
			{
				for (CCode w = 0; w < 8; ++w)
				{
					const CCode i = h * 8 + w;
					const s3d::Point diff(w, h);

					rects[i]
						.setPos(position + diff * patchSize)
						.setSize(patchSize)
						.draw(codes[i].GetColor());
				}
			}

			// 横軸の文字を描画
			for (CCode h = 0; h < 8; ++h)
			{
				const s3d::Point diff(h * patchSize.x + 8, -patchSize.y);
				FontProvider::GetFont()(coord[h]).draw(position + diff, s3d::Palette::Black);
			}

			// 縦軸の文字を描画
			for (CCode v = 0; v < 8; ++v)
			{
				const s3d::Point diff(-patchSize.x + 8, v * patchSize.x);
				FontProvider::GetFont()(coord[v]).draw(position + diff, s3d::Palette::Black);
			}
		}

		void Update() override
		{
			for (CCode i = 0; i < 64; ++i)
			{
				// ブラシの情報を受け取る
				if (rects[i].leftPressed())
				{
					codes[i] = BrushProvider::GetInstance().GetBrush();
				}
			}
		}
	};

	class DrawAreaProvider : public SingletonProvider<DrawArea> {};
}