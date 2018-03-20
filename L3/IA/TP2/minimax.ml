let listeMax liste =
let rec aux accu = function 
	| [] -> accu
	| e::l -> if e>accu then (aux e l) else (aux accu l)
in aux (-10000) liste;;

let listeMin liste = 
let rec aux accu = function
	| [] -> accu
	| e::l -> if accu>e then (aux e l) else (aux accu l)
in aux 10000 liste;;



let rec minimax etatCourant profondeurCourante etatsFils evaluation =
	let coupsPoss = etatsFils etatCourant in
	if (coupsPoss = [])
			  then 
 					(evaluation etatCourant)
 			  else
 			  if (profondeurCourante mod 2) = 0 
 			  		then listeMax (List.fold_right (fun (coup,etat) l -> (minimax etat (profondeurCourante+1) etatsFils evaluation)::l) coupsPoss [])
 			  		else listeMin (List.fold_right (fun (coup,etat) l -> (minimax etat (profondeurCourante+1) etatsFils evaluation)::l) coupsPoss []);;
 			  		

let rec recherche profondeurMaximale etatCourant profondeurCourante etatsFils evaluation =
	let coupsPoss = etatsFils etatCourant in
	if ((profondeurCourante=profondeurMaximale) || (coupsPoss = [])) 
		then 
 		(evaluation etatCourant)
 	else
 		if (profondeurCourante mod 2 = 0)  
 			  		then listeMax (List.fold_right (fun (coup,etat) l -> (recherche profondeurMaximale etat (profondeurCourante+1) etatsFils evaluation)::l) coupsPoss [])
 			  		else listeMin (List.fold_right (fun (coup,etat) l -> (recherche profondeurMaximale etat (profondeurCourante+1) etatsFils evaluation)::l) coupsPoss []);;
 			  		

let meilleurCoup profondeurMaximale etatCourant profondeurCourante etatsFils evaluation =
	let recherche_res = recherche profondeurMaximale etatCourant profondeurCourante etatsFils evaluation in
	let rec aux = function
	| [] -> 0, " "
	| (coup,etat)::l -> if recherche_res <> (recherche profondeurMaximale etat (profondeurCourante+1) etatsFils evaluation)
		then aux l 
		else (recherche_res,coup)
	in aux (etatsFils etatCourant);;


