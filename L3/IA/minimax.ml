(* Arbre de l'exemple DESCRIPTION A COMPLETER ----------------------------------------- *)

(* etatInitial de type ‘a : l’état initial                                              *)
(* etatsFils de type 'a -> ('b * 'a) list : fonction qui associe à chaque état la liste *)
(* des doublets (coup possible, état fils obtenu)                                       *)

let etatInitial = "0";;

let etatsFils
(e : 'a)
: ('b * 'a) list =
match e with
	"0"    -> [("p","a");("q","c")]
	|"a"  -> [("u","a1");("r","a2")]
	|"a1" -> [("s","a1a")]
	| _   -> [];;


(* evaluation de type 'a -> int : fonction d’évaluation qui renvoie un entier           *)
(* appartenant à l'intervalle [-INFINI,+INFINI]                                         *)

let evaluation
(e : 'a)
: int =
match e with
	"a1a"  -> -7
	|"a2"  -> -2
	|"b1"  -> 2
	|"b3"  -> -1
	|"c1"  -> -7
	| _    -> failwith "Erreur : evaluation : etat non terminal";;

let pair entier = (entier mod 2) = 0;;

let rec longueur = function
	|[] -> 0
	|e::l -> 1+(longueur l);;

let tete = function
	|[] -> failwith "pas de tete"
	|e::l -> e;;
	
let pop = function
	|[] -> []
	|e::l -> l;;

let PROFMAX = 5;;
let INFINI = 100000;;
let meilleur = 

let rec minimax = EtatCourant profondeurCourante etatF eval = function
	let listeCoupsPossibles = etatF(EtatCourant) in
		if (profondeurCourante = PROFMAX || (longueur(listeCoupsPossibles) = 0)
		then eval(EtatCourant)
		else let meilleur = if (pair(profondeurCourante)) then -INFINI else INFINI in
			if (longueur(listeCoupsPossibles) != 0)
			then let valeur = (minimax (tete(listeCoupsPossibles) profondeurCourante+1 etatF eval) in
				if (pair(profondeurCourante)
				then if (valeur > meilleur) then let meilleur = valeur else meilleur
				else if (valeur < meilleur) then let meilleur = valeur else meilleur
				
			else
			meilleur;;
