#pragma once
#include "DrawableObject.hpp"
#include "SingletonProvider.hpp"
#include "Character.hpp"
#include "FontProvider.hpp"

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
					selected = (SelectionID)i;	// 描画エリアのキャラクターを入れ替える
					DrawAreaProvider::GetInstance().SetCharacter(hitchar);
					break;
				}
			}
		}

		// アクセサ ---------------------------------------------------

		const s3d::Size& GetPatchSize() const { return characters[selected].GetPatchSize(); }
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




	/**
	* パターンテーブルの種類単位で切り替えられるクラス
	* ボタン等が押されたらBGとスプライトで表示を切り替えられる仕様が望ましい
	* BGとスプライトで機能の拡張は行わないので共通して使用できる
	*/
	class PatternTableSelector : public SingletonProvider<PatternTableSelector>, public DrawableObject
	{
		// 基本的にそれぞれ1つずつ存在しなければならないので個別のクラスに分けた
		BGPatternTable* bg;
		SpritePatternTable* sprite;

		PatternTable* selector;

	public:
		PatternTableSelector() 
			: 
			bg(&BGPatternProvider::GetInstance()), sprite(&SpritePatternProvider::GetInstance()),
			DrawableObject()
		{
			selector = sprite;
		}

		/**
		* bgもしくはspriteの表示を入れ替える
		*/
		PatternTable& Toggle()
		{
			// 三項演算子の変換がうまくいかない
			if (selector == sprite)
				selector = bg;
			else
				selector = sprite;

			return *selector;
		}

		void Draw() override
		{
			selector->Draw();

			// 現在表示中のパターンテーブルの種類を描画する
			const auto& size = selector->GetPatchSize();
			const s3d::Point diff(0, size.y);
			const int mag = 13;
			if (selector == sprite)
				FontProvider::GetFont()(U"Spriter Pattern").draw(position - diff * mag, s3d::Palette::Black);
			else
				FontProvider::GetFont()(U"BG Pattern Table").draw(position - diff * mag, s3d::Palette::Black);
		}

		void Update() override
		{
			selector->Update();
		}

		// アクセサ ---------------------------------------------------

		/**
		* 現在表示されているテーブルを返す
		*/
		PatternTable& GetShownTable() const
		{
			return *selector;
		}

		DrawableObject& SetPos(const s3d::Point& pos) override 
		{ 
			position = pos;
			bg->SetPos(position);
			sprite->SetPos(position);
			return *this; 
		}

		DrawableObject& SetPos(const int x, const int y) override
		{
			position = s3d::Point(x, y);
			bg->SetPos(position);
			sprite->SetPos(position);
			return *this;
		}
	};
}