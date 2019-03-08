#pragma once
#include "PaletteCode.hpp"
#include "DrawableObject.hpp"
#include "SelectionTable.hpp"
#include "Brush.hpp"

namespace nes
{
	/**
	* 4色セットのパレット
	*/
	class Palette : public DrawableObject, public SelectionTable
	{
		std::array<PaletteCode, 4> codes;
		s3d::Size patchSize = s3d::Size(24, 24);

	public:
		// コンストラクタ ---------------------------------------------------
		
		Palette()
			:	codes({ PaletteCode(0), PaletteCode(0), PaletteCode(0), PaletteCode(0)}), 
				DrawableObject(), SelectionTable({ KeyQ, KeyW, KeyE, KeyR }) {}

		// アクセサ ---------------------------------------------------

		const PaletteCode& GetCode(const int index) const { return codes[index]; }

		const PaletteCode& GetCode() const { return codes[selected]; }

		void SetCode(const int index, const PCode p) { codes[index] = PaletteCode(p); }

		void SetCode(const int index, const PaletteCode& p) { codes[index] = p; }

		void SetSize(const s3d::Size& size) { patchSize = size; }

		// メソッド ---------------------------------------------------

		void Draw() override
		{
			for (int i = 0; i < 4; ++i)
			{
				// 矩形の描画
				rects[i]
					.setPos(position.x + patchSize.x * i, position.y)
					.setSize(patchSize)
					.draw(codes[i].GetColor())
					.drawFrame(1, s3d::Palette::Darkgray);
			}
		}

		void Update()
		{
			for (SelectionID i = 0; i < 4; ++i)
			{
				if (JudgeClick() != NO_SELECT || JudgeKeys() != NO_SELECT)
				{
					BrushProvider::GetInstance().SetBrush(GetCode());
				}
			}
		}
	};
}