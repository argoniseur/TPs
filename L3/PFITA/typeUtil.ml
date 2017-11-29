type couleur = Bleu|Blanc|Rouge;;

let r = Rouge;;

type carte = Un|Deux|Trois|Quatre|Cinq|Six|Sept|Huit|Neuf|Dix|Valet|Dame|Roi;;

type nombre = Entier of int | Reel of float | Complexe of (float*float);;



type ('a,'b) afnd = Afnd of 'a * ('a -> 'b -> 'a list) * ('a -> bool);;

type monAutomate = Afnd of int * (int -> char -> int list) * (int -> bool);;

type binaryTree = Feuille|binaryTree
