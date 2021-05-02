#ifndef __CARD_H__
#define __CARD_H__
#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <memory>

class Card {
protected:
	int suit; //1:Clubs, 2:Diamonds, 3:Hearts, 4:Spades
	int rank; //1,2,3,...,11,12,13
public:
	Card(int suit, int rank);
	int getSuit() const ;
	int getRank() const;
	void print(std::ostream &out) const;
	bool operator == (const Card &Ref) const;
	Card& operator ++ ();
	Card& operator -- ();
};

bool ptrCardCompare(std::shared_ptr<Card> l,  std::shared_ptr<Card> r);


class Hand {
protected:
	std::vector<std::shared_ptr<Card>> deck;
public:
	std::vector<std::shared_ptr<Card>> getDeck() const ;
	void addCard(std::shared_ptr<Card> x) ;
	void removeCard(std::shared_ptr<Card> x);
	std::shared_ptr<Card> hasCard(Card x);

	void deckSort();
	
	bool operator == (const Hand &Ref) const ;
	virtual void print(std::ostream &out) const;	
};

class Deck : public Hand{
	std::default_random_engine rng;
public:
	void populateDeck();
	void setRng(std::default_random_engine rng);
	void shuffle();
	void print(std::ostream &out) const;
};

class Table : public Hand{
	std::vector<int> clubs;
	std::vector<int> diamonds;
	std::vector<int> hearts;
	std::vector<int> spades;
public:
	bool startCardPlayed;
	void setHands();
	void print(std::ostream &out) const;
};

#endif

