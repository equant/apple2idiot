10000  REM  WRITE WS$ TO WA
10010  FOR N = 0 TO  LEN(WS$) -1
10020 P = WA +N
10030 C$ =  MID$ (WS$,N +1,1)
10040  PRINT C$, ASC(C$)
10050  POKE P, ASC(C$)
10060  NEXT N
10070  POKE P +1,3
10080  RETURN 