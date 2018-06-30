#lang scheme
(define  a  2)
(define  b  5)
(define  c  10)

(- (* 5 4) 2)

(+ (* (+ 7 3) 2) 5)

(+ (* b c) a)

(* (+ 8 2) 3)

(newline)
(+ 2 '2)
;('+ 2 3)
'(+ 2 3)
(define a1 a)
(define a2 'a)
(define a3 '(1 2 3 . 4))

(newline)
(define triple
  (lambda (x)
    (* 3 x)))

(triple 3)

(newline)
(define fib
  (lambda (n)
    (cond
      ((<= n 2) 1)
      ((> n 2) (+ (fib (- n 1)) (fib (- n 2)))))))
(fib 5)

(newline)
(define quad
  (lambda (x)
    (* 4 x)))

(quad 3)

(newline)
(define bloop
  (lambda (x)
    (cond
      ((> x 0) (* 2 x))
      ((< x 0) (/ x 2)))))

(bloop 2)
(bloop -2)

(newline)
(define multi
  (lambda (x y)
    (* y x)))
(multi 3 4)

(newline)
(define bigger
  (lambda (x y)
    (cond
      ((> x y) x)
      ((< x y) y))))
(bigger 4 2)
(bigger 2 8)

(newline)
(define absol
  (lambda (x)
    (abs x)))
(absol -8)

(newline)
(define mult-by
  (lambda (1st n)
    (if(null? 1st)
       null
       (cons(*(car 1st) n) (mult-by (cdr 1st) n )))))

(mult-by '(1 2 3 4) 2)
(mult-by '(2) 2)

(newline)
(define dec-all
  (lambda (1st)
    (if(null? 1st)
       null
       (cons(-(car 1st) 1) (dec-all (cdr 1st))))))

(dec-all '(1 2 3 4))
(dec-all '(2))

(newline)
(define clean-list
  (lambda (lst)
    (if (null? lst)
        '()
        (filter number? lst) )))

(clean-list '(list 1 'a + 10 'hello lst '(1 2 3) '(a . b) red 8 6 -3))

(newline)
(define squares
  (lambda (lst)
    (if (null? lst)
        '()
        (cons (* (car (clean-list lst)) (car (clean-list lst))) (squares(cdr (clean-list lst)))) )))

(define sum-squares
  (lambda (lst)
    (apply + (squares lst))))

(sum-squares '(1 2 'symb + - 3 'l ))

(newline)
(define sum-squares2
  (lambda (lst)
    (if (null? lst)
        '()
        (apply + (map (lambda (x) (* x x)) (clean-list lst))) )))

(sum-squares2 '(1 2 'symb + - 3 'l ))
 
(newline)   
(define mult-position
  (lambda (lst)
    (if (null? lst)
        '()
       (map (lambda (x) (* x (list-ref lst (- x 1)) )) lst ) )))


(mult-position '(1 2 3 4 5))
(mult-position '(1 1 1 1 1))
(mult-position '(5 4 3 2 1))


(newline)
(define transform
  (lambda (x)
    (cond
      ((symbol? x) (symbol->string x))
      ((string? x) (string->symbol x)))))

(transform "string")
(transform 'symbol)