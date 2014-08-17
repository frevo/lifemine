#include<stdio.h>
#include<stdlib.h>
#include"lifemine.h"
const uint8_t COL = 10;
const uint8_t ROW = 10;
const uint8_t PLAYERS_CNT = 2;		/* 0 < players < 10 */
int main(){
		char arr[COL*ROW];
		int i;
		int X, Y;
		struct player *plst = getPlayerlist();
		for( i = 0; i < COL*ROW; ++i )
				arr[i] = ' ';
		initPlayers( PLAYERS_CNT );
		atexit( destroyPlayers );
		initRandomCells();
#if 0
		while( getPlayerscount() > 1 ){
				plst = plst->next;
				rePrint( plst );
				while( getPoint( &X, &Y, "please input the point you want to put your cell: " )
								&& updateOccupy( plst, X, Y ) );
				updateAll();
				rePrint( plst );
				while( getPoint( &X, &Y, "please input the point you want to explore: " )
								&& updateExplore( plst, X, Y ) );
				rePrint( plst );
				updateAll();
		}
#endif
		rePrint( getPlayerlist()->next );
		rePrint( getPlayerlist() );
		printf( "Player%c survived!\n", getPlayerlist()->next->p_name );
		exit( 0 );
}
