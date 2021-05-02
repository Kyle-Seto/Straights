#include "cards.h"

Card::Card(int suit, int rank) {
	this->suit = suit;
	this->rank = rank;
}
int Card::getSuit() const{
	return suit;
}
int Card::getRank() const{
	return rank;
}
void Card::print(std::ostream &out) const{
	if (rank <= 9) {
		out << rank;
	} else if (rank == 10) {
		out << "T";
	} else if (rank == 11) {
		out << "J";
	} else if (rank == 12) {
		out << "Q";
	} else if (rank == 13) {
		out << "K";
	}

	if (suit == 1) {
		out << "C";
	} else if (suit == 2) {
		out << "D";			
	} else if (suit == 3) {
		out << "H";			
	} else if (suit == 4) {
		out << "S";			
	}
}
bool Card::operator == (const Card &Ref) const {
	return((this->suit == Ref.getSuit()) && this->rank == Ref.getRank());
}
Card& Card::operator ++ (){
	if (rank != 13) {
		rank++;
	}
	return *this;
}
Card& Card::operator -- (){
	if (rank != 1) {
		rank--;
	}
	return *this;
}

bool ptrCardCompare(std::shared_ptr<Card> l,  std::shared_ptr<Card> r){
	return l->getRank() < r->getRank();
}


std::vector<std::shared_ptr<Card>> Hand::getDeck() const{
	return deck;
}
void Hand::addCard(std::shared_ptr<Card> x) {
	this->deck.push_back(x);
}
void Hand::removeCard(std::shared_ptr<Card> x){
	deck.erase(std::remove(deck.begin(), deck.end(), x), deck.end());
}
std::shared_ptr<Card> Hand::hasCard(Card x){
	auto first = this->deck.begin();
	auto last = this->deck.end();
	while (first!=last) {
		if (**first==x) return *first;
		++first;
	}
	return nullptr;
}

void Hand::deckSort(){
	std::sort(deck.begin(),deck.end(),ptrCardCompare);
}

bool Hand::operator == (const Hand &Ref) const {
	return(this->deck == Ref.getDeck());
}
void Hand::print(std::ostream &out) const{
	for (unsigned i = 0; i < deck.size(); ++i) {
		out << " ";
		deck[i]->print(out);
	}
}


void Deck::populateDeck() {
	for (int suit = 1; suit <= 4; ++suit) {
		for (int rank = 1; rank <= 13; ++rank) {
			Card a{suit, rank};
			auto x = std::make_shared<Card>(a);
			this->deck.push_back(std::move(x));
		}
	}		
}
void Deck::setRng(std::default_random_engine rng) {
	this->rng = rng;
}
void Deck::shuffle(){
	std::shuffle(this->deck.begin(), this->deck.end(), this->rng);
}
void Deck::print(std::ostream &out) const {
	for (unsigned i = 0; i < deck.size(); ++i) {
		if (i % 13 == 0 && i != 0) {
			out << std::endl;
		}
		deck[i]->print(out);
		out << " ";
	}
	out << std::endl;
}

void Table::setHands() {
	clubs.erase(clubs.begin(),clubs.end());
	diamonds.erase(diamonds.begin(),diamonds.end());
	hearts.erase(hearts.begin(),hearts.end());
	spades.erase(spades.begin(),spades.end());
	this->deckSort();
	for (unsigned i = 0; i < deck.size(); ++i) {
		if (deck[i]->getSuit() == 1) {
			clubs.emplace_back(deck[i]->getRank());								
		} else if (deck[i]->getSuit() == 2) {
			diamonds.emplace_back(deck[i]->getRank());							
		} else if (deck[i]->getSuit() == 3) {
			hearts.emplace_back(deck[i]->getRank());							
		} else if (deck[i]->getSuit() == 4) {
			spades.emplace_back(deck[i]->getRank());							
		}
	}
}
void Table::print(std::ostream &out) const {
	out << "Cards on the table:" << std::endl;
	out << "Clubs:";
	for (int i = 0; i < clubs.size(); ++i){
		if (clubs[i] == 1){
			out << " 1";
		} else if (clubs[i] == 2){
			out << " 2";
		} else if (clubs[i] == 3){
			out << " 3";
		} else if (clubs[i] == 4){
			out << " 4";
		} else if (clubs[i] == 5){
			out << " 5";
		} else if (clubs[i] == 6){
			out << " 6";
		} else if (clubs[i] == 7){
			out << " 7";
		} else if (clubs[i] == 8){
			out << " 8";
		} else if (clubs[i] == 9){
			out << " 9";
		} else if (clubs[i] == 10){
			out << " T";
		} else if (clubs[i] == 11){
			out << " J";
		} else if (clubs[i] == 12){
			out << " Q";
		} else if (clubs[i] == 13){
			out << " K";
		}
	}
	out << std::endl << "Diamonds:";
	for (int i = 0; i < diamonds.size(); ++i){
		if (diamonds[i] == 1){
			out << " 1";
		} else if (diamonds[i] == 2){
			out << " 2";
		} else if (diamonds[i] == 3){
			out << " 3";
		} else if (diamonds[i] == 4){
			out << " 4";
		} else if (diamonds[i] == 5){
			out << " 5";
		} else if (diamonds[i] == 6){
			out << " 6";
		} else if (diamonds[i] == 7){
			out << " 7";
		} else if (diamonds[i] == 8){
			out << " 8";
		} else if (diamonds[i] == 9){
			out << " 9";
		} else if (diamonds[i] == 10){
			out << " T";
		} else if (diamonds[i] == 11){
			out << " J";
		} else if (diamonds[i] == 12){
			out << " Q";
		} else if (diamonds[i] == 13){
			out << " K";
		}
	}
	out << std::endl << "Hearts:";
	for (int i = 0; i < hearts.size(); ++i){
		if (hearts[i] == 1){
			out << " 1";
		} else if (hearts[i] == 2){
			out << " 2";
		} else if (hearts[i] == 3){
			out << " 3";
		} else if (hearts[i] == 4){
			out << " 4";
		} else if (hearts[i] == 5){
			out << " 5";
		} else if (hearts[i] == 6){
			out << " 6";
		} else if (hearts[i] == 7){
			out << " 7";
		} else if (hearts[i] == 8){
			out << " 8";
		} else if (hearts[i] == 9){
			out << " 9";
		} else if (hearts[i] == 10){
			out << " T";
		} else if (hearts[i] == 11){
			out << " J";
		} else if (hearts[i] == 12){
			out << " Q";
		} else if (hearts[i] == 13){
			out << " K";
		}
	}
	out << std::endl << "Spades:";
	for (int i = 0; i < spades.size(); ++i){
		if (spades[i] == 1){
			out << " 1";
		} else if (spades[i] == 2){
			out << " 2";
		} else if (spades[i] == 3){
			out << " 3";
		} else if (spades[i] == 4){
			out << " 4";
		} else if (spades[i] == 5){
			out << " 5";
		} else if (spades[i] == 6){
			out << " 6";
		} else if (spades[i] == 7){
			out << " 7";
		} else if (spades[i] == 8){
			out << " 8";
		} else if (spades[i] == 9){
			out << " 9";
		} else if (spades[i] == 10){
			out << " T";
		} else if (spades[i] == 11){
			out << " J";
		} else if (spades[i] == 12){
			out << " Q";
		} else if (spades[i] == 13){
			out << " K";
		}
	}
	out << std::endl;
}

