#pragma once
#include "vEngine.h"

class EditorComponent;

class LayerWindow : public wi::gui::Window
{
public:
	void Create(EditorComponent* editor);

	wi::ecs::Entity entity;
	void SetEntity(wi::ecs::Entity entity);

	wi::gui::Label label;
	wi::gui::CheckBox layers[32];
	wi::gui::Button enableAllButton;
	wi::gui::Button enableNoneButton;
};
