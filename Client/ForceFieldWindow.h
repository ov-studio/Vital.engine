#pragma once
#include "vEngine.h"

class ClientComponent;

class ForceFieldWindow : public wi::gui::Window
{
public:
	void Create(ClientComponent* editor);

	wi::ecs::Entity entity;
	void SetEntity(wi::ecs::Entity entity);

	wi::gui::ComboBox typeComboBox;
	wi::gui::Slider gravitySlider;
	wi::gui::Slider rangeSlider;
	wi::gui::Button addButton;
};

