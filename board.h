#define BOARDSTATUS_OK         1
#define BOARDSTATUS_NOK        0
#define N_BOARD                15



int board_initBoard(void);//보드 초기화
void board_printBoardStatus(void);//보드판 상태 출력
int board_getBoardStatus(int pos);//특저어 칸의 파손 여부 출력
int board_getSharkPosition(void);//상어 위치 출력
int board_stepShark(void);//상어 전진 명령
int board_getBoardCoin(int pos);//코인 습득 명령

