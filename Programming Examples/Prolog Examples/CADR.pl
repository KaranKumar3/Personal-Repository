cadr([_, X | _], X) :- !.

:- nl, write('cadr'), nl.
:- cadr([1, 2, 3, 4, 5], C), write(' case 1: '), write(C), nl.
:- cadr([1, 2, 3], C), write(' case 3: '), write(C), nl.
:- cadr([1, 2], C), write(' case 2: '), write(C), nl. 