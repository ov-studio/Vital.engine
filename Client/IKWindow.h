#pragma once
#include "vEngine.h"

class ClientComponent;

class IKWindow : public wi::gui::Window
{
public:
	void Create(ClientComponent* editor);

	wi::ecs::Entity entity;
	void SetEntity(wi::ecs::Entity entity);

	wi::gui::Button createButton;
	wi::gui::ComboBox targetCombo;
	wi::gui::CheckBox disabledCheckBox;
	wi::gui::Slider chainLengthSlider;
	wi::gui::Slider iterationCountSlider;
};

