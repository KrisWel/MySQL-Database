#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "SQLConnector.cpp"
#include "Button.cpp"


class UserPanel {
private:

	sf::Clock clock;
	sf::Time elapsed;
	sf::Font font;
	sf::RectangleShape games, gamers, statistics;
	sf::RectangleShape searchGame, searchPlayer;
	sf::RenderWindow* window;
	SQLConnector* connection;
	sf::Text playerGames;
	sf::Text playerHours;

	std::vector<sf::Text> texts;
	std::vector<Button> buttons;

	bool lSearch, rSearch;
	bool changeGUI;
	bool ifUser;
	bool changeBudget;
	std::string lsSearch, rsSearch;
	std::string userName;
	float budget;
	float lastbuyed;

public:

	UserPanel(sf::RenderWindow* window, SQLConnector* connection) {
		this->connection = connection;
		this->window = window;

		if (!font.loadFromFile("external/arial.ttf"))	std::cout << "Font failed" << std::endl;
		playerHours.setFont(font);
		playerHours.setCharacterSize(20);
		playerHours.setFillColor(sf::Color(211, 239, 222));
		playerHours.setPosition(sf::Vector2f(275.f, 850.f));
		playerGames.setFont(font);
		playerGames.setCharacterSize(20);
		playerGames.setFillColor(sf::Color(211, 239, 222));
		playerGames.setPosition(sf::Vector2f(275.f, 800.f));

		

		games.setSize(sf::Vector2f(500.f, 700.f));
		games.setPosition(sf::Vector2f(0.f, 0.f));
		games.setFillColor(sf::Color(150, 150, 250));
		gamers.setSize(sf::Vector2f(500.f, 700.f));
		gamers.setPosition(sf::Vector2f(500.f, 0.f));
		gamers.setFillColor(sf::Color(200, 200, 200));
		statistics.setSize(sf::Vector2f(1000.f, 300.f));
		statistics.setPosition(sf::Vector2f(0.f, 700.f));
		statistics.setFillColor(sf::Color(120, 120, 200));

		searchGame.setSize(sf::Vector2f(300.f, 50.f));
		searchGame.setPosition(sf::Vector2f(100.f, 20.f));
		searchGame.setFillColor(sf::Color(50, 50, 250));
		searchPlayer.setSize(sf::Vector2f(300.f, 50.f));
		searchPlayer.setPosition(sf::Vector2f(600.f, 20.f));
		searchPlayer.setFillColor(sf::Color(50, 50, 250));

		texts.push_back(sf::Text("Twoje statystyki", font, 20));
		texts[0].setPosition(sf::Vector2f(50.f, 750.f));
		texts.push_back(sf::Text("Ilosc gier: ", font, 20));
		texts[1].setPosition(sf::Vector2f(50.f, 800.f));
		texts.push_back(sf::Text("Ilosc godzin w grach: ", font, 20));
		texts[2].setPosition(sf::Vector2f(50.f, 850.f));
		texts.push_back(sf::Text("Twoj budzet: ", font, 20));
		texts[3].setPosition(sf::Vector2f(50.f, 900.f));
		texts.push_back(sf::Text("wiecej", font, 20));
		texts[4].setPosition(sf::Vector2f(350.f, 800.f));
		texts.push_back(sf::Text("wiecej", font, 20));
		texts[5].setPosition(sf::Vector2f(350.f, 850.f));
		texts.push_back(sf::Text("PLN", font, 20));
		texts[6].setPosition(sf::Vector2f(350.f, 900.f));
		texts.push_back(sf::Text("", font, 25));
		texts[7].setPosition(sf::Vector2f(100.f, 25.f));
		texts.push_back(sf::Text("", font, 25));
		texts[8].setPosition(sf::Vector2f(600.f, 25.f));
		texts.push_back(sf::Text("", font, 20));
		texts[9].setPosition(sf::Vector2f(275.f, 900.f));

		std::vector<std::string> allGames = connection->allGames();
		for (int i = 0; i < allGames.size(); i++) {
			texts.push_back(sf::Text(allGames[i], font, 27));
			texts[texts.size() - 1].setPosition(sf::Vector2f(75.f, 50.f + 50.f * (i+1)));

			int price = connection->getPrice(allGames[i]);
			texts.push_back(sf::Text(std::to_string(price) + " PLN", font, 21));
			texts[texts.size() - 1].setPosition(sf::Vector2f(400.f, 50.f + 50.f * (i + 1)));



			Button* temp = new Button("Kup", window, sf::Vector2f(250.f, 50.f + 50.f * (i + 1)), 25, 0.4f);
			buttons.push_back(*temp);
			
			

			if (i >= 9) break;
		}

		std::vector<std::string> allPlayers = connection->allPlayers();
		for (int i = 0; i < allPlayers.size(); i++) {
			texts.push_back(sf::Text(allPlayers[i], font, 25));
			texts[texts.size() - 1].setPosition(sf::Vector2f(575.f, 50.f + 50.f * (i + 1)));
			if (i >= 9) break;
		}

		texts.push_back(sf::Text("Twoje osiagniecia:", font, 25));
		texts[texts.size() - 1].setPosition(sf::Vector2f(650.f, 700.f));
		

		for (auto& text : texts) {
			text.setFillColor(sf::Color(211, 239, 222));
		}

		
		
		changeGUI = false;
		lSearch = false;
		rSearch = false;
		ifUser = false;
		changeBudget = false;
		lsSearch = "";
		rsSearch = "";
		userName = "";

		lastbuyed = -1.f;
		budget = 0.f;

		

		
	}

