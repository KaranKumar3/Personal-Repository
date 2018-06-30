quad(X,Y) :- Y is 4 * X.

bloop(X,Y) :- X>0 ->  Y is 2 * X; Y is X /2.

mult(X,Y,Z) :- Z is X * Y.

bigger(X,Y,Z) :- X > Y ->  Z = X; Z = Y.

absol(X,Y) :- Y is abs(X).