#pragma once
#include "vEngine.h"

class EditorComponent;

class NameWindow : public wi::gui::Window
{
public:
	void Create(EditorComponent* editor);

	wi::ecs::Entity entity;
	void SetEntity(wi::ecs::Entity entity);

	wi::gui::TextInputField nameInput;
};

