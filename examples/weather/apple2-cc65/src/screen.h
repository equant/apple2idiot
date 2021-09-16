/*

Screen handling

*/

/* Initialize screen mode, set title and colors */
void InitScreen(unsigned char *title, unsigned char border, unsigned char bg, unsigned char text);

/* Restore basic screen mode */
void ExitScreen(void);

/* Draw petscii box */
void DrawBox(unsigned char xsize, unsigned char ysize, unsigned char xpos, unsigned char ypos);

/* Clear screen area */
void ClearBox(unsigned char xsize, unsigned char ysize, unsigned char xpos, unsigned char ypos);

/* print maxlen leftmost chars of string */
void PrintLeftString(unsigned char *string, unsigned char maxlen);
