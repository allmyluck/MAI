(defun sum-product1 (list1 list2)
    (cond 
        ((null list1) 0)
        (t (+ (* (first list1)(first list2))(sum-product1 (rest list1)(rest list2))))
    )
)

(defun sum-product2 (list)
    (if (>= (list-length list) 2)
        (sum-product1 list (reverse list))
    )
)