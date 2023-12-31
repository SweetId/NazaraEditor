#include <NazaraEditor/Core/UI/Window.hpp>

#include <entt/entt.hpp>

namespace NzEditor
{
	class InspectorWindow
		: public Nz::EditorWindow
	{
	public:
		InspectorWindow(Nz::EditorBaseApplication* app);

		virtual void OnEditorGUI() override;

	protected:
		void OnEntitySelected(entt::handle entity);
		void OnEntityDeselected(entt::handle);

		entt::handle m_currentEntity;
	};
}