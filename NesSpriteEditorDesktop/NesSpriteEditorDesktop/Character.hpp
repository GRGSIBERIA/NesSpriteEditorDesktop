#pragma once
#include <array>
#include "Definition.hpp"
#include "DrawableObject.hpp"
#include "PaletteTable.hpp"
//#include "PatternTable.hpp"	// include すると相互参照

namespace nes
{
	/**
	* 8x8ピクセルで表されるキャラクタークラス
	* 描画エリアやパターンテーブルなどで共通で使用する
	*/
	class Character : public DrawableObject
	{
		PaletteID paletteId;				// 使用しているパレットID
		std::array<ColorID, 64> colorIds;	// ドットごとに使用している色ID
		std::array<s3d::Rect, 64> rects;
		s3d::Size patchSize;
		bool enablePixelHitTest;

	public:
		Character(const bool enablePixelHitTest = false, const s3d::Size patchSize = s3d::Size(24, 24)) 
			: enablePixelHitTest(enablePixelHitTest),  patchSize(patchSize), paletteId(0) 
		{
			colorIds.fill(0);
		}

		Character& operator=(const Character& lhs)
		{
			paletteId = lhs.paletteId;
			colorIds = lhs.colorIds;
			rects = lhs.rects;
			patchSize = lhs.patchSize;
			enablePixelHitTest = lhs.enablePixelHitTest;
			return *this;
		}

		// メソッド ---------------------------------------------------

		void Draw() override
		{
			const auto& palette = PaletteTableProvider::GetInstance().GetPalette(paletteId);

			for (PixelID h = 0; h < 8; ++h)
			{
				for (PixelID w = 0; w < 8; ++w)
				{
					const auto id = h * 8 + w;
					const auto& code = palette.GetCode(colorIds[id]);

					const s3d::Point diff(w, h);
					rects[id]
						.setPos(position + diff * patchSize)
						.setSize(patchSize)
						.draw(code.GetColor());
				}
			}
		}

		void Update() override
		{
			if (enablePixelHitTest)	// ピクセルの当たり判定
			{
				paletteId = PaletteTableProvider::GetInstance().GetSelectedPaletteID();

				for (PixelID id = 0; id < 64; ++id)
				{
					if (rects[id].leftPressed())
					{
						// 左クリックされたら色を塗り替える
						colorIds[id] = PaletteTableProvider::GetInstance().GetSelectedColorID();

						// パターンテーブルを参照して該当するテーブルの色をすべて塗り替える
						// ここに書くべきかどうかは怪しい
					}
				}
			}
		}

		// アクセサ ---------------------------------------------------

		const s3d::Size& GetPatchSize() const { return patchSize; }

		const s3d::Size GetCharacterSize() const { return patchSize * 8; }

		Character& Copy(const Character& lhs)
		{
			paletteId = lhs.paletteId;
			colorIds = lhs.colorIds;
			rects = lhs.rects;
			return *this;
		}
	};
}