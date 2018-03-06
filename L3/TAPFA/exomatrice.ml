(* 1 - transposition d'une matrice *)

let l = [[1;2;3];[4;5;6];[7;8;9]];;

let rec premier = function
	|[] -> failwith "liste vide"
	| e::l -> e;;

let rec tete = function
	| [] -> []
	| e::l -> (premier e)::(tete l);;
tete l;;

let fin = function
  |[] -> []
  |e::l -> l;;

let rec reste = function
  |[] -> []
  |e::l -> (fin e)::(reste l);;
reste l;;

let rec trans = function
  |[]::_ -> []
  |l -> (tete l)::(trans (reste l));;
trans l;;

(* 2 - fonctionnelle map *)
let l = [1;2;3;4;5;6;7;8;9];;

let rec map f = function
  |[] -> []
  |e::l -> (f e)::(map f l);;
map ((+) 1) l;;

let add0 = function
  |l -> 0::l;;

let rec zero = function
  |0 -> []
  |n -> let m = zero (n-1) in (add0 (tete m))::(map add0 m);;
zero 4;;

let rec buildligne = function
  |0 -> []
  |n -> let l = buildligne (n-1) in 0::l;;

let rec unite = function
  |0 -> []
  |n -> let m = unite (n-1) in (1::(buildligne (n-1)))::(map add0 m);;
unite 4;;

(* 3 - Addition de deux matrices *)

let l1 = [1;2;3;4;5;6];;
let l2 = [1;2;3;4;5;6];;
let rec map2 f l1 l2 = match (l1,l2) with
  |([],[]) -> []
  |([],l2) -> failwith "listes de longueur différentes"
  |(l1,[]) -> failwith "listes de longueur différentes"              
  |(e1::l1,e2::l2) -> (f e1 e2)::(map2 f l1 l2);;

let somlig l1 l2 = map2 (+) l1 l2;;
somlig l1 l2;;  

let rec add m1 m2 = match (m1,m2) with
  |([],[]) -> []
  |([],l2) -> failwith "listes de longueur différentes"
  |(l1,[]) -> failwith "listes de longueur différentes"
  |(e1::m1,e2::m2) -> (somlig e1 e2)::(add m1 m2);;
