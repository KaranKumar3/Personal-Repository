check_it(X,Y,A):- X>Y, A is X-Y.
check_it(X,Y,A):- X is Y, A is Y.
check_it(X,Y,A):- X<Y, A is Y+X.

:- write('check_it '), nl. 
:- check_it(5, 15, A), write(' (5,15): '), write(A), nl.
:- check_it(15, 5, B), write(' (15,5): '), write(B), nl.
:- check_it(5, 5, C), write(' (5,5): '), write(C), nl.