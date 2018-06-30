show_multiples([],_,[]):-!.
show_multiples([H|T], N, T1):- 1 is H mod N, !, show_multiples(T, N, T1).
show_multiples([H|T], N, [H|T1]):- show_multiples(T, N,T1).

:- nl, write('show_multiples'), nl.
:- write(' 2: '), show_multiples([1,2,3,4,5,6,5,4,3,2,1], 2, Lst), write(Lst), nl.
:- write(' 3: '), show_multiples([1,2,3,4,5,6,5,4,3,2,1], 3, Lst), write(Lst), nl.
:- write(' 10: '), show_multiples([1,2,3,4,5,6,5,4,3,2,1], 10, Lst), write(Lst), nl.
