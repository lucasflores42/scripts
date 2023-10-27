
/*******************************************************
*                                                      *
*    ezgfx v1.0  -  written in 21/04/2000 by adlroc    *
*                                                      *
*******************************************************/


int ezOpenWin(int Width, int Height, char *wname);
void ezPlot(int x, int y, int c);
void ezLine(int x1, int y1, int x2, int y2, int c);
void ezCls(void);
void ezBox(int x1, int y1, int x2, int y2, int c);
void ezBoxF(int x1, int y1, int x2, int y2, int c);
void ezEllipse(int x, int y, int rx, int ry, int c);
void ezEllipseF(int x, int y, int rx, int ry, int c);
void ezCopyArea(int x1, int y1, int x2, int y2, int destx, int desty);
void ezText(int x, int y, int c, char *text);
void ezFlush(void);
int ezCheckKey(void);
void ezClearKeyBuf(void);
int ezCheckMouse(void);
void ezClearMouseBuf(void);
void ezChangeWindowTitle(char *wname);
void ezClose(void);
void ezErrorMsg(void);
extern int ezMouseX, ezMouseY;




