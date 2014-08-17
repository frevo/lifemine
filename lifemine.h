#ifndef LIFEMINE_H
#define LIFEMINE_H
#include<stdio.h>
#include<stdint.h>

struct player{
		struct player *next;		/* next player */
		union{
				uint8_t plrcount;
				struct{ 
						uint16_t count;
						char name;
				} NC;
		} PL;
		char *cells;				/* player cells */
};

#define p_count	PL.plrcount			/* player's count */
#define c_count	PL.NC.count			/* cells' count */
#define p_name	PL.NC.name			/* player's name */

#define LEFT_SIDE		0x01
#define TOP_SIDE		0x02
#define RIGHT_SIDE		0x04
#define BOTTOM_SIDE		0x08
#define TOP_LEFT		0x10	|LEFT_SIDE	|TOP_SIDE
#define TOP_RIGHT		0x20	|TOP_SIDE	|RIGHT_SIDE
#define BOTTOM_RIGHT	0x40	|RIGHT_SIDE	|BOTTOM_SIDE
#define BOTTOM_LEFT		0x80	|BOTTOM_SIDE|LEFT_SIDE
#define CENTER_AREA		0xff

void initPlayers( uint8_t );										/* intialize players with count of PLAYERS_CNT */
void randGenerator( uint16_t*, uint8_t, uint16_t, uint16_t );		/* generate unique random numbers */
void initRandomCells();												/* initialize the cells of each player */
void rePrint( struct player* );										/* print players' cells */
void delPlayers( struct player* );									/* delete players */
void destroyPlayers();												/* destroy all players before exit */
void updateAll();
uint8_t updateExplore( struct player*, uint8_t, uint8_t );			/* update the point explored */
uint8_t updateOccupy( struct player*, uint8_t, uint8_t );			/* update the point occupied */
uint8_t getPoint( uint8_t*, uint8_t*, char* );						/* get the point of players' input */
uint8_t getPos( uint8_t X, uint8_t Y );
uint8_t getSquare( char, uint8_t, uint8_t );
uint8_t getPlayerscount();											/* get the current players' count */
uint8_t isNumber( char );
struct player *getPlayerlist();										/* get the playerlist pointer */


#endif
