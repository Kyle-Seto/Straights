#ifndef __PLAYERS_H__
#define __PLAYERS_H__

#include <iostream>
#include "cards.h"

class Player{
public:
	Hand hand;
	Hand discards;
	std::shared_ptr<Hand> legalPlays;
	int score;

	Player();
	Hand getHand() const;
	Hand getDiscards() const;
	int getScore() const;
	void setLegalPlays(std::shared_ptr<Hand> LegalPlays);
	void updateScore();

	void giveCard(std::shared_ptr<Card> x);

	void print(std::ostream &out) const;
		
	virtual std::shared_ptr<Card> playMove(int id, Deck x);

	bool operator == (const Player &Ref) const ;
};

class Human : public Player{
public:
	std::shared_ptr<Card> playMove(int id, Deck x) override;
};

class Computer : public Player{
public:
	Computer () = default;
	Computer (const Player &obj);
	std::shared_ptr<Card> playMove(int id, Deck x) override;
};

#endif

