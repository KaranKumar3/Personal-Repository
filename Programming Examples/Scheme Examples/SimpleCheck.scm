#lang scheme

(define check-it
  (lambda (x y)
    (cond
      ((> x y) (- x y))
      ((= x y) y)
      ((< x y) (+ y x)))))

(newline) "check-it testing"
(check-it 5 15)
(check-it 15 5)
(check-it 5 5)