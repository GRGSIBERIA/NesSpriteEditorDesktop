#pragma once
#include "ColorCode.hpp"
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
		std::array<ColorCode, 4> codes;
		s3d::Size patchSize = s3d::Size(24, 24);

	public:
		// コンストラクタ ---------------------------------------------------
		
		Palette()
			:	codes({ ColorCode(0), ColorCode(0), ColorCode(0), ColorCode(0)}), 
				DrawableObject(), SelectionTable({ KeyQ, KeyW, KeyE, KeyR }) {}

		// アクセサ ---------------------------------------------------

		const ColorCode& GetCode(const int index) const { return codes[index]; }

		const ColorCode& GetCode() const { return codes[selected]; }

		void SetCode(const int index, const CCode p) { codes[index] = ColorCode(p); }

		void SetCode(const int index, const ColorCode& p) { codes[index] = p; }

		void SetCode(const ColorCode& p) { codes[selected] = p; }

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