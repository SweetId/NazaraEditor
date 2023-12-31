#include <NazaraEditor/Editor/Application.hpp>
#include <NazaraEditor/Editor/UI/AssetsWindow.hpp>
#include <NazaraEditor/Editor/UI/InspectorWindow.hpp>
#include <NazaraEditor/Editor/UI/LevelWindow.hpp>
#include <NazaraEditor/Editor/UI/MainWindow.hpp>
#include <NazaraEditor/Editor/UI/OutputWindow.hpp>
#include <NazaraEditor/Core/Components/CameraComponent.hpp>

#include <Nazara/Graphics/Components/GraphicsComponent.hpp>
#include <Nazara/Graphics/Components/LightComponent.hpp>
#include <Nazara/Graphics/DirectionalLight.hpp>
#include <Nazara/Graphics/GraphicalMesh.hpp>
#include <Nazara/Graphics/Model.hpp>

#include <NazaraLocalization/Localization.hpp>

#include <NazaraEditor/Core/Application/Actions/EditorAction_Camera.hpp>

namespace NzEditor
{
	Application::Application(int argc, char** argv)
		: Nz::EditorBaseApplication(argc, argv)
	{
		RegisterWindow<NzEditor::MainWindow>();
		RegisterWindow<NzEditor::AssetsWindow>();
		RegisterWindow<NzEditor::LevelWindow>();
		RegisterWindow<NzEditor::InspectorWindow>();
		RegisterWindow<NzEditor::OutputWindow>();

		Nz::RegisterLevelActions(*this);
		Nz::RegisterEditorActions(*this);
		Nz::RegisterCameraActions(*this);
		Nz::RegisterLogActions(*this);

		Nz::Localization::OnLocaleInstalled.Connect([this](std::string_view locale) {
			RegisterAction<Nz::EditorAction_SetLocale>({
				.className = std::format("{}_{}", Nz::EditorAction_SetLocale::GetClassName(), locale),
				.description = locale,
				.path = { "LOC_EDITOR_MENU_TOOLS", "LOC_EDITOR_MENU_LANGUAGE", locale },
				.category = "Tools",
			}, locale);
		});
	}

	bool Application::NewLevel()
	{
		bool bResult = EditorBaseApplication::NewLevel();
		if (!bResult)
			return false;

		{
			auto directional = CreateEntity("SunLight");
			Nz::LightComponent& lightComponent = directional.emplace<Nz::LightComponent>();
			Nz::DirectionalLight& light = lightComponent.AddLight<Nz::DirectionalLight>();
			light.UpdateRotation(Nz::Quaternionf::LookAt(Nz::Vector3f(-1, 0, -1), Nz::Vector3f::Up()));
			light.EnableShadowCasting(true);

			{
				auto& cmp = directional.get<Nz::EditorNameComponent>();
				cmp.SetIcon("editor:/icons/light.png");
			}
		}

		for (int i = 0; i < 5; ++i)
		{
			auto cube = CreateEntity(std::format("Cube_{}", i + 1));
			cube.get<Nz::NodeComponent>().SetPosition(Nz::Vector3f(i * 2, 0, i + 1));
			Nz::GraphicsComponent& graphicsComponent = cube.emplace<Nz::GraphicsComponent>();

			std::shared_ptr<Nz::GraphicalMesh> boxMesh = Nz::GraphicalMesh::Build(Nz::Primitive::Box(Nz::Vector3f(1.f), Nz::Vector3ui::Zero(), Nz::Matrix4f::Scale(Nz::Vector3f(1.f)), Nz::Rectf(0.f, 0.f, 2.f, 2.f)));

			std::shared_ptr<Nz::MaterialInstance> boxMat = Nz::MaterialInstance::Instantiate(Nz::MaterialType::Phong);
			
			std::shared_ptr<Nz::Model> boxModel = std::make_shared<Nz::Model>(std::move(boxMesh));
			boxModel->SetMaterial(0, std::move(boxMat));
			graphicsComponent.AttachRenderable(boxModel);
		}

		GetMainCamera().get<Nz::EditorCameraComponent>().SetPosition(Nz::Vector3f(- 5, 0, 0));
		GetMainCamera().get<Nz::EditorCameraComponent>().SetRotation(Nz::Quaternionf::LookAt(Nz::Vector3f(1, 0, 0), Nz::Vector3f::Up()));

		return true;
	}
}