#include "game.h"

const Card STARTINGCARD{4,7}; //Starting card is 7 of Spades

Game::Game(Deck deck){
	std::vector<std::shared_ptr<Player>> players;
	Hand legalPlays;
	Table table;
	this->players = players;
	this->table = table;
	this->legalPlays = std::make_shared<Hand>(legalPlays);
	this->whoseMove = 0;
	this->deck = std::make_unique<Deck>(deck);
}

bool Game::gameOn(){
	for (int i=0; i<4; ++i){
		if (players[i]->getScore() >= 80) {return false;}
	}
	return true;
}

std::shared_ptr<Card> Game::playTurn(){
	players[whoseMove]->setLegalPlays(legalPlays);
	table.print(std::cout);
	players[whoseMove]->print(std::cout);
	std::cout << std::endl;
	std::shared_ptr<Card> x = players[whoseMove]->playMove(whoseMove + 1, *deck);
	if (x != nullptr) {
		if (legalPlays->hasCard(*x)) {
			table.addCard(x);
			table.setHands();
		}
	} else {
		//Rage quit the player
		players[whoseMove] = std::make_shared<Computer>(*players[whoseMove]);
		std::shared_ptr<Card> x = players[whoseMove]->playMove(whoseMove + 1, *deck);
		if (legalPlays->hasCard(*x)) {
			table.addCard(x);
			table.setHands();
		}
		whoseMove++;
		whoseMove = whoseMove % 4;
		return x;
	}
	whoseMove++;
	whoseMove = whoseMove % 4;
	return x;
}
void Game::updateLegalTurns(std::shared_ptr<Card> x) {
	if (table.hasCard(*x)) {
		if (*x == STARTINGCARD) {
			Card c{1,7};
			Card d{2,7};
			Card h{3,7};
			legalPlays->addCard(deck->hasCard(c));
			legalPlays->addCard(deck->hasCard(d));
			legalPlays->addCard(deck->hasCard(h));
		}
		legalPlays->removeCard(x);
		if (x->getRank() != 13) {
			Card u = ++*x;
			--*x;
			if (x->getRank() >= 7 && x->getRank() != 13) {
				legalPlays->addCard(deck->hasCard(u));	
			}
		} else {
			Card u = *x;
			if (x->getRank() >= 7 && x->getRank() != 13) {
				legalPlays->addCard(deck->hasCard(u));
			}
		}
		if (x->getRank() != 1) {
			Card d = --*x;
			++*x;
			if (x->getRank() <= 7 && x->getRank() != 1){
				legalPlays->addCard(deck->hasCard(d));
			} 
		} else {
			Card d = *x;
			if (x->getRank() <= 7 && x->getRank() != 1){
				legalPlays->addCard(deck->hasCard(d));
			} 
		}			
	}
}



void Game::updateScores(){
	for (int i = 0; i < 4; ++i){
		std::cout << "Player" << i + 1 << "\'s discards:";
		players[i]->getDiscards().print(std::cout);
		std::cout << std::endl << "Player" << i + 1 << "\'s score: ";
		players[i]->updateScore(); 
		
	}
}
void Game::setupStart(){
	Hand legalPlays;
	Hand discard1, discard2, discard3, discard4;
	Table table;
	this->legalPlays = std::make_shared<Hand>(legalPlays);
	this->table = table;
	players[0]->discards = discard1;
	players[1]->discards = discard2;
	players[2]->discards = discard3;
	players[3]->discards = discard4;
	for (unsigned i=0; i < players.size(); i++) {
		if (players[i]->getHand().hasCard(STARTINGCARD)){
			whoseMove = i;
		}
	}
	this->legalPlays->addCard(deck->hasCard(STARTINGCARD));
	table.startCardPlayed = false;
	std::cout << "A new round begins. It’s Player" << whoseMove + 1 << "’s turn to play." << std::endl;
}

void Game::loadDeck(Deck x){
	this->deck = std::make_unique<Deck>(x);
}

void Game::addHuman(){
	Human x;
	auto y = std::make_shared<Human>(x); 
	this->players.push_back(std::move(y));		
}

void Game::addComputer(){
	Computer x;
	auto y = std::make_shared<Computer>(x); 
	this->players.push_back(std::move(y));		
}

void Game::invitePlayers(){
	char c;
	for (int i = 1; i <= 4; ++i){
		std::cout << "Is player" << i << " a human (h) or a computer (c)?" << std::endl;
		std::cin >> c;
		if (c == 'h') {
			this->addHuman();
		} else if (c == 'c'){
			this->addComputer();
		}
	}
}

void Game::dealDeck(){
	int i = 0; //Which player to deal
	for (unsigned n = 0; n < deck->getDeck().size(); ++n) {
		players[i]->giveCard(deck->getDeck()[n]);
		i = (n+1)/13;
	}
}

void Game::printWinners(){
	bool win [4] = {true, true, true, true};
	for (int i = 0; i < 4; ++i) {
		int s1 = players[i]->getScore();
		int s2 = players[(i + 1) % 4]->getScore();
		int s3 = players[(i + 2) % 4]->getScore();
		int s4 = players[(i + 3) % 4]->getScore();
		if (s1 > s2 || s1 > s3 || s1 > s4) {
			win[i] = false;
		} 
	}
	for (int i=0; i<4; ++i) {
		if (win[i]) {
			std::cout << "Player" << i+1 <<" wins!" << std::endl;
		}
	}		
}

void Game::print(std::ostream &out) const{
	out << std::endl << "Players:" << std::endl;
	for (unsigned i = 0; i < players.size(); ++i) {
		players[i]->print(out);
	}
	out << std::endl << "Table:" << std::endl;
	table.print(out);
	out << std::endl << "Legal Plays:" << std::endl;
	legalPlays->print(out);
	out << std::endl << "Deck:" << std::endl;
	deck->print(out);
	out << std::endl << "Whose Move:" << whoseMove << std::endl;
}

