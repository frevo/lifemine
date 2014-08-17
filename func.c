#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"lifemine.h"
extern uint8_t COL;
extern uint8_t ROW;
extern uint8_t PLAYERS_CNT;
struct player *playerlist = NULL;
#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAX(a,b) ((a)>(b)?(a):(b))

void initPlayers( uint8_t cnt ){
		int i;
		struct player *tmp;
		atexit( destroyPlayers );
		if( (playerlist =(struct player*) calloc( 1, sizeof(struct player) )) != NULL &&
						(playerlist->cells = (char*) malloc( COL*ROW*sizeof(char) )) != NULL ){
				playerlist->p_count = cnt;
				for( i = 0; i < ROW*COL; ++i )
						playerlist->cells[i] = ' ';
				while( cnt-- ){
						tmp = NULL;
						if((tmp = (struct player*) calloc( 1, sizeof(struct player) ))
										!= NULL && 
										(tmp->cells = (char*) malloc( COL*ROW*sizeof(char) ))
										!= NULL ){
								tmp->next = playerlist->next;
								playerlist->next = tmp;
								tmp->p_name = cnt + 49;
								for( i = 0; i < ROW*COL; ++i )
										tmp->cells[i] = ' ';
						}
						else{
								printf( "Initialization of players failed. Goodbye!\n" );
								exit( -1 );
						}
				}
		}
		else{
				printf( "Initialization of playerlist failed. Goodbye!\n" );
				exit( -1 );
		}
}

void randGenerator( uint16_t *number, uint8_t count, uint16_t from, uint16_t to ){
		uint16_t tmp;
		uint8_t i, j;
		srand( time(NULL) );
		for( i = 0; i < count; ++i ){
rnd:			tmp = rand() % (to-from+1) + from;
				for( j = 0; j < i; ++j )
						if( number[j] == tmp )
								goto rnd;
				number[i] = tmp;
		}
}

void initRandomCells(){
		uint8_t i, j;
		uint8_t cellscnt = MIN( ROW, COL ) / 2;
		struct player *plrtmp = playerlist;
		uint16_t rndtmp[ MIN(ROW, COL) * PLAYERS_CNT ];
		randGenerator( rndtmp, cellscnt*PLAYERS_CNT, 1, ROW*COL );
		for( i = 0; i < PLAYERS_CNT; ++i ){
				plrtmp = plrtmp->next;
				for( j = 0; j < cellscnt; ++j ){
						plrtmp->cells[ rndtmp[i*cellscnt+j] ] = '#';
						playerlist->cells[ rndtmp[i*cellscnt+j] ] = plrtmp->p_name;
				}
		}
}

struct player *getPlayerlist(){
		return playerlist;
}

void rePrint( struct player *plyr ){
		uint8_t i, j;
		printf( "Player%c:\n", plyr->p_name );
		printf( "   " );
		for( i = 1; i <= COL; ++i )
				printf( "%-4d", i );
		printf( "\n" );
		for( i = 1; i <= ROW; ++i ){
				printf( "   +" );
				for( j = 1; j <= COL; ++j )
						printf( "---+" );
				printf( "\n" );
				printf( "%-3d|", i );
				for( j = 1; j <= COL; ++j )
						printf( " %c |", plyr->cells[(i-1)*COL+j-1] );
				printf( "\n" );
		}
		printf( "   +" );
		for( j = 1; j <= COL; ++j )
				printf( "---+" );
		printf( "\n" );
}

uint8_t getPoint( uint8_t *X, uint8_t *Y, char* prompt ){
		uint8_t Xtmp, Ytmp;
		printf( "%s", prompt  );
		if( scanf( "%hhu%hhu", &Xtmp, &Ytmp ) != 2 )
				return 0;
		if( Xtmp > ROW || Ytmp > COL )
				return 0;
		*X = Xtmp;
		*Y = Ytmp;
		return 1;
}

uint8_t getPlayerscount(){
		return playerlist->p_count;
}

