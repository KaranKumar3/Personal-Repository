#lang scheme

(define show_multiples
  (lambda (lst n)
    (if (null? lst)
        '()
        (if( = 0 (remainder (car lst) n))
           (cons (car lst) (show_multiples (cdr lst) n))
           (show_multiples (cdr lst) n)))))

(define show_multiples2
  (lambda (lst n)
    (if (null? lst)
        '()
         (filter (lambda (x) ( = 0 (remainder x n))) lst) )))

(newline) "show_multiples testing"
(show_multiples '(4 -2 8 2) 2)
(show_multiples '(10 9 8 7 6) 20)
(show_multiples '(3 -25 8 9) 3)
(newline) "show_multiples2 testing"
(show_multiples2 '(4 -2 8 2) 2)
(show_multiples2 '(10 9 8 7 6) 20)
(show_multiples2 '(3 -25 8 9) 3)