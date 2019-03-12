#pragma once
#include "DrawableObject.hpp"
#include "SingletonProvider.hpp"
#include "Character.hpp"

namespace nes
{
	/**
	* キャラクターを格納するためのテーブル
	* 256個格納できる
	*/
	class PatternTable : public DrawableObject
	{
		SelectionID selected;

		std::array<Character, 256> characters;

	public:
		PatternTable() : DrawableObject(), selected(1)
		{
			for (int i = 0; i < 256; ++i)
			{
				characters[i] = Character(false, s3d::Size(2, 2));
			}
		}

		void Draw() override
		{
			// キャラクター自体の描画
			for (int h = 0; h < 16; ++h)
			{
				for (int w = 0; w < 16; ++w)
				{
					const int index = h * 16 + w;
					const auto& size = characters[index].GetPatchSize();
					const s3d::Point diff(w, h);
					characters[index].SetPos(position + diff * size * 8).Draw();
				}
			}

			// 選択枠の描画
			const int x = selected % 16;
			const int y = selected / 16;
			const s3d::Point diff(x, y);
			const auto& size = characters[selected].GetPatchSize();
			Rect(position + diff * size * 8, size * 8).drawFrame(1, s3d::Palette::White);
		}

		void Update() override
		{
			// キャラクターの枠で当たり判定
			for (int i = 0; i < 256; ++i)
			{
				const auto& hitchar = characters[i];
				const auto& size = hitchar.GetCharacterSize();
				if (Rect(hitchar.GetPos(), size).leftClicked())
				{
					selected = (SelectionID)i;	// ヒットしたら描画エリアのキャラクターを入れ替える
					DrawAreaProvider::GetInstance().SetCharacter(hitchar);
					break;
				}
			}
		}
	};

	class BGPatternTable : public PatternTable
	{
		friend SingletonProvider<BGPatternTable>;
	};

	class SpritePatternTable : public PatternTable
	{
		friend SingletonProvider<SpritePatternTable>;
	};

	class BGPatternProvider : public SingletonProvider<BGPatternTable> {};

	class SpritePatternProvider : public SingletonProvider<SpritePatternTable> {};
}