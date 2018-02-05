let nom = "de FERLUC" and prenom = "Louis";;


module type tENV = sig
type ('var, 'valeur) env
val empty : ('var, 'valeur) env
val get : ('var, 'valeur) env -> 'var -> 'valeur
val put : ('var, 'valeur) env -> 'var -> 'valeur -> ('var, 'valeur) env
end;;

module Env : tENV = struct
	type ('var, 'valeur) env = VIDE | LIAISON of ('var * 'valeur) *
('var, 'valeur) env
	let empty = VIDE
	let rec get env_donne variable = match env_donne with LIAISON ((var,valeur), nouveau_env) -> if var = variable then valeur else
get nouveau_env variable | VIDE -> failwith "Error"
	let put env_donne nouvelle_var nouvelle_valeur = LIAISON ((nouvelle_var,nouvelle_valeur),env_donne)
end;;

type expr =
| Variable of string
| Constante of int
| AppelFonction of (int -> int -> int) * expr * expr
| Alternative of expr * expr * expr
| Definition of string * expr * expr;;


let rec eval env = function
	| Variable s -> Env.get env s
	| Constante ent -> ent
	| AppelFonction (fonction_ent, expr1, expr2) -> fonction_ent (eval env expr1) (eval env expr2)
	| Alternative (expr1, expr2, expr3) -> if (eval env expr1) > 0 then (eval env expr2) else (eval env expr3)
	| Definition (s, valeur, expr1) -> eval (Env.put env s (eval env valeur)) expr1;;


let rec member elem = function
	|[] -> false
	|e::l -> if e = elem then true else member elem l;;

let rec union l1 l2 = match l1 with
	|[] -> l2
	|e::l -> if member e l2 then union l2 l else e::union l2 l;;


let rec listeVars = function
	| Variable s -> s::[]
	| Constante _ -> []
	| AppelFonction (_, expr1, expr2) -> union (listeVars expr1) (listeVars expr2)
	| Alternative (expr1, expr2, expr3) -> union (union (listeVars expr1) (listeVars expr2)) (listeVars expr3)
	| Definition (s, expr1, expr2) -> let l = union (listeVars expr1) (listeVars expr2) in if (member s l) then l else s::l;;


let rec supprime elem = function
	|[] -> []
	|e::l -> if e = elem then supprime elem l else e::supprime elem l;;


let rec listeVarsLibres = function 
	| Variable s -> s::[]
	| Constante _ -> []
	| AppelFonction (_, expr1, expr2) -> union (listeVarsLibres expr1) (listeVarsLibres expr2)
	| Alternative (expr1, expr2, expr3) -> union (union (listeVarsLibres expr1) (listeVarsLibres expr2)) (listeVarsLibres expr3)
	| Definition (s, expr1, expr2) -> union (listeVarsLibres expr1) (supprime s (listeVarsLibres expr2));;

let rec eliminer env = function
	| Variable s -> eliminer env (Env.get env s)
	| Constante ent -> Constante ent
	| AppelFonction (fonction, expr1, expr2) -> AppelFonction (fonction, (eliminer env expr1), (eliminer env expr2))
	| Alternative (expr1, expr2, expr3) -> Alternative ((eliminer env expr1),(eliminer env expr2),(eliminer env expr3))
	| Definition (s, expr1, expr2) -> eliminer (Env.put env s (eliminer env expr1)) expr2;;