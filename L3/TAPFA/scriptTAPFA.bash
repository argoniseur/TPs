#!/usr/bin/env bash
# Author: Erik Martin-Dorel
version="version 2.2.3 (2018-01-26)"

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
    local val
    select val in "Oui" "Non"; do break; done
    if [ "$REPLY" = "" ]; then
        die_hard "Vous avez sauté la question."
    fi
    if [ "$val" = "" ]; then
        die_hard "Votre réponse '$REPLY' est incorrecte. (Chiffre 1 ou 2 attendu.)"
    fi
    if [ "$val" = "Oui" ]; then
        return 0
    else
        return 1
    fi
}

function main() {
    cat <<EOF
$(basename $0) - $version
Ce script est dédié à l'installation de tuareg-mode + company (+ merlin)
pour GNU/Linux.
En particulier ce script n'est pas conçu pour Windows ou macOS.
De plus, il suppose que les logiciels suivants sont déjà installés :
- ocaml (version >= 4.01.0)
- emacs (version >= 24.3)
- curl (pour installer merlin)
- m4   (pour installer merlin)
- make (pour installer merlin)
  make est typiquement fourni avec le paquet nommé build-essential.
EOF

    local srcdir
    srcdir=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )
    stderr "Script lancé à partir du dossier : '$srcdir'"

    local src_obj="$srcdir/_pfita"
    stderr "Si vous choisissez d'installer Merlin,"
    stderr "il sera installé dans le dossier : '${src_obj}'"

    if [[ "$src_obj" =~ " " ]]; then
	stderr "
Attention : ce dossier contient des espaces, ce qui peut faire échouer
la compilation d'OCaml. Si vous souhaitez installer Merlin, mieux vaut
copier ce script à la racine de votre répertoire personnel ~/ avant de
le ré-exécuter."
    fi

    stderr
    pause
    stderr

    # ================================================================

    local fil_emacs=0
    if [[ -r "$HOME/.emacs" ]]; then fil_emacs=1; fi

    local fil_init=0
    if [[ -r "$HOME/.emacs.d/init.el" ]]; then fil_init=1; fi

    if [[ $fil_emacs = 1 && $fil_init = 1 ]]; then
        stderr "Note : Vous avez à la fois un fichier ~/.emacs et ~/.emacs.d/init.el"
        die_hard "Veuillez supprimer ou renommer ~/.emacs avant de relancer le script."
    fi

    local ini
    if [[ $fil_emacs = 1 ]]; then
        ini="$HOME/.emacs"
    else
        mkdir -p "$HOME/.emacs.d"
        ini="$HOME/.emacs.d/init.el"
    fi

    if [[ -f $ini ]]; then
        stderr "*** Le fichier '$ini' existe déjà et va être sauvegardé ..."
        cp --backup=numbered -f -v -- "$ini" "$ini"
        stderr
    fi

    # ================================================================

    stderr "*** Préparation du fichier $ini ..."

    cat > "$ini" <<EOF
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
  (local-set-key (kbd "M-RET") #'company-complete)))
;; Configuration globale
(setq column-number-mode t)
(setq line-number-mode t)
;; Marquage des parenthèses
(load-library "paren")
(show-paren-mode 1)
;; Raccourcis C-c/C-x/C-v/C-z standards
(cua-mode 1)
EOF

    stderr

    # ================================================================

    stderr "*** Installation facultative de Merlin ..."

    if ask "Voulez-vous installer Merlin ? (améliore Tuareg, mais plus lourd à installer)"; then
        curl -OL https://github.com/erikmd/opam-boot/raw/e14c42f21407576abc523125815d295a898cf0ea/opam-boot
        chmod a+x opam-boot

        local opam_env="${src_obj}/opam-env.sh"

        if [[ ! -r "$opam_env" ]]; then
            ./opam-boot --ocaml 4.02.2 --obj "${src_obj}"
        else
            stderr "Le fichier '$opam_env' existe déjà."
        fi

        ## We could use system's version of OCaml (else pick a default version)
        ## but the version of merlin could change!
        # ocaml_version=$(ocamlc -version 2>/dev/null || true)
        # if [[ -z $ocaml_version ]]; then ocaml_version='4.01.0'; fi
        # bash ./opam-boot --ocaml "${ocaml_version}" --obj "${src_obj}"

        source "${opam_env}"

        opam install -y merlin.2.3.1
        ## Note: merlin 2.3.1 doesn't support OCaml >= 4.03:
        ## https://raw.githubusercontent.com/ocaml/opam-repository/master/packages/merlin/merlin.2.3.1/opam

        stderr
        stderr "*** Merlin a été installé et le fichier '$ini' va être mis à jour ..."

        local bin_ocaml
        bin_ocaml="$(which ocaml)" || die_hard "Erreur inattendue : ocaml non trouvé"
        local bin_opam
        bin_opam="$(which opam)" || die_hard "Erreur inattendue : opam non trouvé"
        local share
        share="$(opam config var share 2> /dev/null)"
        local bin_merlin
        bin_merlin="$(which ocamlmerlin)" || die_hard "Erreur inattendue : ocamlmerlin non trouvé"

        cat >> "$ini" <<EOF
;; Configuration de Merlin
(setq tuareg-interactive-program "$bin_ocaml")
(setq tuareg-opam "$bin_opam")
;;;  (setq tuareg-opam-insinuate t) ; disabled - would overwrite merlin-command
;; Add opam emacs directory to the load-path
;;;  (setq opam-share (substring (shell-command-to-string "opam config var share 2> /dev/null") 0 -1))
(setq opam-share "$share")
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
(setq merlin-command "$bin_merlin")
EOF

        stderr
    fi

    # ================================================================

    stderr "*** Dernière étape : lancement d'Emacs et installation de tuareg & company."

    emacs --eval "(progn (package-refresh-contents) (package-install 'tuareg) (package-install 'company) (insert \"Installation de tuareg-mode terminée.\n\nVous pouvez créer un fichier avec l'extension .ml en faisant C-x C-f tp1.ml RET\n\n(Rappel : C-x désigne la combinaison de touches Ctrl+x et RET la touche Entrée)\n\") (goto-char (point-min)))" &
}

main
