100 CA = 49664: REM  CARD ADDRESS 0XCN0
120 AA = CA +1: REM  APPL CMD ADDRESS
140 ESPA = CA: REM  ESP CMD ADDRESS
150 MAXSTR = 20
160 S$ = ""
170  INPUT "ENTER STRING: ";A$
200  FOR N = 0 TO  LEN(A$) -1
210 P = CA +2 +N
215 P = CA +2 +N
220 C$ =  MID$ (A$,N +1,1)
230  PRINT C$, ASC(C$)
240  POKE P, ASC(C$)
350  NEXT N
360  POKE P +1,3