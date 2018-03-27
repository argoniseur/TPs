open List;;

let g1 = ["WA","NA" ; "WA","SA" ; "NA","SA" ; "NA","Q" ; "SA","Q" ; "SA","V" ; "SA","NSW" ; "Q","NSW" ; "NSW","V" ];;

let rec adjacent graphe sommet1 sommet2 = match graphe with
	|[] -> false
	|(s1,s2)::l -> if s1 = sommet1 && s2 = sommet2
					then true
					else adjacent l sommet1 sommet2;;
					
let rec suppDoublons = function
    |[] -> []
    |x::l -> if List.exists (fun y -> x=y) l then suppDoublons l else x::(suppDoublons l);;

let sommetGraphe graphe = let(l1,l2) = List.split graphe in suppDoublons (l1@l2);;

let rec voisinsDouble graphe sommet = match graphe with
	|[] -> []
	|(s1, s2)::l -> if s1 = sommet then s2::(voisinsDouble l sommet)
					else if s2 = sommet then s1::(voisinsDouble l sommet)
						else voisinsDouble l sommet;;

let g2 = ["A","B" ; "A","E" ; "B","C" ; "B","D" ; "B","E" ; "C","D" ; "D","E"];;

(*
let rec testerCouleur lv sommet nbCouleur = match lv with
	|
	|

let backtrack graphe nbCouleur =
	let rec trait sg nbCouleur nbEchec listeSommetColorier = match sg with
		|[] -> (listeSommetColorier, nbEchec)
		|s::resteSommet -> if 
	in let sg = sommetGraphe graphe
		in trait sg nbCouleur 0 [];;
*)
