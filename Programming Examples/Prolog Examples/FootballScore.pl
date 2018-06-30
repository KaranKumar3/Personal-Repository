fbscore(T, F, S, EX, Total) :- 
		member(T, [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]), 
		member(F, [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]),
		member(S, [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]), 
		member(EX, [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]), 
		
		(EX < T; EX = T), Total is 6*T + 3*F + 2*S + EX.


:- nl, write('fbscore'), nl.
:- fbscore(3, 2, 1, 2, Score), write(['T', 3, 'F', 2, 'S', 1, 'X', 2, 'Score', Score]), nl.
:- fbscore(1, F, 0, X, 10), write(['T', 1, 'F', F, 'S', 0, 'X', X, 'Score', 10]), nl, nl.