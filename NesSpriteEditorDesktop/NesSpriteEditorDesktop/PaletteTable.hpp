#pragma once
#include <Siv3D\Rectangle.hpp>
#include "SingletonProvider.hpp"
#include "Palette.hpp"
#include "DrawableObject.hpp"
#include "FontProvider.hpp"

namespace nes
{
	/**
	* パレットのテーブルクラス
	*/
	class PaletteTable : public DrawableObject
	{
		friend SingletonProvider<PaletteTable>;
		typedef unsigned int SelectionID;

		const std::array<s3d::Key, 4> rowKeys = { Key1, Key2, Key3, Key4 };
		const std::array<std::u32string, 4> columnString = { U"Q", U"W", U"E", U"R" };
		const std::array<std::u32string, 4> rowString = { U"1", U"2", U"3", U"4" };

		std::array<Palette, 4> palettes;
		s3d::Size patchSize;

		SelectionID selection;

		PaletteTable() 
			: selection(0), patchSize(s3d::Size(24, 24)), DrawableObject() {}

	public:

		void Draw() override
		{
			const auto& font = FontProvider::GetFont();

			// for文を2つ書くのはパレットを先に描画しないと、選択したパレットの下線部が上書きされてしまうから
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
				const Rect paletteRect(position + posDiff, s3d::Size(patchSize.x * 4, patchSize.y));

				if (paletteRect.leftClicked())
					selection = i;

				if (selection == (PCode)i)
					paletteRect.drawFrame(1, s3d::Palette::Darkred);
			}

			// 下に表示する文字列を描画
			for (int i = 0; i < 4; ++i)
			{
				const s3d::Point ydiff(patchSize.x * (i + 1) + 6, patchSize.y * 4);
				font(columnString[i]).draw(position + ydiff, s3d::Palette::Black);
			}
		}

		void Update()
		{
			for (SelectionID i = 0; i < 4; ++i)
				if (rowKeys[i].pressed()) selection = i;
		}
	};

	/**
	* パレットのテーブルを提供するクラス
	*/
	class PaletteTableProvider : public SingletonProvider<PaletteTable> {};
}