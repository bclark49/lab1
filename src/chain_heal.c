#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <errno.h>

typedef struct node{
	char* name;
	int x, y;
	int cur_PP, max_PP;
	struct node* prev;
} Node;

int load_player( Node* player ){
	int n;
	n = scanf( "%d %d %d %d %ms", &player->x, &player->y, &player->cur_PP, &player->max_PP, &player->name );
	player->prev = NULL;
	return n;
}

void delete_player( Node* player ){
	free( player->name );
	free( player );
}

void erase_game( int player_count, Node** players ){
	Node* player = *players;
	for( int j=0; j <= player_count; j++ ){
		printf( "player: %s at (%d,%d) has %d/%d \n", player->name, player->x, player->y, player->cur_PP, player->max_PP );
		delete_player( player );
		player = player->prev;
	}
}

int main( int argc, char** argv ){

	/* check command line */
	if( argc != 1 ){ fprintf( stderr, "usage: chain_heal < text.txt\n"); exit(1); }
	
	int n, player_count=0;
	Node** players = NULL;		//head of player list
	Node* prev_player = NULL;	//tmp player for initializing prev pointers
	
	printf("%s\n", argv[0] );
	errno = 0;
	/* read players from stdin and store into player array */
	while(1){
		Node* player = (Node*)malloc(sizeof(Node));
		n = load_player( player );
		if( n == 5 ){
			printf( "player: %s at (%d,%d) has %d/%d \n", player->name, player->x, player->y, player->cur_PP, player->max_PP );
		}
		else if( errno != 0 ){
			perror( "scanf" );
			exit(1);
		}	
		else{
			fprintf( stderr, "No matching characters\n" );
		}	
		/* if first player then initialize array else adjust prev pointer */
		if( player_count == 0 ){ /*players = &player;*/ }
		else{ player->prev = prev_player; }
		prev_player = player;
		
		/* break if last player else increment player count */
		if( player_count >= 5 ){ players = &player; break; }
		else{ player_count++; }
	}	

	erase_game( player_count, players );

	return 0;
}
