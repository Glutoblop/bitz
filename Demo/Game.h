#pragma once
#include "Common.h"

#include "GameClasses/States/Test1/GSTest1.h"
#include "GameClasses/States/Test2/GSTest2.h"
#include "GameClasses/States/Test3/GSTest3.h"

class Game : public Bitz::GameLogic::GameCore
{
public:
	Game();
	~Game();

	static Bitz::GFX::GraphicsStates::GS2D * RenderState2d;
	static Bitz::GFX::GraphicsStates::GS3D * RenderState3d;

protected:
	virtual bool Update() override;
	virtual bool Draw() override;
	virtual bool Init() override;
	virtual bool LoadContent() override;
	virtual bool UnloadContent() override;
	virtual bool OnExit() override;

private:
	static std::shared_ptr<Bitz::GameLogic::GameState> GameState_Test;
};
