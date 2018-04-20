#include "Game.h"

using namespace Bitz::Math;
using namespace Bitz::Content;
using namespace Bitz::GFX;

GraphicsStates::GS2D * Game::RenderState2d;
GraphicsStates::GS3D * Game::RenderState3d;

std::shared_ptr<Bitz::GameLogic::GameState> Game::GameState_Test = nullptr;

Game::Game() : Bitz::GameLogic::GameCore("Explore")
{
	ContentManager::Init("Content/", "Content/", "Content/");
	Bitz::Debug::Logging::EnableLogToConsole();
}

Game::~Game()
{
}

bool Game::Update()
{
	return true;
}

bool Game::Draw()
{
	return true;
}

bool Game::Init()
{
	Bitz::Debug::Logging::EnableLogToBlackHole();

	RenderState2d = new GraphicsStates::GS2D();
	RenderState2d->GetActiveCamera()->SetPosition(Vector3F(0, 0, 0));
	RenderState2d->SetActiveBlendState(Bitz::GFX::GraphicsStates::BaseGS::ADDATIVE);

	RenderState3d = new GraphicsStates::GS3D();
	RenderState3d->GetActiveCamera()->SetPosition(Vector3F(0, 0, -30));
	RenderState3d->SetActiveBlendState(Bitz::GFX::GraphicsStates::BaseGS::ALPHA);

	int test = 1;

	switch (test)
	{
	case 0:
		GameState_Test = std::make_shared<GSTest1>();
		break;
	case 1:
		GameState_Test = std::make_shared<GSTest2>();
		break;
	case 2:
		GameState_Test = std::make_shared<GSTest3>();
		break;
	}

	Bitz::GameLogic::GameStateService::StartState(static_cast<Bitz::GameLogic::GameState_Ptr>(GameState_Test));

	return true;
}

bool Game::LoadContent()
{
	Phys_Ground::LoadContent();
	Phys_Crate::LoadContent();
	Orb::LoadContent();
	return true;
}

bool Game::UnloadContent()
{
	Phys_Ground::UnloadContent();
	Phys_Crate::UnloadContent();
	Orb::UnloadContent();
	return true;
}

bool Game::OnExit()
{
	Bitz::GameLogic::GameStateService::EndState(GameState_Test);
	GameState_Test = nullptr;

	return true;
}