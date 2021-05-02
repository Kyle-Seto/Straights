#include "players.h"

Player::Player(){
	Hand hand, discards, legalPlays;
	this->hand = hand;
	this->discards = discards;
	this->legalPlays = std::make_shared<Hand>(legalPlays);
	this->score = 0;
}
Hand Player::getHand() const{
	return hand;
}
Hand Player::getDiscards() const{
	return discards;
}
int Player::getScore() const{
	return score;
}
void Player::setLegalPlays(std::shared_ptr<Hand> LegalPlays){
	Hand lPlays;
	this->legalPlays = std::make_shared<Hand>(lPlays);
	for (unsigned int i = 0; i < hand.getDeck().size(); ++i){
		if (LegalPlays->hasCard(*hand.getDeck()[i])){
			legalPlays->addCard(hand.getDeck()[i]);				
		}
	}
}
void Player::updateScore(){
	int roundScore = 0;
	for (unsigned int i = 0; i < discards.getDeck().size(); ++i){
		roundScore += discards.getDeck()[i]->getRank();
	}
	std::cout << score << " + " << roundScore << " = " << score + roundScore << std::endl;
	score += roundScore;
}

void Player::giveCard(std::shared_ptr<Card> x){
	hand.addCard(x);
}

void Player::print(std::ostream &out) const{
	out << "Your hand: ";
	hand.print(out);
	out << std::endl << "Legal plays: ";
	legalPlays->print(out);
}

std::shared_ptr<Card> Player::playMove(int id, Deck x){return legalPlays->getDeck()[0];}

bool Player::operator == (const Player &Ref) const {
	return((this->hand == Ref.getHand() && this->discards == Ref.getDiscards() && this->score == Ref.getScore()));
}


std::shared_ptr<Card> Human::playMove(int id, Deck x) {
	std::string cmd;
	while (std::cin >> cmd) {
		if (cmd == "play") {
			std::string card;
			std::cin >> card;
			int suit, rank;
			if (card[0] == '1') {
				rank = 1;
			} else if (card[0] == '2') {
				rank = 2;
			} else if (card[0] == '3') {
				rank = 3;
			} else if (card[0] == '4') {
				rank = 4;
			} else if (card[0] == '5') {
				rank = 5;
			} else if (card[0] == '6') {
				rank = 6;
			} else if (card[0] == '7') {
				rank = 7;
			} else if (card[0] == '8') {
				rank = 8;
			} else if (card[0] == '9') {
				rank = 9;
			} else if (card[0] == 'T') {
				rank = 10;
			} else if (card[0] == 'J') {
				rank = 11;
			} else if (card[0] == 'Q') {
				rank = 12;
			} else if (card[0] == 'K') {
				rank = 13;
			}

			if (card[1] == 'C') {
				suit = 1;
			} else if (card[1] == 'D') {
				suit = 2;			
			} else if (card[1] == 'H') {
				suit = 3;			
			} else if (card[1] == 'S') {
				suit = 4;			
			}
			Card c{suit, rank};
			if (legalPlays->hasCard(c)){
				std::cout << "Player " << id << " plays ";
				c.print(std::cout);
				std::cout << std::endl;
				hand.removeCard(legalPlays->hasCard(c));
				return legalPlays->hasCard(c);
			} else {
				std::cout << "This is not a legal play." << std::endl;
			}
		} else if (cmd == "discard") {
			std::string card;
			std::cin >> card;
			int suit, rank;
			if (card[0] == '1') {
				rank = 1;
			} else if (card[0] == '2') {
				rank = 2;
			} else if (card[0] == '3') {
				rank = 3;
			} else if (card[0] == '4') {
				rank = 4;
			} else if (card[0] == '5') {
				rank = 5;
			} else if (card[0] == '6') {
				rank = 6;
			} else if (card[0] == '7') {
				rank = 7;
			} else if (card[0] == '8') {
				rank = 8;
			} else if (card[0] == '9') {
				rank = 9;
			} else if (card[0] == 'T') {
				rank = 10;
			} else if (card[0] == 'J') {
				rank = 11;
			} else if (card[0] == 'Q') {
				rank = 12;
			} else if (card[0] == 'K') {
				rank = 13;
			}

			if (card[1] == 'C') {
				suit = 1;
			} else if (card[1] == 'D') {
				suit = 2;			
			} else if (card[1] == 'H') {
				suit = 3;			
			} else if (card[1] == 'S') {
				suit = 4;			
			}
			Card c{suit, rank};
			if (legalPlays->getDeck().size() != 0){
				std::cout << "You have a legal play. You may not discard." << std::endl;
			} else {
				std::cout << "Player " << id << " discards ";
				c.print(std::cout);
				std::cout << std::endl;
				hand.removeCard(x.hasCard(c));
				return x.hasCard(c);;
			}
		} else if (cmd == "deck") {
			x.print(std::cout);	
		} else if (cmd == "quit") {
			throw(cmd);		
		} else if (cmd == "ragequit") {
			return nullptr;
		}
	}
	return legalPlays->getDeck()[0];
}


Computer::Computer (const Player &obj) {
	this->hand = obj.hand;
	this->discards = obj.discards;
	this->legalPlays = obj.legalPlays;
	this->score = obj.score;
}

std::shared_ptr<Card> Computer::playMove(int id, Deck x) {
	if (legalPlays->getDeck().size() > 0){
		std::shared_ptr<Card> x;
		x = legalPlays->getDeck()[0];
		std::cout << "Player" << id << " plays ";
		x->print(std::cout);
		std::cout << "." << std::endl;
		hand.removeCard(x);
		return x;
	} else {
		std::cout << "Player" << id << " discards ";
		std::shared_ptr<Card> x;
		x = hand.getDeck()[0];
		x->print(std::cout); 
		std::cout << "." << std::endl;
		discards.addCard(x);
		hand.removeCard(x);
		return x;
	}
}

