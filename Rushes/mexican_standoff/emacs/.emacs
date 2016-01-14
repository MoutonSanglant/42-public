(load-file "~/.emacs.d/ft_header/ft_header.el")
(require 'ft_header)

;; Show cursor position
(column-number-mode 1)
;; Indent newlines
(define-key global-map (kbd "RET") 'newline-and-indent)
(set-language-environment "UTF-8")
(setq-default c-default-style "linux"
			  c-basic-offset 4
			  tab-width 4
			  indent-tabs-mode t)

;; Write '()'
(defun pair-parenthesis ()
	(interactive)
	(insert "()")
	(backward-char 1))
;; Write '{}'
(defun pair-accol ()
	(interactive)
	(insert "{}")
	(backward-char 1))

;; Return path of the backup file
(defun my-backup-file-name (fpath)
  (let* (
		 (backupRootDir "~/.emacs.d/backup")
		 (filePath (replace-regexp-in-string "[A-Za-z]:" "" fpath ))
		 (backupFilePath (replace-regexp-in-string "//" "/" (concat backupRootDir filePath "~") ))
		 )
	(make-directory (file-name-directory backupFilePath) (file-name-directory backupFilePath))
	backupFilePath
	)
  )

;; Set backup file
(setq make-backup-file-name-function 'my-backup-file-name)

;; Map '(' to auto-close parenthesis
(add-hook 'c-mode-common-hook
	'(lambda ()
		(local-set-key "(" 'pair-parenthesis)))

;; Map '{' to auto-close accolades
(add-hook 'c-mode-common-hook
	'(lambda ()
		(local-set-key "{" 'pair-accol)))

;; Highlight double spaces and EOL spaces
(add-hook 'c-mode-common-hook
		(lambda () (highlight-regexp " \\( \\|$\\)" 'trailing-whitespace)
		))	