uint8_t getPos( uint8_t X, uint8_t Y ){
		if( X == 1 ){
				if( Y == 1 )
						return TOP_LEFT;
				else{
						if( Y == ROW )
								return BOTTOM_LEFT;
						else
								return LEFT_SIDE;
				}
		}
		if( X == COL ){
				if( Y == 1 )
						return TOP_RIGHT;
				else{
						if( Y == ROW )
								return BOTTOM_RIGHT;
						else
								return RIGHT_SIDE;
				}
		}
		if( Y == 1 )
				return TOP_SIDE;
		if( Y == ROW )
				return BOTTOM_SIDE;
		return CENTER_AREA;
}
uint8_t getSquare( char name, uint8_t X, uint8_t Y ){
		uint8_t posflag = getPos( X, Y );
		uint8_t cellscnt = 0;
		if( posflag & LEFT_SIDE )
				cellscnt += isNumber( playerlist->cells[ (X-1)*COL+Y ] )
						&& playerlist->cells[ (X-1)*COL+Y ] != name;
		if( posflag & TOP_SIDE )
				cellscnt += isNumber( playerlist->cells[ X*COL+Y-1 ] )
						&& playerlist->cells[ X*COL+Y-1 ] != name;
		if( posflag & RIGHT_SIDE )
				cellscnt += isNumber( playerlist->cells[ (X-1)*COL+Y-2 ] )
						&& playerlist->cells[ (X-1)*COL+Y-2 ] != name;
		if( posflag & BOTTOM_SIDE )
				cellscnt += isNumber( playerlist->cells[ (X-2)*COL+Y-1 ] )
						&& playerlist->cells[ (X-2)*COL+Y-1 ] != name;
		if( posflag & TOP_LEFT )
				cellscnt += isNumber( playerlist->cells[ X*COL+Y ] )
						&& playerlist->cells[ X*COL+Y ] != name;
		if( posflag & TOP_RIGHT )
				cellscnt += isNumber( playerlist->cells[ X*COL+Y-2 ] )
						&& playerlist->cells[ X*COL+Y-2 ] != name;
		if( posflag & BOTTOM_RIGHT )
				cellscnt += isNumber( playerlist->cells[ (X-2)*COL+Y-2 ] )
						&& playerlist->cells[ (X-2)*COL+Y-2 ] != name;
		if( posflag & BOTTOM_LEFT )
				cellscnt += isNumber( playerlist->cells[ (X-2)*COL+Y ] )
						&& playerlist->cells[ (X-2)*COL+Y ] != name;
		return cellscnt;
}

uint8_t isNumber( char ch ){
		return ( ch >= 48 && ch <= 57 );
}
#if 0
uint8_t updateExplore( struct player *plr, uint8_t X, uint8_t Y ){
		if( isNumber( playerlist->cells[ (X-1)*COL+Y-1 ] ) &&
						(playerlist->cells[ (X-1)*COL+Y-1 ] != plr->p_name) )

				uint8_t othercells = getSquare( plr->p_name, X, Y );
		playerlist->cells[ (X-1)*COL+Y-1 ] = '!';
		plr->cells[ (X-1)*COL+Y-1 ] = othercells + 48;
		return 1;
		else{
				if( playerlist->cells[ (X-1)*COL+Y-1 ] != ' ' ) 
						return 0;
		}
} // not completed
#endif

uint8_t updateOccupy( struct player *plr, uint8_t X, uint8_t Y ){
		if( plr->cells[ (X-1)*COL+Y-1 ] != ' ' )
				return 0;
		plr->cells[ (X-1)*COL+Y-1 ] = '#';
		return 1;
}

void updateAll(){
}

void delPlayers( struct player *plr ){
}

void destroyPlayers(){
		struct player *tmp;
		while( playerlist ){
				tmp = playerlist;
				playerlist = playerlist->next;
				if( tmp->cells )
						free( tmp->cells );
				free( tmp );
		}
}

