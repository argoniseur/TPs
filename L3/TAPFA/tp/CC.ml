let rec tete = function
    [] -> []
   |([])::l -> []
   |(e::l1)::l -> e::(tete l);;

let rec reste = function
    [] -> []
   |([])::l -> []
   |(e::l1)::l -> l1::(reste l);;

let rec trans m = match tete m with
    [] -> []
  | _ -> tete m::(trans (reste m));;

tete [[1;2;3];[4;5;6];[7;8;9]];;
reste [[1;2;3];[4;5;6];[7;8;9]];;
trans [[1;2;3];[4;5;6];[7;8;9]];;

let rec map f l = match l with
    [] -> []
  | e::x -> f e::(map f x);;

let tete2 = map List.hd;;
let reste2 = map List.tl;;

let zero n =
  let rec buildLx x acc = if x>0 then buildLx (x-1) (0::acc) else acc in
  let rec buildLy y acc = if y>0 then buildLy (y-1) ((buildLx n [])::acc) else acc in
  buildLy n [];;

zero 3;;

let rec unite x =
  let rec buildL i pos acc = if i=pos then buildL (i-1) pos (1::acc)
                             else if i>0 then buildL (i-1) pos (0::acc)
                             else acc in
  let rec buildC j acc = if j>0 then buildC (j-1) ((buildL x (j) [])::acc) else acc in
  buildC x [];;
unite 3;;

let rec map2 f x y = match (x, y) with
    ([], []) -> []
   |([], l) | (l, []) -> failwith "liste incompatibles"
   |(e1::l1, e2::l2) -> (f e1 e2)::(map2 f l1 l2);;

let somlig x y = map2 (+) x y;;
somlig [1;2;3] [3;2;1];;

let add m1 m2 = map2 somlig m1 m2;;
add [[1;2;3];[4;5;6];[7;8;9]] [[1;2;3];[4;5;6];[7;8;9]];;

let prodligcol x y = let rec sum = function
                         [] -> 0
                       |e::l -> e+(sum l) in 
                         sum (map2 (fun i j -> i*j) x y);;
prodligcol [1;2;3] [1;4;7];;
                           (*let rec prodligtmat x m = map2 prodligcol*)
