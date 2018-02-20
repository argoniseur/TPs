open List;;

(* 1 *)
(*
1 - map
2 - filter
3 - fold
 *)

type etudiant = Etd of string * int * int * int list;;

let nom = function Etd(n,g,a,ln) -> n;;
let groupe = function Etd(n,g,a,ln) -> g;;
let anneeNaissance = function Etd(n,g,a,ln) -> a;;
let listeNotes = function Etd(n,g,a,ln) -> ln;;

(* A *)
(* a *)
let moyenne = fun etd -> match
                           fold_left (fun (a,nbNotes) e -> (a+e,nbNotes+1)) (0,0) (listeNotes etd)
                         with (a,n) -> if n <> 0 then a/n else failwith "aucune note";;

(* b *)
(* 
liste les etudiants qui ont au moins une note en dessous de 10
 *)

(* c *)
let requeteC listEtd = map nom (filter (fun etd -> moyenne etd < 10) listEtd);;

(* d *)
let requeteD listEtd = let maxG2 = fold_left (fun a e -> let moyE = moyenne e in
                                                      if a > moyE && groupe e = 2 then a
                                                      else moyE) 0 listEtd
                       in
                       fold_left (fun a e -> if groupe e = 1 && moyenne e > maxG2 then e::a else a)
                         [] listEtd;;

(* B *)
let rec produit l1 l2 =
  let rec putEveryoneBehind e = function
      [] -> []
    | e1::l1 -> (e,e1) :: putEveryoneBehind e l1
  in
  match l1 with
    [] -> []
  | e::l -> putEveryoneBehind e l2 @ produit l l2;; 

(* 3 *)
(* a *)
let somme n =
  let rec sommeI n accu = if n < 1 then accu else sommeI (n-1) (n+accu)
  in
  sommeI n 0;;

(* b *)
let reverse list =
    let rec aux acc = function
      | [] -> acc
      | h::t -> aux (h::acc) t
    in
    aux [] list;;

let elim e l =
  let rec elimI e l accu = match l with
      [] -> accu
    | e1::l1 -> let newAccu = if e = e1 then accu else e1::accu
                in
                elimI e l1 newAccu
  in
  elimI e (reverse l) [];;

(* c *)
let elim2 e l = fold_right (fun e1 a -> if e1 = e then a else e1::a) l [];;
let elim3 e l = fold_left (fun a e1 -> if e1 = e then a else e1::a) [] (reverse l);;

(*temps: O(n) pour les deux
memoire: O(n) pour les deux (a verifier)
pile: O(1) pour fold_left 
      O(n) pour fold_right*)

(* 4 *)
(* a *)
(*
('a -> bool) -> ('a -> 'b -> 'b) -> 'a list -> 'b -> 'b
 *)

(* b *)
let rec foldrFilter p opb l a = match l with
    [] -> a
  | e::l1 -> let newA = if p e then opb e a else a in
             foldrFilter p opb l1 newA;;

(* c *)
let sommePos l = foldrFilter (fun a -> a > 0) (+) l 0;;

(* d *)
let foldrFilter p opb l a = fold_right (fun e a -> if p e then opb e a else a) l a;;

(* 5 *)
(* a *)
(*
31
 *)

(* b *)
let test_somme l = fold_right (fun e a -> let som = e+a in
                                          if som < 0 then failwith "somme negative" else som) l 0;;
