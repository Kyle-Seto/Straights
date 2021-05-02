#include "game.h"
#include <iostream>
#include <chrono>
using namespace std; 

int main( int argc, char * argv[] ) {
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    if ( argc > 1 ) {
        try {
            seed = stoi( string{ argv[1] } );
    	} catch( invalid_argument & e ) {
            cerr << e.what() << endl;
        	return 1;
        } catch( out_of_range & e ) {
        	cerr << e.what() << endl;
            return -1;
	    }
	}
    default_random_engine rng{seed};
	extern ostream cout;
		
	try {
		Deck x;
		Game g{x};
		//setup
		x.populateDeck();
		x.setRng(rng);
		g.invitePlayers();

		while (g.gameOn()) {
			x.shuffle();
			g.loadDeck(x);
			g.dealDeck();
			g.setupStart();
			for (int i = 0; i < 52; ++i) {
				g.updateLegalTurns(g.playTurn());
					//if g.playTurn() is on table, 
						// if x == high increase high and add lplays
						// if x == low decrease low and add lplays
						// remove x from legal plays
			}
			g.updateScores();	
		}
		g.printWinners();
		return 0;
	} catch(string s){
		return 1;
	}
}

