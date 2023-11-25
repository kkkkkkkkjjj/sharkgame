#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "board.h"//main.c에서 board.h 호출하려고

#define MAX_CHARNAME  200
#define N_PLAYER      3
#define MAX_DIE       6

#define N_COINPOS     12
#define MAX_COIN      4

#define PLAYERSTATUS_LIVE   0
#define PLAYERSTATUS_DIE    1
#define PLAYERSTATUS_END    2


int player_position[N_PLAYER];
char player_name[N_PLAYER][MAX_CHARNAME];
int player_coin[N_PLAYER];
int player_status[N_PLAYER];
char player_statusString[3][MAX_CHARNAME] = {"LIVE","DIE","END"};





void opening(void)
{
    printf("===============\n");
    printf("***************\n");
    printf("sharkislandgame!\n");
    printf("***************\n");
    printf("===============\n");
}

int rolldie(void)
{
    return rand()%MAX_DIE+1;
}

void printPlayerPosition(int player)
{
    int i;
    for (i=0;i<N_PLAYER;i++)
    {
        printf("|");
        if (i == player_position[player])
          printf("%c", player_name[player][0]);
        else 
        {
            if (board_getBoardStatus(i))
               printf("X");
            else
               printf(" ");
            
        }
    }
    printf("|\n");
}
        
void printPlayerStatus(void)
{
    int i;
    printf("player status ---\n");
    for (i=0;i<N_PLAYER;i++)
    {
        printf("player name :%s ,pos: %i, coin : %i, status : %s\n", 
        player_name[i],player_position[i],player_coin[i],player_statusString[player_status[i]]);
    }
}

void checkDie(void)
{
    int i;
    for (i=0;i<N_PLAYER;i++)
        if (board_getBoardStatus(player_position[i])== BOARDSTATUS_NOK)
           player_status[i]= PLAYERSTATUS_DIE;
}

int game_end()
{
    int i;
    int flag_end = 1;

    for (i=0;i<N_PLAYER;i++)
    {  
        if (player_status[i] == PLAYERSTATUS_LIVE)
      {
        flag_end = 0;
        break;
      }
    }
 return flag_end;
}

int getAlivePlayer(void)
{
    int i;
    int cnt=0;
    for (i=0;i<N_PLAYER;i++)
    {
        if (player_status[i]== PLAYERSTATUS_END)
            cnt++;
    }

    return cnt;
}

int getWinner(void)
{
    int i;
    int winner=0;
    int max_coin= -1;

    for( i=0;i<N_PLAYER;i++)
    {
        if (player_coin[i] > max_coin)
        {
            max_coin = player_coin[i];
            winner = i;
        }
    }

    return winner; 
}


int main(int argc, char *argv[])
{
    int pos = 0;
    int i;
    int turn;
    srand((unsigned)time(NULL));

    opening();//opening 함수 호출
  //step 1. initialization
  ///1-1: board init
    board_initBoard();//보드상태 및 플레이어 상태  초기화
  ///1-2: player init
    for (i = 0;i<N_PLAYER;i++)
    {
         player_position[i] = 0;
         player_coin[i]= 0;
         player_status[i]= PLAYERSTATUS_LIVE;
         
         printf("Player %i's name: ",i);
         scanf("%s",player_name[i]);
    }

  
   //step 2. game loop
    do {
        int step;
        int coinResult;
        char c;

        if(player_status[turn] != PLAYERSTATUS_LIVE)
        {
            turn = (turn +1 )%N_PLAYER;
            continue; 
        }



        board_printBoardStatus();
        for (i=0;i<N_PLAYER;i++)
            printPlayerPosition(i);
        printPlayerStatus();
        
  //2-2 주사위 던지기
    printf("%s turn!", player_name[turn]);
    printf("press any key to roll a die!\n");
    scanf("%c",&c);
    fflush(stdin);
    step = rolldie();        
    
  //2-3  이동

    player_position[turn] += step;
    
    if (player_position[turn] >= N_BOARD)
      player_position[turn]= N_BOARD-1;
    

    if(player_position[turn] == N_BOARD-1)
      player_status[turn]= PLAYERSTATUS_END;
    
  //2-4 동전 줍기
    coinResult = board_getBoardCoin(pos);
    player_coin[turn] += coinResult;
    printf("you get %d coin!\n",player_coin[turn]);




  //2-5 다음 턴
  turn = (turn+1)%N_PLAYER;//wrap around
  //s2-6:if(모든 플레이어가 한번씩 턴)
  if (turn== 0)
    {
         //상어 동작
         int shark_pos = board_stepShark();
         printf("shark moved!\n");
         checkDie();
    }
} while( game_end() == 0);
// step 3: 게임 결과( winner 계산하고 결과 출력)
    getAlivePlayer();
    printf("%d players are alive !",getAlivePlayer());
    getWinner();
    printf("THE WINNER NUMBER IS %d ! ",getWinner());
    
    system("PAUSE");
    return 0;
}