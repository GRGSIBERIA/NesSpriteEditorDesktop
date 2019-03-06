
#include <Siv3D.hpp> // OpenSiv3D v0.3.1
#include "ColorTable.hpp"

void Main()
{
	Graphics::SetBackground(Color(U"#F2F2F2"));

	const Font font(60);

	nes::ColorTable& table = nes::ColorTableProvider::GetInstance();
	
	while (System::Update())
	{
		table.Draw(Point(0, 0));

		Circle(Cursor::Pos(), 60).draw(ColorF(1, 0, 0, 0.5));
	}
}
