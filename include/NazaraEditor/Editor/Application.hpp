#pragma once

#include <NazaraEditor/Core.hpp>

namespace NzEditor
{
	class Application
		: public Nz::EditorBaseApplication
	{
	public:
		Application();

		virtual bool NewLevel() override;
	};
}