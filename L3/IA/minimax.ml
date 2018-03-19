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


let listeMax liste =
let rec aux accu = function 
	| [] -> accu
	| e::l -> if e>accu then (aux e l) else (aux accu l)
in aux (-10000) liste 

let listeMin liste = 
let rec aux accu = function
	| [] -> accu
	| e::l -> if accu>e then (aux e l) else (aux accu l)
in aux 10000 liste



let rec minimax etatCourant profondeurCourante etatsFils evaluation =
	let coupsPoss = etatsFils etatCourant in
	if (coupsPoss = [])
			  then 
 					(evaluation etatCourant)
 			  else
 			  if (profondeurCourante mod 2) = 0 
 			  		then listeMax (List.fold_right (fun (coup,etat) l -> (minimax etat (profondeurCourante+1) etatsFils evaluation)::l) coupsPoss [])
 			  		else listeMin (List.fold_right (fun (coup,etat) l -> (minimax etat (profondeurCourante+1) etatsFils evaluation)::l) coupsPoss [])
 			  		

let rec recherche profondeurMaximale etatCourant profondeurCourante etatsFils evaluation =
	let coupsPoss = etatsFils etatCourant in
	if ((profondeurCourante=profondeurMaximale) || (coupsPoss = [])) 
		then 
 		(evaluation etatCourant)
 	else
 		if (profondeurCourante mod 2 = 0)  
 			  		then listeMax (List.fold_right (fun (coup,etat) l -> (recherche profondeurMaximale etat (profondeurCourante+1) etatsFils evaluation)::l) coupsPoss [])
 			  		else listeMin (List.fold_right (fun (coup,etat) l -> (recherche profondeurMaximale etat (profondeurCourante+1) etatsFils evaluation)::l) coupsPoss [])
 			  		

let meilleurCoup profondeurMaximale etatCourant profondeurCourante etatsFils evaluation =
	let recherche_res = recherche profondeurMaximale etatCourant profondeurCourante etatsFils evaluation in
	let rec aux = function
	| [] -> 0, " "
	| (coup,etat)::l -> if recherche_res <> (recherche profondeurMaximale etat (profondeurCourante+1) etatsFils evaluation)
		then aux l 
		else (recherche_res,coup)
	in aux (etatsFils etatCourant)


