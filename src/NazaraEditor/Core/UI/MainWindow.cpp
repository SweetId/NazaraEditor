#include <NazaraEditor/Core/UI/MainWindow.hpp>

#include <imgui.h>

namespace Nz
{
	EditorMainWindow::EditorMainWindow(EditorBaseApplication* app, const Nz::LocalizedText& name, const std::vector<std::string>& categories)
		: EditorWindow(app, name, categories)
	{ }

	void EditorMainWindow::OnRenderImgui()
	{
		if (ImGui::BeginMainMenuBar())
		{
			DrawMenus();

			ImGui::EndMainMenuBar();
		}

		// Create docks everywhere in the main area
		ImGui::DockSpaceOverViewport(nullptr, ImGuiDockNodeFlags_PassthruCentralNode);
	}
}