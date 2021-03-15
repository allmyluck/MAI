(defun square (x) (* x x))

(defun max (x y z)
   (if (> x y)
       (if (> x z)
           x
           (if (> y z)
               y
               z
           )
       )
       (if (> y z)
           y
           (if (> x z)
               x
               z
           )
       )
   )
)


(defun acute-angled (a b c))
