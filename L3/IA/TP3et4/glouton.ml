open List;;

let g1 = ["WA","NA" ; "WA","SA" ; "NA","SA" ; "NA","Q" ; "SA","Q" ; "SA","V" ; "SA","NSW" ; "Q","NSW" ; "NSW","V" ];;

let rec adjacent graphe sommet1 sommet2 = match graphe with
	|[] -> false
	|(s1,s2)::l -> if s1 = sommet1 && s2 = sommet2
					then true
					else adjacent l sommet1 sommet2;;

adjacent g1 "WA" "NA";;
adjacent g1 "V" "Q";;

let rec print_list_string = function
[] -> print_string "\n"
| x::reste -> print_string x;print_string " ";print_list_string reste;;


let splitList graphe = let l = List.split graphe in
			match l with
			|([], _) -> failwith "Liste vide"
			|(a, b) -> a@b;;

let sommetGraphe graphe = List.sort_uniq compare (splitList graphe);;

print_list_string (sommetGraphe g1);;

let rec voisinsDouble graphe sommet = match graphe with
	|[] -> []
	|(s1, s2)::l -> if s1 = sommet then s2::(voisinsDouble l sommet)
					else if s2 = sommet then s1::(voisinsDouble l sommet)
						else voisinsDouble l sommet;;

voisinsDouble g1 "WA";;
