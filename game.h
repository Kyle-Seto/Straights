#ifndef __GAME_H__
#define __GAME_H__

#include "players.h"

class Player;
class Table;
class Game{
	std::vector<std::shared_ptr<Player>> players;
	Table table;
	std::shared_ptr<Hand> legalPlays;
	int whoseMove;
	std::unique_ptr<Deck> deck;
public:
	Game(Deck deck);

	bool gameOn();

	std::shared_ptr<Card> playTurn();
	void updateLegalTurns(std::shared_ptr<Card> x);

	void updateScores();
	void setupStart();

	void loadDeck(Deck x);

	void addHuman();

	void addComputer();

	void invitePlayers();

	void dealDeck();

	void printWinners();

	void print(std::ostream &out) const;
};

#endif

