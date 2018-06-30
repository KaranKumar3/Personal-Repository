#lang scheme

(define gpa
  (lambda (lst)
    (if (null? lst)
        '()
        (/ (apply + (map gpa_converter lst)) (length lst) ))))

(define gpa_converter
  (lambda (g)
    (cond
      ((equal? g 'A) 4.0)
      ((equal? g 'B) 3.0)
      ((equal? g 'C) 2.0)
      ((equal? g 'D) 1.0)
      ((equal? g 'F) 0.0))))

(gpa '(A B A B))  