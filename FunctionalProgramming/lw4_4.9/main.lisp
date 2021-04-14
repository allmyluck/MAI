(defun whitespace-char(ch)
	(member ch '(#\Space #\Tab #\Newline))
)


(defun russian-upper-case-p (char)
  (position char "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ"))

(defun russian-char-downcase (char)
	(let ((i (russian-upper-case-p char)))
    (if i 
        (char "абвгдеёжзийклмнопрстуфхцчшщъыьэюя" i)
        (char-downcase char))))  

(defun russian-char-equal (char1 char2)
  (char-equal (russian-char-downcase char1)
              (russian-char-downcase char2)))

(defun endSentence-char(ch)
	(member ch '(#\! #\? #\. #\"))
)

(defun last-word-char-count(ch str)
	(let
		(
			(res 0)
			(cur-ch nil)
		)
		
		(loop for i from (- (length str) 1) downto 0 do
			(setq cur-ch (char str i))	
			(if (and (or (char-equal ch cur-ch) (russian-char-equal ch cur-ch)) (not (endSentence-char cur-ch)))
				(setq res (+ res 1))
			)	
			(if (or (whitespace-char cur-ch) (equalp i 0))
				(return res)
			)
		)
	)
)

;(last-word-char-count #\Ы "К долинам,  покоем объятым,  ему не сойти с высоты.")
;(last-word-char-count #\А "\"Почему здесь никого нет, - удивилась Аленка, - я пришла раньше или опоздала?\"")
;(last-word-char-count #\а "\"Почему здесь никого нет, - удивилась Аленка, - я пришла раньше или опоздала?\"")
;(last-word-char-count #\о "Много.")
;(last-word-char-count #\к "Креветка.")
;(last-word-char-count #\к "Креветка!?")
;(last-word-char-count #\к "Двойные кавычки активно используются в русском языке в машинном тексте!?")
;(last-word-char-count #\у "Двойные кавычки активно используются в русском языке в машинном тексте!?")
;(last-word-char-count #\f "Hello, my friend!")
