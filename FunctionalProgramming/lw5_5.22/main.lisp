(defclass polar ()
    ((radius :initarg :radius :accessor radius)
    (angle  :initarg :angle  :accessor angle)))

(defclass cart ()
    ((x :initarg :x :reader cart-x)
    (y :initarg :y :reader cart-y)))

(defclass line ()
    ((start :initarg :start :accessor line-start)
    (end   :initarg :end   :accessor line-end)))

(defmethod cart-x ((p polar)) ; angle ~ (-pi,pi]
    (* (radius p) (cos (angle p))))

(defmethod cart-y ((p polar)) ; angle ~ (-pi,pi]
    (* (radius p) (sin (angle p))))

(defmethod line-k ((line1 line))
    (/ (- (cart-y (line-start line1)) (cart-y (line-end line1)))
    (- (cart-x (line-start line1)) (cart-x (line-end line1)))))

(defmethod line-x-const ((l line))
    (almost-equal (cart-x (line-start l)) (cart-x (line-end l))))

(defmethod print-object ((p polar) stream)
    (format stream "[POLAR (radius ~d angle ~d)]"
    (radius p) (angle p)))

(defmethod print-object ((c cart) stream)
    (format stream "[CART (x ~d y ~d)]"
    (cart-x c) (cart-y c)))

(defmethod print-object ((lin line) stream)
    (format stream "LINE (~s ~s)"
    (line-start lin) (line-end lin)))

(defun almost-equal (a b)
    (< (abs(- a b)) 0.001))

(defun line-parallel2-p (line1 line2)
    (if (or (line-x-const line1) (line-x-const line2))
        (if (and (line-x-const line1) (line-x-const line2)) T NIL)
        (if (almost-equal (line-k line1) (line-k line2)) T NIL)))

;(setq l1 (make-instance 'line :start (make-instance 'cart :x 1 :y 1) :end   (make-instance 'cart :x 0 :y -1)))
;(setq l2 (make-instance 'line :start (make-instance 'cart :x 0 :y 2) :end   (make-instance 'cart :x -1 :y 0)))
;(setq l2 (make-instance 'line :start (make-instance 'cart :x -1 :y 0) :end   (make-instance 'cart :x  0 :y 1)))
;(setq l2 (make-instance 'line :start (make-instance 'polar :radius 1 :angle (/ pi 4)) :end   (make-instance 'cart :x  0 :y 2)))
;(setq l2 (make-instance 'line :start (make-instance 'polar :radius 0 :angle 0) :end   (make-instance 'cart :x  1 :y 1)))
;(setq l2 (make-instance 'line :start (make-instance 'cart :x 0 :y 2) :end   (make-instance 'cart :x 0 :y 0)))
;(setq l2 (make-instance 'line :start (make-instance 'polar :radius 20 :angle (/ pi 2)) :end   (make-instance 'polar :radius 2 :angle (- (/ pi 2)))))
;(line-parallel2-p l1 l2)