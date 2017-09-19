#!/usr/bin/env bash
# Author: Erik Martin-Dorel
# Version 2.1 (2017-09-18)

set -euo pipefail
# La ligne précédente, facultative, permet de quitter immédiatement
# en cas d'erreur

function die_hard() {
    echo -e "$@" >&2
    exit 1
}

function stderr() {
    echo -e "$@" >&2
}

function pause() {
    read -p 'Appuyer sur Entrée pour continuer (ou Ctrl-C pour quitter)...'
}

function ask() {
    stderr "$@"
    select val in "Oui" "Non"; do break; done
    if [ "$REPLY" = "" ]; then
	die_hard "Vous avez sauté la question."
    fi
    if [ "$val" = "" ]; then
	die_hard "Votre réponse '$REPLY' est incorrecte. (Chiffre 1 ou 2 attendu.)"
    fi
    if [ "$val" = "Oui" ]; then
	val=""
	return 0
    else
	val=""
	return 1
    fi
}

cat <<EOF
Ce script "install-tuareg-pfita.bash" est dédié à l'installation de
tuareg-mode + company (+ merlin) pour GNU/Linux.

En particulier ce script n'est pas conçu pour Windows ou macOS.

De plus, il suppose que les logiciels suivants sont déjà installés :
- OCaml ["4.00.0" <= version < "4.03"]
- GNU Emacs [version >= 24.3]
- wget (pour installer merlin)
- m4   (pour installer merlin)

EOF

SRCDIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )
stderr "Script lancé à partir du dossier : $SRCDIR"

src_obj="$SRCDIR/_pfita"
stderr "Si vous choisissez d'installer Merlin,"
stderr "il sera installé dans le dossier : ${src_obj}"

stderr
pause
stderr

# ================================================================

FIL_EMACS=0
if [[ -r "$HOME/.emacs" ]]; then FIL_EMACS=1; fi

FIL_INIT=0
if [[ -r "$HOME/.emacs.d/init.el" ]]; then FIL_INIT=1; fi

if [[ $FIL_EMACS = 1 && $FIL_INIT = 1 ]]; then
    stderr "Note : Vous avez à la fois un fichier ~/.emacs et ~/.emacs.d/init.el"
    die_hard "Veuillez supprimer ou renommer ~/.emacs avant de relancer le script."
fi

if [[ $FIL_EMACS = 1 ]]; then
    INI="$HOME/.emacs"
else
    mkdir -p "$HOME/.emacs.d"
    INI="$HOME/.emacs.d/init.el"
fi

if [[ -f $INI ]]; then
    stderr "*** Le fichier '$INI' existe déjà et va être sauvegardé ..."
    cp --backup=numbered -f -v -- "$INI" "$INI"
    stderr
fi

# ================================================================

stderr "*** Préparation du fichier $INI ..."

cat > "$INI" <<EOF
;;; init.el --- Emacs conf file, created on $(date -I) -*- coding: utf-8 -*-

;; Configuration de Tuareg

(require 'package)
(add-to-list 'package-archives '("melpa" . "http://melpa.org/packages/") t)
(package-initialize)
(custom-set-variables
 ;; custom-set-variables was added by Custom.
 ;; If you edit it by hand, you could mess it up, so be careful.
 ;; Your init file should contain only one such instance.
 ;; If there is more than one, they won't work right.
 '(package-selected-packages (quote (company tuareg))))
(custom-set-faces
 ;; custom-set-faces was added by Custom.
 ;; If you edit it by hand, you could mess it up, so be careful.
 ;; Your init file should contain only one such instance.
 ;; If there is more than one, they won't work right.
 )

(add-hook 'tuareg-mode-hook (lambda () (company-mode)
  (local-set-key (kbd "<S-return>") #'electric-indent-just-newline)
  (local-set-key (kbd "<C-return>") #'company-complete)))

;; Configuration globale

(setq column-number-mode t)
(setq line-number-mode t)

;; Marquage des parenthèses

(load-library "paren")
(show-paren-mode 1)

EOF

stderr

# https://github.com/ocaml/tuareg/releases/download/2.0.10/tuareg-2.0.10.tar.gz
# https://github.com/ocaml/tuareg/archive/master.tar.gz
# (load "~/.emacs.d/lisp/tuareg-2.0.10/tuareg-site-file")
# https://raw.githubusercontent.com/ocaml/opam-repository/master/packages/merlin/merlin.2.3.1/opam

# ================================================================

stderr "*** Installation facultative de Merlin ..."

if ask "Voulez-vous installer Merlin ? (améliore Tuareg, mais plus lourd à installer)"; then
    wget https://raw.githubusercontent.com/avsm/opam-boot/master/opam-boot
    # chmod a+x opam-boot # unnecessary (as we prepend 'bash' below)

    opam_env="${src_obj}/opam-env.sh"

    if [[ ! -r "$opam_env" ]]; then
	bash ./opam-boot --ocaml 4.02.2 --obj "${src_obj}"
    else
	stderr "Le fichier '$opam_env' existe déjà."
    fi

    ## We could use system's version of OCaml (else pick a default version)
    ## but the version of merlin could change!
    # OCAML_VERSION=$(ocamlc -version 2>/dev/null || true)
    # if [[ -z $OCAML_VERSION ]]; then OCAML_VERSION='4.01.0'; fi
    # bash ./opam-boot --ocaml "${OCAML_VERSION}" --obj "${src_obj}"

    source "${opam_env}"

    opam install -y merlin.2.3.1

    stderr
    stderr "*** Merlin a été installé et le fichier '$INI' va être mis à jour ..."

    BIN_OCAML="$(which ocaml)" || die_hard "Erreur inattendue : ocaml non trouvé"
    BIN_OPAM="$(which opam)" || die_hard "Erreur inattendue : opam non trouvé"
    SHARE="$(opam config var share 2> /dev/null)"
    BIN_MERLIN="$(which ocamlmerlin)" || die_hard "Erreur inattendue : ocamlmerlin non trouvé"

    cat >> "$INI" <<EOF
;; Configuration de Merlin

(setq tuareg-interactive-program "$BIN_OCAML")
(setq tuareg-opam "$BIN_OPAM")
;;;  (setq tuareg-opam-insinuate t) ; disabled - would overwrite merlin-command

;; Add opam emacs directory to the load-path
;;;  (setq opam-share (substring (shell-command-to-string "opam config var share 2> /dev/null") 0 -1))
(setq opam-share "$SHARE")
(add-to-list 'load-path (concat opam-share "/emacs/site-lisp"))
;; Load merlin-mode
(require 'merlin)
;; Start merlin on ocaml files
(add-hook 'tuareg-mode-hook 'merlin-mode t)
(add-hook 'caml-mode-hook 'merlin-mode t)
;; Enable auto-complete
(setq merlin-use-auto-complete-mode 'easy)
;; Use opam switch to lookup ocamlmerlin binary
;;;  (setq merlin-command 'opam)
(setq merlin-command "$BIN_MERLIN")

EOF

    stderr
fi

# ================================================================

stderr "*** Dernière étape : lancement d'Emacs et installation de tuareg & company."

emacs --eval "(progn (package-refresh-contents) (package-install 'tuareg) (package-install 'company) (insert \"Installation de tuareg-mode terminée !\n\nVous pouvez créer un fichier avec l'extension .ml en faisant C-x C-f tp1.ml RET\"))" &
