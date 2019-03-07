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

		std::array<Palette, 4> palettes;
		s3d::Size patchSize;

		SelectionID selection;

		PaletteTable() 
			: selection(0), patchSize(s3d::Size(24, 24)), DrawableObject() {}

	public:

		void Draw() override
		{
			// for文を2つ書くのはパレットを先に描画しないと、選択したパレットの下線部が上書きされてしまうから
			for (int i = 0; i < 4; ++i)
			{
				FontProvider::GetFont()(i).draw(position.x, position.y + (patchSize.y * i), s3d::Palette::Black);

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
					paletteRect.drawFrame(1, s3d::Palette::Yellow);
			}

		}
	};

	/**
	* パレットのテーブルを提供するクラス
	*/
	class PaletteTableProvider : public SingletonProvider<PaletteTable> {};
}