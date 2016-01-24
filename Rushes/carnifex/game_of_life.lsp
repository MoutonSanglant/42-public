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
	;;	(vector-push '8 (aref my_array 2)) my_array)
	;;(vector-push 'x (aref my_array 2))
	;; (defparameter *grid* (make-array '((list (integerp *width*) (integerp *height*)))))
	;;						:initial-contents'0))
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

(defun set-grid-value(g x y v)
	(vector-push v (aref g x)))

(defun get-grid-value(g x y)
	(let ((row x)
			(col y))
		(aref (aref g row) col)))

(defun parse-grid())

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

;; Main
(defun main (argv)
	(defparameter *random-color* sdl:*white*)
	;; Size of the viewport: ratio is height / width of the grid
	(defparameter *height* (* 800 *ratio*))
	(sdl:with-init ()
		;; (sdl:window *width* *height* :title-caption "Move a rectangle using the mouse")
		(sdl:window 800 *height* :title-caption "Carnifex: The Game of Life")
		(setf (sdl:frame-rate) 60)
		(sdl:with-events ()
			(:quit-event () t
						(sb-ext:exit))
			(:key-down-event ()
				(sdl:push-quit-event))
			(:idle ()
;; Change the color of the box if the left mouse button is depressed
				(when (sdl:mouse-left-p)
					(setf *random-color* (sdl:color :r (random 255) :g (random 255) :b (random 255))))
;; Clear the display each game loop
				(sdl:clear-display sdl:*black*)
;; Draw the box having a center at the mouse x/y coordinates.
				(sdl:draw-box (sdl:rectangle-from-midpoint-* (sdl:mouse-x) (sdl:mouse-y) 20 20)
																		:color *random-color*)
;; Redraw the display
				(sdl:update-display)))))



;; Run
(sb-int:with-float-traps-masked (:invalid :inexact :overflow)
	(main *posix-argv*))
