#pragma once
#include <Siv3D\Rectangle.hpp>
#include "SingletonProvider.hpp"
#include "DrawableObject.hpp"
#include "Character.hpp"
#include <string>

namespace nes
{
	class DrawArea : public DrawableObject
	{
		friend SingletonProvider<DrawArea>;

		Character character;
		std::array<std::u32string, 8> coordChar = { U"0", U"1", U"2", U"3", U"4", U"5", U"6", U"7" };
		

	public:
		DrawArea() : character(true), DrawableObject() 
		{
			character.SetPos(position);
		}

		void Draw() override
		{
			// 描画エリアの描画
			character.Draw();

			const auto& font = FontProvider::GetFont();
			const auto& size = character.GetPatchSize();

			for (PixelID h = 0; h < 8; ++h)
			{
				const s3d::Point pos(size.x * h + 8, -size.y);
				font(h).draw(position + pos, s3d::Palette::Black);
			}

			for (PixelID w = 0; w < 8; ++w)
			{
				const s3d::Point pos(-size.x, size.y * w);
				font(w).draw(position + pos, s3d::Palette::Black);
			}
		}

		void Update() override
		{
			character.Update();
		}

		DrawableObject& SetPos(const s3d::Point& pos) override 
		{ 
			position = pos;
			character.SetPos(pos);
			return *this; 
		}

		void SetCharacter(const Character& lhs)
		{
			character.Copy(lhs);
		}
	};

	class DrawAreaProvider : public SingletonProvider<DrawArea> {};
}