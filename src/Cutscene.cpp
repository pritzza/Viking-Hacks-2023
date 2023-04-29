#include "Cutscene.h"

#include "util/Resources.h"

Cutscene::Cutscene(std::vector<std::string> lines)
	:
	dialogueLines{ lines }
{}

void Cutscene::init(Resources& res)
{
	dialogueText.setFont(res.textFont);
	dialogueText.setFillColor(sf::Color::White);
	dialogueText.setCharacterSize(24);
	dialogueText.setPosition({ 100, 100 });
}

void Cutscene::update(float dt)
{
	if (!isOver)
	{
		totalTime += dt;
		textTime += dt;

		bool isDialogueRemaining{ currentLine < dialogueLines.size() };

		if (isDialogueRemaining)
			updateDialogue();
	}
}

void Cutscene::updateDialogue()
{
	const int charsNeeded = textTime * charactersPerSecond;
	const int charsActual = currentText.size();

	int charsToAdd = charsNeeded - charsActual;

	for (int i = 0; i < charsToAdd; ++i)
	{
		int charIndex = currentText.size() + i;

		const std::string& lineInProgress{ dialogueLines[currentLine] };

		if (charIndex < dialogueLines[currentLine].size())
		{
			currentText += lineInProgress.at(charIndex);
		}
	}

	dialogueText.setString(currentText);
}

void Cutscene::draw(sf::RenderWindow& window, sf::View& camera)
{
	window.draw(dialogueText);
}

void Cutscene::nextLine()
{
	currentLine++;
	currentText = "";
	textTime = 0;

	if (currentLine > dialogueLines.size())
		isOver = true;
}