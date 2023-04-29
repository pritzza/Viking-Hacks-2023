#pragma once


#include "Cutscene.h"
#include "Entity.h"
#include "Stage.h"

#include "util/Resources.h"
#include "util/Window.h"

class Application final
{
public:
	Application(
		const uint16_t width,
		const uint16_t height, 
		const uint8_t frameRate, 
		const std::string& name
	);

	void start();
	void stop();

private:
	Window m_window;
	sf::View view;

	Resources res;

	Cutscene* cutscene{ nullptr };

	Entity player{ createPlayer(res) };
	std::vector<Entity> entities;

	// LOOK AT CONSTRUCTOR OF Stage IN Stage.cpp FOR CHARACTER MAPPINGS
	const std::string STAGE_1_DATA{
		R"(
		i....................................................................................................................................................ddddddddddd
		i....................................................................................................................................................ddddddddddd
		i....................................................................................................................................................ddddddddddd
		i....................................................................................................................................................ddddddddddd
		i....................................................................................................................................................ddddddddddd
		i....................................................................................................................................................ddddddddddd
		i....................................................................................................................................................ddddddddddd
		i....................................................................................................................................................ddddddddddd
		i........................gggggggggggg................................................................................................................ddddddddddd
		i........................dddddddddddd..............................................................ggggggggggggggggggggggggggggggggggggggggggggggggggddddddddddd
		i........................dddddddddddd.............................................................dddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddd
		i........................dddddddddddd.............................................................dddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddd
		i........................dddddddddddd..................................................ggggg.......ddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddd
		i......................................................................................ddddd.......ddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddd
		gggggggg................................................ggg............................ddddd.......ddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddd
		ddddddddg...........................................ggggddd........................................ddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddd
		dddddddddg..........................................ddddddd........................................ddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddd
		ddddddddddg.........................................ddddddd..........gg...........................dddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddd
		dddddddddddgggggggggggggggggggggggggggg...gggggggggggggggggggggg.....dd.....gg...gggggggggggggggggggdddddddddddddddddddddddddddddddddddddddddddddddddddddddddddd
		ddddddddddddddddddddddddddddddddddddddd...dddddddddddddddddddddd.....dd.....dd...ddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddd
		ddddddddddddddddgdddgdddddddddddddddddd...dddddddddddddddddddddd.....dd.....dd...ddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddd
		dddddddddddddgdddddddddgddddddddddddddd...dddddddddddddddddddddd.....dd.....dd...ddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddd
		ddddddddddddddgggggggggdddddddddddddddd...dddddddddddddddddddddd.....dd.....dd...ddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddd
		dddddddddddddddddddddddddddddddddddddddpppddddddddddddddddddddddpppppddppppppdpppddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddd
		)"
	};
	//widthxheightxlevel data
    Stage stage{ 160, 24, STAGE_1_DATA, res };

	int frame{};

	const uint8_t m_frameRate;

	bool m_isRunning{ false };

private:
	void init();

	void applicationLoop();

	void handleInput();
	void update(float dt);
	void render();
};