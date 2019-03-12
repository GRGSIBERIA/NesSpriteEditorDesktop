
#include <Siv3D.hpp> // OpenSiv3D v0.3.1
#include "ColorTable.hpp"
#include "PaletteTable.hpp"
#include "DrawArea.hpp"
#include "PatternTable.hpp"

void Main()
{
	Graphics::SetBackground(Color(U"#E2E2E2"));

	const Font font(60);

	nes::BrushProvider::GetInstance();	// 生成しておかないとまずい

	nes::ColorTable& colorTable = nes::ColorTableProvider::GetInstance();
	nes::PaletteTable& paletteTable = nes::PaletteTableProvider::GetInstance();
	nes::DrawArea& drawArea = nes::DrawAreaProvider::GetInstance();
	nes::SpritePatternTable& spritePatternTable = nes::SpritePatternProvider::GetInstance();
	
	colorTable.SetPos(Point(4, 4));
	paletteTable.SetPos(Point(4, 24 * 4 + 24));
	drawArea.SetPos(Point(24 * 7, 24 * 6));
	spritePatternTable.SetPos(Point(24 * 16, 24 * 6));

	while (System::Update())
	{
		colorTable.Update();
		paletteTable.Update();
		drawArea.Update();
		spritePatternTable.Update();

		colorTable.Draw();
		paletteTable.Draw();
		drawArea.Draw();
		spritePatternTable.Draw();

		Circle(Cursor::Pos(), 10).draw(ColorF(1, 0, 0, 0.5));
	}
}
