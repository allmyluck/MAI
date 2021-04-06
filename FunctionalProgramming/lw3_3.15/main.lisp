(defun column-extend-matrix (a k u)
  (let ((m (array-dimension a 0))
        (n (array-dimension a 1)))
    (let ((b (make-array (list m (+ 1 n))))) ; b = Matrix(* m (1 + n)) 
      (dotimes (i m)
        (dotimes (j k)
          (setf (aref b i j) (aref a i j)))) ; b[i][j] = a[i][j]
      (loop
        :for i :below m
        :do (setf (aref b i k) (aref u i))) ; b[i][k] = u[i]
      (dotimes (i m)
        (loop :for j :from k :to (- n 1) :do 
          (setf (aref b i (+ 1 j)) (aref a i j)))) ; b[i][1 + j] = a[i][j]
      b)))

(defun line-extend-matrix (a k v)
  (let ((m (array-dimension a 0))
        (n (array-dimension a 1)))
    (let ((b (make-array (list (+ 1 m) n)))) ; b = Matrix(* (1 + m) n)
      (dotimes (i k)
        (dotimes (j n)
          (setf (aref b i j) (aref a i j)))) ; b[i][j] = a[i][j]
      (loop
        :for j :below n
        :do (setf (aref b k j) (aref v j))) ; b[k][j] = v[j], j : 0 to n
      (dotimes (j n)
        (loop :for i :from k :to (- m 1) :do
          (setf (aref b (+ 1 i) j) (aref a i j)))) ; b[i + 1][j] = a[i][j]
      b)))

(defun extend-matrix (a u v i j)
  (array-dimension a 0)
  (array-dimension a 1)
  (if (and (and (<= i (array-dimension a 0)) (<= j (array-dimension a 1))) (and (> i 0) (> j 0))) (column-extend-matrix (line-extend-matrix a i u) j v))
)
;test_variables
(defvar m1 (make-array '(3 3) :initial-contents '((0 0 0 ) (0 0 0) (0 0 0))))
(defvar u1 #(1 1 1))
(defvar v1 #(2 2 2 2))
(defvar m2 (make-array '(2 4) :initial-contents '((0 0 0 0) (0 0 0 0))))
(defvar u2 #(1 1 1 1))
(defvar v2 #(2 2 2))
(defvar m3 (make-array '(3 4) :initial-contents '((0 0 0 0) (0 0 0 0) (0 0 0 0))))
(defvar u3 #(1 1 1 1))
(defvar v3 #(2 2 2 2))
(defvar m4 (make-array '(1 1) :initial-contents '((0))))
(defvar u4 #(1))
(defvar v4 #(2 2))
;(extend-matrix m1 u1 v1 0 0)
;(extend-matrix m2 u2 v2 1 1)
;(extend-matrix m3 u3 v3 2 3)
;(extend-matrix m4 u4 v4 0 0)
;(extend-matrix m4 u4 v4 1 1)
;(extend-matrix m4 u4 v4 2 2)