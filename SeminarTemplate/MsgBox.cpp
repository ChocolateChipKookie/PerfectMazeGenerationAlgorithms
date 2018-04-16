#include "stdafx.h"
#include "MsgBox.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

MsgBox::MsgBox(std::string message, std::string msgBoxName, bool openMsgBox)
{
	font.loadFromFile("arial.ttf");

	this->message = message;
	this->windowName = msgBoxName;

	if(openMsgBox)
	{
		makeMsgBox();
	}
}

void MsgBox::newMsgBox(std::string message, std::string msgBoxName)
{
	MsgBox msgBox(message, msgBoxName, true);
}

int MsgBox::makeMsgBox()
{
	sf::RenderWindow msgBoxWin(sf::VideoMode(windowSize.x, windowSize.y), windowName);

	sf::Text text(message.c_str(), font);
	text.setCharacterSize(fontSize);
	text.setStyle(sf::Text::Regular);
	text.setFillColor(sf::Color::Black);

	text.setPosition(	static_cast<float>(windowSize.x - text.getGlobalBounds().width) / 2,
						static_cast<float>(windowSize.y - text.getGlobalBounds().height) / 2);

	msgBoxWin.clear(sf::Color::White);
	msgBoxWin.draw(text);
	msgBoxWin.display();

	while (msgBoxWin.isOpen())
	{
		sf::Event event;
		while (msgBoxWin.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				msgBoxWin.close();
			}
		}
	}

	return 0;
}

void MsgBox::setWindowName(std::string newWindowName)
{
	windowName = newWindowName;
}

std::string MsgBox::getWindowName()
{
	return windowName;
}

void MsgBox::setMessage(std::string newMessage)
{
	message = newMessage;
}

std::string MsgBox::getMessage()
{
	return message;
}

void MsgBox::setFont(std::string newFontName)
{
	sf::Font help;

	if(help.loadFromFile(newFontName.c_str()))
	{
		font = help;
	}
}

sf::Font MsgBox::getFont()
{
	return font;
}
