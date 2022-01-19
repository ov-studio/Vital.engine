#pragma once

namespace wi::lua
{
	//update lua scripts which are waiting for a fixed game tick
	void AsyncUpdate();

	//update lua scripts which are waiting for a game tick
	void Update();

	//issue lua drawing commands which are waiting for a render tick
	void Render();
};

