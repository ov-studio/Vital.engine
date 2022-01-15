#pragma once
#include "vEngine.h"

class ClientComponent;

class DecalWindow : public wi::gui::Window
{
public:
	void Create(ClientComponent* editor);

	wi::ecs::Entity entity;
	void SetEntity(wi::ecs::Entity entity);

	wi::gui::CheckBox placementCheckBox;
	wi::gui::Label infoLabel;
	wi::gui::TextInputField decalNameField;
};

