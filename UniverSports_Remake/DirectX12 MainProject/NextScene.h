#pragma once

enum class NextScene : int {
	Continue = 0,
	TitleScene,
	LobbyScene,
	MainScene,
	ResultScene,
	StartScene = TitleScene
};