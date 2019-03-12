#pragma once
#include <array>
#include "Definition.hpp"
#include "DrawableObject.hpp"
#include "PaletteTable.hpp"

namespace nes
{
	class Character : public DrawableObject
	{
		PaletteID paletteId;				// 使用しているパレットID
		std::array<ColorID, 64> colorIds;	// ドットごとに使用している色ID
		std::array<s3d::Rect, 64> rects;
		s3d::Size patchSize;
		const bool enablePixelHitTest;

	public:
		Character(const bool enablePixelHitTest = false, const s3d::Size patchSize = s3d::Size(24, 24)) 
			: enablePixelHitTest(enablePixelHitTest),  patchSize(patchSize), paletteId(0) 
		{
			colorIds.fill(0);
		}

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
			// ピクセルの当たり判定
			if (enablePixelHitTest)
			{
				for (PixelID id = 0; id < 64; ++id)
				{
					if (rects[id].leftPressed())
					{
						colorIds[id] = PaletteTableProvider::GetInstance().GetSelectedColorID();
					}
				}
			}
		}
	};
}