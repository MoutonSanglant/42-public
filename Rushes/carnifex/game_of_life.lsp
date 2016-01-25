;;;;;;;;;;;;;;;;;;;;;;;
;;;	INIT FUNCTIONS	;;;
;;;;;;;;;;;;;;;;;;;;;;;

;; Prints the usage notice on incorrect arguments
(defun error-args()
	"Output an error relative to passed arguments and exit the program"
	(format t "usage: sbcl --load game_of_life.lsp [-h] width height~%
positional arguments:
	width			width of the grid~%
	height			height of the grid~%
optional arguments:
	-h, --help		show this help message and exit~%"
	)
	(sb-ext:exit))

;; Prints the usage notice on incorrect provided sizes
(defun error-size()
	"Output an error relative to grid size and exit the program"
	(format t "Window size is too small (should be 40x40 at least)~%")
	(sb-ext:exit))

(defun check-arguments(arguments)
	"Check passed arguments and call error for incorrect formating"
	;; Fetch the arguments (discard the program's name')

	;; Check if there are exactly 2 arguments
	(if (not (eq (length arguments) 2)) (error-args))

	;; Check if the arguments are strict integers and no trailing caracters
	(if (parse-integer (car arguments) :junk-allowed t)
		(if (parse-integer (reverse (car arguments)) :junk-allowed t)
			(if (parse-integer (car (cdr arguments)) :junk-allowed t)
				(if (not (parse-integer (reverse (car (cdr arguments))) :junk-allowed t))
					(error-args))
				(error-args))
			(error-args))
		(error-args))
	)

(defun init-grid(width height)
	"Initialize the cells grid"
	;; Width & Height of the window

	;; Check if the size provided is within a correct range
	(if (< width 40) (error-size))
	(if (< height 40) (error-size))

	;; Init the grid
	(make-array (list width height)
				:element-type 'array
				:initial-element 0)
)

;;;;;;;;;;;;;;;
;;;	PRELOAD	;;;
;;;;;;;;;;;;;;;

;; Preliminary checks
(check-arguments (cdr *posix-argv*))
(defparameter *width* (parse-integer(car(cdr *posix-argv*))))
(defparameter *height* (parse-integer(car(cdr (cdr *posix-argv*)))))
(defparameter *current-grid* (init-grid *width* *height*))
(defparameter *successors-grid* (init-grid *width* *height*))
(defparameter *ratio* (/ *height* *width*))
;; Load SDL library
(ql:quickload "lispbuilder-sdl")
(defparameter *time* 0)
(defparameter *animation-speed* 10)
(defparameter *neighbours* 0)
(defparameter *vp-width* 800)
(defparameter *vp-height* (* *vp-width* *ratio*))
;; The viewport pixel twist
;(defparameter *vp-twist* (if (< (/ 800 *width*) 3) 3 (/ 800 *width*)))
(defparameter *zoom* (/ *vp-width* *width*))
(defparameter *vp-twist-x* (/ (* *zoom* *width*) *vp-width*))
(defparameter *visible-x* (/ (* *width* *vp-twist-x*) 800))
(defparameter *vp-x* 0)
(defparameter *vp-y* 0)

;;;;;;;;;;;;;;;;;;;
;;;	FUNCTIONS	;;;
;;;;;;;;;;;;;;;;;;;

(defun get-grid-value(g x y)
	(aref g x y))

(defun set-grid-value(g x y v)
	(setf (aref g x y) v))

(defun switch-cell(read-grid write-grid x y)
	(if (eq (get-grid-value read-grid x y) 0)
		(new-cell write-grid x y)
		(destroy-cell write-grid x y)))

(defun new-cell(write-grid x y)
	(set-grid-value write-grid x y 1)
)

(defun destroy-cell(write-grid x y)
	(set-grid-value write-grid x y 0)
)

