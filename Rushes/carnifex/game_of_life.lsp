;;(with-open-file (*standard-output* "/dev/null" :direction :output
;;												:if-exists :supersede))

;; Convenient way to store the notice message

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
	(format t "Window size is too small (should be 10x10 at least)~%")
	(sb-ext:exit))

(defun check-arguments()
	"Check passed arguments and call error for incorrect formating"
	;; Fetch the arguments (discard the program's name')
	(defparameter *arguments* (cdr *posix-argv*))

	;; Check if there are exactly 2 arguments
	(if (not (eq (length *arguments*) 2)) (error-args))

	;; Check if the arguments are strict integers and no trailing caracters
	(if (parse-integer (car *arguments*) :junk-allowed t)
		(if (parse-integer (reverse (car *arguments*)) :junk-allowed t)
			(if (parse-integer (car (cdr *arguments*)) :junk-allowed t)
				(if (not (parse-integer (reverse (car (cdr *arguments*))) :junk-allowed t))
					(error-args))
				(error-args))
			(error-args))
		(error-args))
	)

(defun make-row-array (rows max-columns)
	"Make an array of length rows containing arrays of
	length max-columns, with a fill pointer initially set to 0"
	(make-array rows
		:initial-contents (loop for i from 0 below rows
								collect (make-array max-columns
												:fill-pointer 0))))
(defun init-grid()
	"Initialize the cells grid"
	;; Width & Height of the window
	(defparameter *width* (parse-integer(car(cdr *posix-argv*))))
	(defparameter *height* (parse-integer(car(cdr (cdr *posix-argv*)))))

	;; Check if the size provided is within a correct range
	(if (< *width* 40) (error-size))
	(if (< *height* 40) (error-size))

	;; Init the grid
	(let ((new_grid (make-row-array *width* *height*))) new_grid)
)

;;;;;;;;;;;;;;;
;;;	PRELOAD	;;;
;;;;;;;;;;;;;;;

;; Preliminary checks
(check-arguments)
(defparameter *current-grid* (init-grid))
(defparameter *successors-grid* (init-grid))
(defparameter *ratio* (/ *height* *width*))
;; Load SDL library
(ql:quickload "lispbuilder-sdl")

;;;;;;;;;;;;;;;;;;;
;;;	FUNCTIONS	;;;
;;;;;;;;;;;;;;;;;;;

(defun get-grid-value(g x y)
	(aref (aref g x) y))

(defun set-grid-value(g x y v)
	(setf (aref (aref g x) y) v))

;; 

(defun set-cell-state(grid x y bitmask state)
	;; Set cell's value inside the grid
	(set-grid-value grid x y (logxor cell state))
	;; propagate information to neighbours

	)

;; successor rules:
;; if 'alive' && neighbours < 2 -> die
;; if 'alive' && neighbours > 3 -> die
;;
;; if 'alive' && 2 < neighbours < 4 -> live
;; if 'dead' && neighbours == 3 -> live
;;
;; details:
;; dead(0) || alive(1) (in fact: WE DON'T CARE ABOUT PREVIOUS STATE !!)
;; && sum(neighbours (2^i))
;; > 3
;; -> die
;; < 2
;; -> die
;; else
;; -> live
;;
;; neighbour states: from 2 to 256 ... (2^1) to (2^8)


(defun compute-successors-grid(grid successor-grid)
	"Compute all successors in the grid to the successor-grid"
	(let ((neighbours 0))
		(loop for i from 0 below *width* do
			(loop for j from 0 below *height* do
				(let ((cell get-grid-value grid i j))
				;; Check the cell's' neighbourhood
					(loop for k from 1 to 8
						;; sum the neighbours bitmask
						collect (if (> (logand cell (exp (2 k))) 0) (+ neighbours 1))
								;; > 3 neighbours -> die ! (& go to the next cell)
								(if (> neighbours 3) ((set-cell-state successor-grid i j cell 0) (return))))
					;; < 3 neighbours -> die ! (else: 2 || 3 neighbours -> live)
					(if (< neighbours 2) (set-cell-state successor-grid i j cell 0))
					(if (< neighbours 4) (set-cell-state successor-grid i j cell 1))))))
	;; TODO
	;; Swap the grids ?
	;; At least, return the modified (successor) grid
	)

(defun draw-grid(g)
	"Draw all grid points in the viewport"
	(loop for i from 0 below *width* do
		(loop for j from 0 below *height*
		;; Check if cell state is 'alive'
			collect (if (> (logand (get-grid-value g i j) 1) 0)
						(let ((x (* i *vp-twist*))
							(y (* j *vp-twist*)))
							(sdl:draw-box (sdl:rectangle-from-edges-* x y (+ x *vp-twist*) (+ y *vp-twist*))
								:color sdl:*white*))))))

;; (set-grid-value *current-grid* 2 0 "M"))
;; (format t "Blabla: ~S~%" (get-grid-value *current-grid* 2 0))

;; NOTE
;; ====
;; How does it work ?
;; Every 'cell' (a point in the grid) can have multiple states
;; which are represented as a bitmask. The values are the following:
;;
;; 0 - died, everyone is dead around
;; 1 - alive, everyone is dead around
;; 2 - top-left neighbourg is alive
;; 4 - top neighbourg is alive
;; 8 - top-right neighbourg is alive
;; 16 - left neighbourg is alive
;; 32 - right neighbourg is alive
;; 64 - bottom-left neighbourg is alive
;; 128 - bottom neighbourg is alive
;; 256 - bottom-right neighbourg is alive
;; (512) - I used to be alive (BONUS)
;;
;; Of course, since we use bitmasks a cell can stack multiple
;; different values without risk of collision, thus represent
;; all the different existing states.

;; We want a 'cell perfect' viewport (no matter the zoom, the
;; viewport/cell size should always draw full cells)


;; NOTES ON VIEWPORT
;; =================
;; Viewport: the visible part of the grid
;; Grid: the cell data set

;; Main
(defun main (argv)
	(defparameter *random-color* sdl:*white*)
	;; Size of the viewport: ratio is height / width of the grid
	(defparameter *vp-height* (* 800 *ratio*))
	;; Viewport twist: factor to resize cells to fit viewport
	(defparameter *vp-twist* (/ 800 *width*))

	(set-grid-value *current-grid* 1 1 1)
	(set-grid-value *current-grid* 3 4 1)
	(set-grid-value *current-grid* 13 4 1)
	(set-grid-value *current-grid* 3 14 1)
	(set-grid-value *current-grid* 25 25 1)
	(set-grid-value *current-grid* 49 49 1)

	(sdl:with-init ()
		;; (sdl:window *width* *height* :title-caption "Move a rectangle using the mouse")
		(sdl:window 800 *vp-height* :title-caption "Carnifex: The Game of Life")
		(setf (sdl:frame-rate) 60)
		(sdl:with-events ()
			(:quit-event () t
						(sb-ext:exit))
			(:key-down-event ()
				(sdl:push-quit-event))
			(:idle ()
;; Set cell under cursor to 'alive' state on left click
				(when (sdl:mouse-left-p)
					(set-grid-value *current-grid* (sdl:mouse-x) (sdl:mouse-y) 1))
;; Clear the display each game loop
				(sdl:clear-display sdl:*black*)
;; Draw the currently processed grid
				(draw-grid *current-grid*)
;; Redraw the display
				(sdl:update-display)))))



;; Run
(sb-int:with-float-traps-masked (:invalid :inexact :overflow)
	(main *posix-argv*))
