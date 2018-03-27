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


let rec colorSom coloration s =  
    match coloration with 
    |[] -> 0 
    |(s1,c)::l -> if (s1 = s) then c else colorSom l s;;

let colorVois g coloration s = 
    let rec aux acc = function 
        |[] -> acc 
        |v::l -> let c = colorSom coloration v in if (c = 0) then aux acc l else aux (c::acc) l 
    in aux [] (voisinsDouble g s);;


let attributColor g s coloration =  
    let rec attCol color = if (List.exists (fun e -> e =color) (colorVois g coloration s)) then attCol (color+1) else color 
    in attCol 1;;
    

let gloutonSansH graphe =  
    let rec g coloration nColor order = function 
        |[] -> (coloration,nColor,order) 
        |s::l -> let c = (attributColor graphe s coloration) in g (coloration@[(s,c)]) (if (c>nColor) then c else nColor) (order@[s]) l 
    in g [] 0 [] (sommetGraphe graphe) 
;;

let nombreVoisinNonColor g s c = 
    let rec aux acc = function 
        |[] -> acc 
        |e::l -> if (colorSom c e) =0 then aux acc l else aux (acc+1) l 
    in List.length(voisinsDouble g s)-(aux 0 (voisinsDouble g s)) 
;;

let nbVoisins s g = List.length(voisinsDouble g s);;

let gloutonDeg graphe =  
    let rec g coloration nColor order = function 
        |[] -> (coloration,nColor,order) 
        |s::l -> let c = (attributColor graphe s coloration) in g (coloration@[(s,c)]) (if (c>nColor) then c else nColor) (order@[s]) l 
    in g [] 0 [] (List.sort (fun x y -> (nbVoisins y graphe)-(nbVoisins x graphe)) (sommetGraphe graphe)) 
;;

let nombreColorVoisine g s c = List.length (colorVois g c s);; 
 
let score g c s = 1000*(nombreColorVoisine g s c)+(nombreVoisinNonColor g s c);; 
 
let gloutonDSat graphe =  
    let rec g coloration nColor order = function 
        |[] -> (coloration,nColor,order) 
        |s::l -> let c = (attributColor graphe s coloration) in g (coloration@[(s,c)]) (if (c>nColor) then c else nColor) (order@[s])(List.sort (fun x y -> (score graphe coloration y)-(score graphe coloration x)) l) 
    in g [] 0 [] (List.sort (fun x y -> (score graphe [] y)-(score graphe [] x)) (sommetGraphe graphe)) 
;;
