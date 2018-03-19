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

let etatInitialA1 = "0";;

let etatsFilsA1
(e : 'a)
: ('b * 'a) list =
match e with
	"0"    -> [("q","a");("v","b");("r","c");("t","d");("p","e")]
	|"a"  -> [("u","a1");("r","a2")]
	|"b"  -> [("q","b1");("u","b2");("v","b3")]
	|"c"  -> [("q","c1");("u","c2")]
	|"d"  -> [("x","d1");("y","d2");("g","d3");("h","d4")]
	|"b2" -> [("s","b2a");("q","b2b")]
	|"d3" -> [("u","d3a");("s","d3b")]
	| _   -> [];;


(* evaluation de type 'a -> int : fonction d’évaluation qui renvoie un entier           *)
(* appartenant à l'intervalle [-INFINI,+INFINI]                                         *)

let evaluationA1
(e : 'a)
: int =
match e with
	|"a" -> 10
	|"b" -> -3
	|"c" -> 0
	|"d" -> -7
	|"e"  -> -4
	|"a1" -> 11
	|"a2" -> 7
	|"b1" -> 9
	|"b2" -> 13
	|"b3" -> 10
	|"c1" -> 7
	|"c2" -> 13
	|"d1" -> 11
	|"d2" -> 13
	|"d3" -> -12
	|"d4" -> 19
	|"b2a" -> -14
	|"b2b" -> 13
	|"d3a" -> 16
	|"d3b" -> -9
	| _    -> failwith "Erreur : evaluation : etat inconnu";;


(* ==================================================================================== *)


(* Arbre A2 --------------------------------------------------------------------------- *)

(* etatInitialA2 de type ‘a : l’état initial                                            *)
(* etatsFilsA2 de type 'a -> ('b * 'a) list : fonction qui associe à chaque état la     *)
(* liste des doublets (coup possible, état fils obtenu)                                 *)



let etatInitialA2 = "0";;

let etatsFilsA2
(e : 'a)
: ('b * 'a) list =
match e with
	"0"    -> [("q","a");("v","b");("r","c");("t","d");("p","e")]
	|"a"  -> [("u","a1");("r","a2")]
	|"b"  -> [("q","b1");("u","b2");("v","b3")]
	|"c"  -> [("q","c1");("u","c2")]
	|"d"  -> [("x","d1");("y","d2");("g","d3");("h","d4")]
	|"b2" -> [("s","b2a");("q","b2b")]
	|"d3" -> [("u","d3a");("s","d3b")]
	| _   -> [];;


(* evaluation de type 'a -> int : fonction d’évaluation qui renvoie un entier           *)
(* appartenant à l'intervalle [-INFINI,+INFINI]                                         *)

let evaluationA2
(e : 'a)
: int =
match e with
	|"a" -> 10
	|"b" -> -3
	|"c" -> 0
	|"d" -> -7
	|"e"  -> -4
	|"a1" -> 14
	|"a2" -> 13
	|"b1" -> 19
	|"b2" -> 10
	|"b3" -> 18
	|"c1" -> 17
	|"c2" -> 18
	|"d1" -> -3
	|"d2" -> 1
	|"d3" -> -12
	|"d4" -> 19
	|"b2a" -> -14
	|"b2b" -> 18
	|"d3a" -> 16
	|"d3b" -> -9
	| _    -> failwith "Erreur : evaluation : etat inconnu";;


(* ==================================================================================== *)


(* Arbre A3 --------------------------------------------------------------------------- *)

(* etatInitialA3 de type ‘a : l’état initial                                            *)
(* etatsFilsA3 de type 'a -> ('b * 'a) list : fonction qui associe à chaque état la     *)
(* liste des doublets (coup possible, état fils obtenu)                                 *)



let etatInitialA3 = "0";;

let etatsFilsA3
(e : 'a)
: ('b * 'a) list =
match e with
	"0"    -> [("t","a");("v","b");("r","c");("q","d");("p","e")]
	|"a"  -> [("u","a1");("r","a2")]
	|"b"  -> [("q","b1");("u","b2");("v","b3")]
	|"c"  -> [("q","c1");("u","c2")]
	|"d"  -> [("x","d1");("y","d2");("g","d3");("h","d4")]
	|"b2" -> [("s","b2a");("q","b2b")]
	|"d3" -> [("u","d3a");("s","d3b")]
	| _   -> [];;


(* evaluation de type 'a -> int : fonction d’évaluation qui renvoie un entier           *)
(* appartenant à l'intervalle [-INFINI,+INFINI]                                         *)

let evaluationA3
(e : 'a)
: int =
match e with
	|"a" -> 9
	|"b" -> -2
	|"c" -> 0
	|"d" -> -7
	|"e"  -> -4
	|"a1" -> 10
	|"a2" -> 6
	|"b1" -> 8
	|"b2" -> 12
	|"b3" -> 9
	|"c1" -> 6
	|"c2" -> 12
	|"d1" -> 10
	|"d2" -> 12
	|"d3" -> -12
	|"d4" -> 18
	|"b2a" -> -14
	|"b2b" -> 12
	|"d3a" -> 15
	|"d3b" -> -9
	| _    -> failwith "Erreur : evaluation : etat inconnu";;

minimax etatInitialA1 0 etatsFilsA1 evaluationA1;;
