#pragma once

#include <NazaraEditor/Core/Application/Action.hpp>

namespace Nz
{
	class NAZARAEDITOR_CORE_API EditorAction_Quit final
		: public EditorAction
	{
		EDITORACTION_BODY(EditorAction_Quit, false);

	public:
		void Execute() override;
	};
}