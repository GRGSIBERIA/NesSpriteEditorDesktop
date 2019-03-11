#pragma once
#include <Siv3D\Rectangle.hpp>

namespace nes
{
	typedef unsigned char SelectionID;

	const SelectionID NO_SELECT = 0xFFFF;

	/**
	* 選択可能なテーブルクラス
	*/
	class SelectionTable
	{
	private:
		std::array<s3d::Key, 4> keys;

	protected:
		SelectionID selected = 0;
		std::array<s3d::Rect, 4> rects;

		const SelectionID JudgeClick()
		{
			for (SelectionID i = 0; i < 4; ++i)
			{
				if (rects[i].leftClicked()) {
					selected = i;
					return selected;
				}
			}
			return NO_SELECT;
		}

		const SelectionID JudgeKeys()
		{
			for (SelectionID i = 0; i < 4; ++i)
			{
				if (keys[i].pressed()) {
					selected = i;
					return selected;
				}
			}
			return NO_SELECT;
		}

	public:
		SelectionTable(const std::array<s3d::Key, 4>& keys) : keys(keys) {}

		/**
		* @return 現在選択中のIDを返す
		*/
		const SelectionID GetSelected() const { return selected; }
	};
}