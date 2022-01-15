#pragma once
#include "vEngine.h"

class ClientComponent;

class NameWindow : public wi::gui::Window
{
public:
	void Create(ClientComponent* editor);

	wi::ecs::Entity entity;
	void SetEntity(wi::ecs::Entity entity);

	wi::gui::TextInputField nameInput;
};

