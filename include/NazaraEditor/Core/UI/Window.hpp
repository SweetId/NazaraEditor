#pragma once

#include <NazaraEditor/Core/Config.hpp>
#include <NazaraImgui/ImguiHandler.hpp>
#include <NazaraLocalization/LocalizedText.hpp>

#include <functional>

namespace Nz
{
	using ActionCallback = std::function<void(void)>;

	class EditorBaseApplication;
	class Texture;

	class NAZARAEDITOR_CORE_API EditorWindow
		: private Nz::ImguiHandler
	{
	public:
		EditorWindow(EditorBaseApplication* app, const Nz::LocalizedText& name, const std::vector<std::string>& categories = {});
		virtual ~EditorWindow();

		EditorWindow(const EditorWindow&) = delete;
		EditorWindow& operator=(const EditorWindow&) = delete;

		virtual void OnRenderImgui() override;

		void AddMenuAction(const std::vector<Nz::LocalizedText>& path, const std::string& shortcut, ActionCallback callback, const std::shared_ptr<Nz::Texture>& icon = {});
		void AddMenuSeparator(const std::vector<Nz::LocalizedText>& path);

		EditorBaseApplication* GetApplication() { return m_application; }
		const EditorBaseApplication* GetApplication() const { return m_application; }

		bool HasMenuCategory(const std::string& category) const;

	protected:
		void DrawMenus();

		virtual void OnEditorGUI() {};

	private:

		EditorBaseApplication* m_application;
		Nz::LocalizedText m_windowName;
		std::vector<std::string> m_categories;

		struct MenuAction
		{
			Nz::LocalizedText label;
			std::string shortcut;
			std::shared_ptr<Nz::Texture> icon;
			ActionCallback callback;
		};

		struct MenuSeparator
		{};

		struct MenuList
		{
			Nz::LocalizedText label;
			std::vector<std::variant<MenuAction, MenuSeparator, MenuList>> entries;
		};

		MenuList m_root;

		MenuList& GetOrCreateMenuHierarchy(const std::vector<Nz::LocalizedText>& hierarchy);
	};
}