(defun check-cell(read-grid write-grid x y)
	(defparameter *neighbours* 0)
	;; case: left
	(if (> x 0)
		(let ((xx (- x 1)))
			(if(eq (get-grid-value read-grid xx y) 1)
				(defparameter *neighbours* (+ *neighbours* 1)))))
	;; case: top
	(if (> y 0)
		(let ((yy (- y 1)))
			(if(eq (get-grid-value read-grid x yy) 1)
				(defparameter *neighbours* (+ *neighbours* 1)))))
	;; case: top-left
	(if (> x 0)
		(if (> y 0)
			(let ((xx (- x 1))(yy (- y 1)))
				(if(eq (get-grid-value read-grid xx yy) 1)
					(defparameter *neighbours* (+ *neighbours* 1))))))
	;; case: right
	(if (< x (- *width* 1))
		(let ((xx (+ x 1)))
			(if(eq (get-grid-value read-grid xx y) 1)
				(defparameter *neighbours* (+ *neighbours* 1)))))
	;; case: top-right
	(if (< x (- *width* 1))
		(if (> y 0)
			(let ((xx (+ x 1))(yy (- y 1)))
				(if(eq (get-grid-value read-grid xx yy) 1)
					(defparameter *neighbours* (+ *neighbours* 1))))))
	;; case: bottom-right
	(if (< x (- *width* 1))
		(if (< y (- *height* 1))
			(let ((xx (+ x 1))(yy (+ y 1)))
				(if(eq (get-grid-value read-grid xx yy) 1)
					(defparameter *neighbours* (+ *neighbours* 1))))))
	;; case: bottom
	(if (< y (- *height* 1))
		(let ((yy (+ y 1)))
			(if(eq (get-grid-value read-grid x yy) 1)
				(defparameter *neighbours* (+ *neighbours* 1)))))
	;; case: bottom-left
	(if (> x 0)
		(if (< y (- *height* 1))
			(let ((xx (- x 1))(yy (+ y 1)))
				(if(eq (get-grid-value read-grid xx yy) 1)
					(defparameter *neighbours* (+ *neighbours* 1))))))

	;; if cell is alive
	(if (eq (get-grid-value read-grid x y) 1)
		;; under populatiom
		(if (< *neighbours* 2)
			(list
				(destroy-cell write-grid x y)
				(return-from check-cell))))

	;; if cell is alive
	(if (eq (get-grid-value read-grid x y) 1)
		;; over-population
		(if (> *neighbours* 3)
			(list
				(destroy-cell write-grid x y)
				(return-from check-cell))))

	;; if cell is dead
	(if (eq (get-grid-value read-grid x y) 0)
		;; birth
		(if (eq *neighbours* 3)
			(list
				(new-cell write-grid x y)
				(return-from check-cell))))
)

(defun move-next-generation(read-grid write-grid)
	"Make a step toward the next generation of cells"
	(if (> *time* 1)
	(list
		(loop for i from 0 below *width* do
			(loop for j from 0 below *height*
				collect (check-cell read-grid write-grid i j)))
		(defparameter *time* 0))
	)
	(loop for i from 0 below *width* do
		(loop for j from 0 below *height*
			collect (set-grid-value read-grid i j (get-grid-value write-grid i j))))
)

(defun draw-grid(g)
	"Draw all grid points in the viewport"
	(loop for i from 0 below *width* do
		(loop for j from 0 below *height*
		;; Check if cell state is 'alive'
			collect (if (> (logand (get-grid-value g i j) 1) 0)
				(let ((x (* i *zoom*))
					(y (* j *zoom*)))
					(sdl:draw-box (sdl:rectangle-from-edges-* x y (+ x *zoom*) (+ y *zoom*))
						:color sdl:*white*))))))

;; Main
(defun main ()
	(defparameter *random-color* sdl:*white*)
	;; Size of the viewport: ratio is height / width of the grid
	;; Viewport twist: factor to resize cells to fit viewport

	(new-cell *successors-grid* 15 5)
	(new-cell *successors-grid* 15 6)
	(new-cell *successors-grid* 15 7)
	(new-cell *successors-grid* 14 7)
	(new-cell *successors-grid* 13 6)

	(new-cell *successors-grid* 24 24)
	(new-cell *successors-grid* 24 25)
	(new-cell *successors-grid* 25 24)
	(new-cell *successors-grid* 15 24)
	(new-cell *successors-grid* 15 25)
	(new-cell *successors-grid* 15 26)

	(sdl:with-init ()
		;; (sdl:window *width* *height* :title-caption "Move a rectangle using the mouse")
		(sdl:window 800 *vp-height* :title-caption "Carnifex: The Game of Life")
		(setf (sdl:frame-rate) 60)
		(sdl:with-events ()
			(:quit-event () t
						(sb-ext:exit))
			(:key-down-event (:key key)
				(when (sdl:key= key :sdl-key-escape)
					(sdl:push-quit-event))
				(when (sdl:key= key :sdl-key-p)
					(if(eq *animation-speed* 0)(defparameter *animation-speed* 12)(defparameter *animation-speed* 0)))
				(when (sdl:key= key :sdl-key-period)
					(if(> *animation-speed* -1)(defparameter *animation-speed* (+ *animation-speed* 1))))
				(when (sdl:key= key :sdl-key-comma)
					(if(not (eq *animation-speed* 0))(defparameter *animation-speed* (- *animation-speed* 1))))
				(when (sdl:key= key :sdl-key-r)
					(defparameter *animation-speed* 0)(defparameter *current-grid* (init-grid *width* *height*))(defparameter *successors-grid* (init-grid *width* *height*))(move-next-generation *current-grid* *successors-grid*))

				(when (sdl:key= key :sdl-key-space)
					(format t ">> next step~%")
					;;(defparameter *current-grid* (move-next-generation *current-grid* *successors-grid*))
					(move-next-generation *current-grid* *successors-grid*)
					)
				)
			(:idle ()
				(defparameter *time* (+ *time* (* (sdl:time-scale) *animation-speed*)))
				(move-next-generation *current-grid* *successors-grid*)
				(when (sdl:mouse-left-p)
					(switch-cell *current-grid* *successors-grid* (truncate (/ (sdl:mouse-x) *zoom* )) (truncate (/ (sdl:mouse-y) *zoom*))))
				(sdl:clear-display sdl:*black*)
				(draw-grid *current-grid*)
				(sdl:update-display)))))
;; Run
(sb-int:with-float-traps-masked (:invalid :inexact :overflow)
	(main))
