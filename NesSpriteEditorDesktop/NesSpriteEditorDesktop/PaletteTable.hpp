#pragma once
#include <Siv3D\Rectangle.hpp>
#include "SingletonProvider.hpp"
#include "Palette.hpp"
#include "DrawableObject.hpp"
#include "FontProvider.hpp"
#include "Brush.hpp"
#include "Definition.hpp"

namespace nes
{
	/**
	* パレットのテーブルクラス
	*/
	class PaletteTable : public DrawableObject, public SelectionTable
	{
		friend SingletonProvider<PaletteTable>;

		const std::array<std::u32string, 4> columnString = { U"Q", U"W", U"E", U"R" };
		const std::array<std::u32string, 4> rowString = { U"1", U"2", U"3", U"4" };

		std::array<Palette, 4> palettes;
		s3d::Size patchSize;

		PaletteTable() 
			: patchSize(s3d::Size(24, 24)), DrawableObject(), SelectionTable({ Key1, Key2, Key3, Key4 }) {}

	public:

		// アクセサ ---------------------------------------------------

		void SetColor(const ColorCode& code) { palettes[selected].SetCode(code); }

		const Palette& GetPalette(const PaletteID id) { return palettes[id]; }

		// メソッド ---------------------------------------------------

		void Draw() override
		{
			const auto& font = FontProvider::GetFont();

			// パレットを先に描画しないと選択したパレットの下線部が上書きされる
			for (int i = 0; i < 4; ++i)
			{
				font(rowString[i]).draw(position.x + 8, position.y + (patchSize.y * i), s3d::Palette::Black);

				const s3d::Point posDiff(patchSize.x, patchSize.y * i);
				palettes[i].SetPos(position + posDiff).Draw();
			}

			for (int i = 0; i < 4; ++i)
			{
				// コンストラクタで初期化するとうまく書けないのでべた書き
				const s3d::Point posDiff(patchSize.x, patchSize.y * i);
				rects[i].setPos(position + posDiff).setSize(s3d::Size(patchSize.x * 4, patchSize.y));

				if (selected == (CCode)i)
					rects[i].drawFrame(1, s3d::Palette::Darkred);
			}

			// 下に表示する文字列を描画
			for (int i = 0; i < 4; ++i)
			{
				const s3d::Point ydiff(patchSize.x * (i + 1) + 6, patchSize.y * 4);
				font(columnString[i]).draw(position + ydiff, s3d::Palette::Black);
			}

			// 選択されている色を明示する
			for (SelectionID i = 0; i < 4; ++i)
			{
				if (selected == (SelectionID)i)
				{
					const s3d::Point diff(patchSize.x * (palettes[i].GetSelected() + 1), patchSize.y * selected);
					Circle(position + diff + (patchSize * 0.5), 3).draw().drawFrame(1, s3d::Palette::Black);
				}
			}
		}

		void Update() override
		{
			if (JudgeClick() != NO_SELECT || JudgeKeys() != NO_SELECT)
				BrushProvider::GetInstance().SetBrush(palettes[selected].GetCode());

			for (SelectionID i = 0; i < 4; ++i)
				palettes[i].Update();
		}
	};

	/**
	* パレットのテーブルを提供するクラス
	*/
	class PaletteTableProvider : public SingletonProvider<PaletteTable> {};
}