	void update() {


		if (!userName.empty() && changeBudget) {
			std::vector<std::string> tempp = connection->getPlayerAchivments(userName);
			int count = 0;
			for (auto& it : tempp) {
				texts.push_back(sf::Text(it, font, 25));
				texts[texts.size() - 1].setPosition(sf::Vector2f(650.f, 750.f + 50.f * (count + 1)));
			}

			budget = connection->userBudget(userName);
			std::string temp = std::to_string(budget);
			temp.pop_back(); temp.pop_back(); temp.pop_back(); temp.pop_back();
			texts[9].setString(temp);
			changeBudget = false;
			std::string nrGames = connection->getPlayerNrGames(userName);
			playerGames.setString(nrGames);
			if (std::stoi(nrGames) >= 1)
				playerHours.setString(connection->getPlayerHours(userName));
			else
				playerHours.setString("0");

			std::vector<std::string> userGames = connection->userGames(userName);
			for (auto & game : userGames) {
				for (auto& text : texts) {
					if (text.getString() == game) {
						for (auto& button : buttons) {
							if (button.getPosit().y == text.getPosition().y) {
								button.setText("Graj");
							}
						}
					}
				}
			}
		}


		window->draw(games);
		window->draw(gamers);
		window->draw(statistics);
		//window->draw(searchGame);
		//window->draw(searchPlayer);
		window->draw(playerHours);
		window->draw(playerGames);

		for (auto& text : texts) {
			window->draw(text);
		}

		if (searchGame.getGlobalBounds().contains((sf::Vector2f)sf::Mouse::getPosition(*window))
			&& sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			lSearch = true;
			rSearch = false;
		}
		if (searchPlayer.getGlobalBounds().contains((sf::Vector2f)sf::Mouse::getPosition(*window))
			&& sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			lSearch = false;
			rSearch = true;
		}
		if (texts[4].getGlobalBounds().contains((sf::Vector2f)sf::Mouse::getPosition(*window))) {
			//texts[4].setFillColor(sf::Color(176, 157, 185));
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				changeGUI = true;
			}
		}
		if (texts[5].getGlobalBounds().contains((sf::Vector2f)sf::Mouse::getPosition(*window))) {
			//texts[5].setFillColor(sf::Color(176, 157, 185));
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				changeGUI = true;
			}
		}

		elapsed = clock.getElapsedTime();
		//std::cout << elapsed.asSeconds() << std::endl;
		
		for (auto& button : buttons) {
			button.update();
			if (button.ifPressed()) {
				for (auto& text : texts) {
					if (text.getPosition().y == button.getPosit().y) {
						if (text.getCharacterSize() == 21 && button.getText() != "Graj" && button.getText() != "Grasz!") {
							std::string priceOfGame = text.getString();
							budget -= std::stof(priceOfGame);
							if (budget >= 0.f) {
								lastbuyed = text.getPosition().y;
								button.setText("Graj");
								std::string temp = std::to_string(budget);
								temp.pop_back(); temp.pop_back(); temp.pop_back(); temp.pop_back();
								texts[9].setString(temp);
								connection->changeBudget(budget, userName);
								elapsed = clock.restart();
							}
						}
						if (text.getCharacterSize() == 27 && lastbuyed == text.getPosition().y) {
							connection->buyGame(text.getString(), userName);
							if (playerGames.getString() == "0") {
								connection->setFirstAchievment(userName);
								std::vector<std::string> temp = connection->getPlayerAchivments(userName);
								int count = 0;
								for (auto& it : temp) {
									texts.push_back(sf::Text(it, font, 25));
									texts[texts.size() - 1].setPosition(sf::Vector2f(650.f, 750.f + 50.f * (count + 1)));
								}
							}
							elapsed = clock.restart();
							lastbuyed = -1.f;
							playerGames.setString(connection->getPlayerNrGames(userName));
						}

						if (text.getCharacterSize() == 27 && button.getText() == "Graj" && elapsed.asSeconds() >= 3.f) {
							button.setText("Grasz!");
							elapsed = clock.restart();
						}
						else if (text.getCharacterSize() == 27 && button.getText() == "Grasz!" && elapsed.asSeconds() >= 3.f) {
							float time = elapsed.asSeconds();
							time /= 10.f;
							if (time >= 1.f) {
								connection->addHoursToPlayer(std::to_string((int)time), userName, (std::string)text.getString());
								connection->addHoursToStatistics(text.getString());
								playerHours.setString(connection->getPlayerHours(userName));
							}
							button.setText("Graj");
							elapsed = clock.restart();
						}
					}
				}
				button.ofPressed();
			}
		}

		if (lSearch && !lsSearch.empty()) {
			//
		}
		if (rSearch && !rsSearch.empty()) {
			//
		}

	}

	void setTexts(char t, int box) {
		if (box == 0) {
			if (t == '-' && !lsSearch.empty()) {
				lsSearch.pop_back();
				texts[7].setString(lsSearch);
			}
			else {
				lsSearch += t;
				texts[7].setString(lsSearch);
			}
		}
		else if (box == 1) {
			if (t == '-' && !rsSearch.empty()) {
				rsSearch.pop_back();
				texts[8].setString(rsSearch);
			}
			else {
				rsSearch += t;
				texts[8].setString(rsSearch);
			}
		}
	}

	bool iflSearch() { return lSearch; }
	bool ifrSearch() { return rSearch; }
	bool ifChangeGUI() { return changeGUI; }
	bool ifGetUserName() { return ifUser; }
	void setGUI(bool gui) { changeGUI = gui; }
	void setUserName(std::string userName) { this->userName = userName; ifUser = true; changeBudget = true; }
	std::string getUserName() { return userName; }
	float getUserBudget() {return budget;}

};