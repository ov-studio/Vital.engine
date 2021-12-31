#pragma once
#include "vEngine.h"

class ClientComponent;

class EnvProbeWindow : public wi::gui::Window
{
public:
	void Create(ClientComponent* editor);

	wi::ecs::Entity entity;
	void SetEntity(wi::ecs::Entity entity);

	wi::gui::CheckBox realTimeCheckBox;
	wi::gui::Button generateButton;
	wi::gui::Button refreshButton;
	wi::gui::Button refreshAllButton;
};

