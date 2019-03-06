
#include <Siv3D.hpp> // OpenSiv3D v0.3.1
#include "ColorTable.hpp"
#include "PaletteTable.hpp"

void Main()
{
	Graphics::SetBackground(Color(U"#E2E2E2"));

	const Font font(60);

	nes::ColorTable& colorTable = nes::ColorTableProvider::GetInstance();
	nes::PaletteTable& paletteTable = nes::PaletteTableProvider::GetInstance();
	
	paletteTable.SetPos(Point(0, 24 * 4));

	while (System::Update())
	{
		colorTable.Update();

		colorTable.Draw();
		paletteTable.Draw();

		Circle(Cursor::Pos(), 60).draw(ColorF(1, 0, 0, 0.5));
	}
}
