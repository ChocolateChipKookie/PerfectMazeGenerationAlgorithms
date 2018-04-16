#pragma once
#include <string>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>
#include <thread>

class MsgBox
{
public:
	MsgBox(std::string message, std::string msgBoxName = "MessageBox", bool openMsgBox = true);
	
	static  void newMsgBox(std::string message, std::string msgBoxName = "MessageBox");

	const int fontSize{20};
	const sf::Vector2f windowSize{ 500.f, 200.f };

	int makeMsgBox();

	void setWindowName(std::string newWindowName);
	std::string getWindowName();

	void setMessage(std::string newMessage);
	std::string getMessage();

	void setFont(std::string newFontName);
	sf::Font getFont();


private:
	sf::Font font;

	std::string message;
	std::string windowName;
};
