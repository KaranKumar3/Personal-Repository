#lang scheme

(define(reverseList lst)
  (if(null? lst)
     null
     (append(reverseList (cdr lst))(list(car lst)))))

(reverseList '(10 8 6 4 2 0))

(newline)

(define (listLength lst)
  (if(null? lst)
     0
     (+ 1 (listLength (cdr lst)))))

(listLength '(1 2 3 4 5 6 7 8 9 10))

(newline)

(define position
  (lambda(currentNumber lst)
    (cond
      ((<(length lst) currentNumber)  'invalid_list) ;if length is less than 3, invalid
      ((= currentNumber 1) (car lst)) ;if you are the third 3 jump out
      (else (position(- currentNumber 1)(cdr lst)))))) ;else keep going

(define findThird
  (lambda (lst)
    (position 3 lst)))

(findThird '(9 6 3 1))
(findThird '(9 6))
(findThird '(100 90 80 70 60))

(newline)

(define (smallest lst)
  (cond 
    ((null? (cdr lst)) (car lst))
    ((< (car lst) (smallest (cdr lst))) (car lst))
    (else (smallest (cdr lst)))))

(smallest '(100 90 80 70 60))

(newline)

(define member-of
  (lambda (e lst)
    (cond
      ((<(length lst) 0)  '())
      ((= e (car lst)) #t)
      ((not(= e (car lst))) (member-of e (cdr lst)) )
      (else #f))))

(member-of 10 '(100 90 80 70 60 10))

(newline)

(define sum-all
  (lambda (lst)
    (if (null? lst)
        0
        (+ (car lst) (sum-all(cdr lst))))))

(sum-all  '(1 2 3 4 5))

(newline)

(define mult-all
  (lambda (lst)
    (if (null? lst)
        1
        (* (car lst) (mult-all(cdr lst))))))

(mult-all  '(1 2 3))

(newline)

(define square-list
  (lambda (lst)
    (if (null? lst)
        '()
        (cons (* (car lst) (car lst)) (square-list(cdr lst))))))

(square-list  '(1 2 3))

(newline)

(define odds-all
  (lambda (lst)
    (if (null? lst)
        '()
        (if( = 0 (remainder (car lst) 2))
           (odds-all(cdr lst))
           (cons (car lst) (odds-all(cdr lst)))))))

(odds-all '(1 2 3 4 5 6 7))

(newline)

(define add-rest
  (lambda (lst)
    (if (null? lst)
        '()
        (cons (apply + lst) (add-rest(cdr lst))) )))

(add-rest '(1 2 3))

(newline)

(define cube-list1
  (lambda (lst)
    (if (null? lst)
        '()
        (cons (* (* (car lst) (car lst)) (car lst)) (cube-list1(cdr lst))))))

(cube-list1  '(1 2 3 4))

(newline)

(define cube-list2
  (lambda (lst)
    (if (null? lst)
        '()
        (map (lambda (x) (* (* x x) x)) lst) )))

(cube-list2 '(1 2 3 4))

(newline)

(define clean-list
  (lambda (lst)
    (if (null? lst)
        '()
        (filter number? lst) )))

(clean-list '(list 1 'a + 10 'hello lst '(1 2 3) '(a . b) red 8 6 -3))

(newline)

