#pragma once

#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

struct Entity;
struct Resources;

// how to use class
// must be dynamcally allocated with keyword new
// must be given lines of dialogue at construction
// init must be called on it thereafter
// 
// TODO: implement camera following spotlight entity,
//		 showing sprite of speaker, and transitional camera movement,
//		 also going from one cutscene to another
struct Cutscene
{
	Entity* speaker{ nullptr };
	Entity* spotlight{ nullptr };

	Cutscene* nextScene = nullptr;

	std::vector<std::string> dialogueLines;
	int currentLine{ 0 };
	sf::Text dialogueText;

	std::string currentText;

	bool isOver{ false };

	float charactersPerSecond{ 20.f };
	float totalTime{ 0 };
	float textTime{ 0 };

	Cutscene(std::vector<std::string> lines);

	void nextLine();

	void init(Resources& res);

	void update(float dt);
	void updateDialogue();

	void draw(sf::RenderWindow& window, sf::View& camera);

};