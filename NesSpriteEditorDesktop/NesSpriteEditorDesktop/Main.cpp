
#include <Siv3D.hpp> // OpenSiv3D v0.3.1
#include "ColorTable.hpp"
#include "PaletteTable.hpp"
#include "DrawArea.hpp"

void Main()
{
	Graphics::SetBackground(Color(U"#E2E2E2"));

	const Font font(60);

	nes::BrushProvider::GetInstance();	// 生成しておかないとまずい

	nes::ColorTable& colorTable = nes::ColorTableProvider::GetInstance();
	nes::PaletteTable& paletteTable = nes::PaletteTableProvider::GetInstance();
	nes::DrawArea& drawArea = nes::DrawAreaProvider::GetInstance();
	
	colorTable.SetPos(Point(4, 4));
	paletteTable.SetPos(Point(4, 24 * 4 + 12));
	drawArea.SetPos(Point(24 * 8, 24 * 7));

	while (System::Update())
	{
		colorTable.Update();
		paletteTable.Update();
		drawArea.Update();

		colorTable.Draw();
		paletteTable.Draw();
		drawArea.Draw();

		Circle(Cursor::Pos(), 10).draw(ColorF(1, 0, 0, 0.5));
	}
}
