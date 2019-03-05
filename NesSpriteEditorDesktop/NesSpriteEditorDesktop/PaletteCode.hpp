#pragma once
#include <Siv3D\Color.hpp>

namespace nes
{
	class IndexOutOfRangeException : public std::exception {};

	typedef unsigned char PCode;	// 数値のパレットコード型

	/*
	* パレットコード
	*/
	class PaletteCode
	{
		PCode code;			// 色番号
		s3d::Color color;	// 実際の色

	public:
		// コンストラクタ ---------------------------------------------------

		// @param paletteCode 色コード
		PaletteCode(const PCode paletteCode)
			: code((PCode)paletteCode), color(GetColor((PCode)paletteCode)) {}

		// デフォルトコンストラクタ
		PaletteCode() : code(0), color(GetColor(0)){}

		// オペレータ ---------------------------------------------------

		PaletteCode& operator=(const PaletteCode& rhs) { code = rhs.code; color = rhs.color; }

		// アクセサ ---------------------------------------------------

		const PCode GetCode() const { return code; }

		const s3d::Color& GetColor() const { return color; }

		// 関数など ---------------------------------------------------
		
		/**
		* 色番号に従った実際の色を取得する関数
		*/
		static const s3d::Color& GetColor(const PCode paletteCode)
		{
			static const std::array<s3d::Color, 0x40> ColorMap = {
				s3d::Color(U"#6B6B6B"),
				s3d::Color(U"#001084"),
				s3d::Color(U"#08008C"),
				s3d::Color(U"#42007B"),
				s3d::Color(U"#63005A"),
				s3d::Color(U"#6B0010"),
				s3d::Color(U"#600000"),
				s3d::Color(U"#4F3500"),
				s3d::Color(U"#314E18"),
				s3d::Color(U"#005A21"),
				s3d::Color(U"#215A10"),
				s3d::Color(U"#085242"),
				s3d::Color(U"#003973"),
				s3d::Color(U"#000000"),
				s3d::Color(U"#000000"),
				s3d::Color(U"#000000"),
				s3d::Color(U"#A5A5A5"),
				s3d::Color(U"#0042C6"),
				s3d::Color(U"#4229CE"),
				s3d::Color(U"#6B00BD"),
				s3d::Color(U"#942994"),
				s3d::Color(U"#9C1042"),
				s3d::Color(U"#9C3900"),
				s3d::Color(U"#845E21"),
				s3d::Color(U"#5F7B21"),
				s3d::Color(U"#2D8C29"),
				s3d::Color(U"#188E10"),
				s3d::Color(U"#2E8663"),
				s3d::Color(U"#29739C"),
				s3d::Color(U"#000000"),
				s3d::Color(U"#000000"),
				s3d::Color(U"#000000"),
				s3d::Color(U"#EFEFEF"),
				s3d::Color(U"#5A8CFF"),
				s3d::Color(U"#7B6BFF"),
				s3d::Color(U"#A55AFF"),
				s3d::Color(U"#D64AFF"),
				s3d::Color(U"#E7639C"),
				s3d::Color(U"#DE7B52"),
				s3d::Color(U"#CE9C29"),
				s3d::Color(U"#ADB531"),
				s3d::Color(U"#7BCE31"),
				s3d::Color(U"#5ACE52"),
				s3d::Color(U"#4AC694"),
				s3d::Color(U"#4AB5CE"),
				s3d::Color(U"#525252"),
				s3d::Color(U"#000000"),
				s3d::Color(U"#000000"),
				s3d::Color(U"#EFEFEF"),
				s3d::Color(U"#ADC6FF"),
				s3d::Color(U"#BDBDFF"),
				s3d::Color(U"#CEB5FF"),
				s3d::Color(U"#E7B5FF"),
				s3d::Color(U"#F9BBDF"),
				s3d::Color(U"#F7C6B5"),
				s3d::Color(U"#DEC69C"),
				s3d::Color(U"#D6D694"),
				s3d::Color(U"#C6E79C"),
				s3d::Color(U"#B5E7AD"),
				s3d::Color(U"#ADE7C6"),
				s3d::Color(U"#ADDEE7"),
				s3d::Color(U"#ADADAD"),
				s3d::Color(U"#000000"),
				s3d::Color(U"#000000"),
			};

			return ColorMap[paletteCode];
		}
	};

	
}