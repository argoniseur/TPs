type elem = Obstacle | Objet | Vide;;

(* elem *)
type prop =
    CaseOccupe of elem
  | PinceVide
  | Conjonc of (prop * prop)
  | Negation of prop;;

let exemple obj = Conjonc(CaseOccupe obj, PinceVide);;

let it_prop = fun fCaseOccupe -> fun fPinceVide -> fun fConjonc -> fun fNegation ->
                let rec trait = function
                  |CaseOccupe elem -> fCaseOccupe elem
                   |PinceVide -> fPinceVide
                   |Conjonc (prop1, prop2) -> fConjonc (prop1, prop2) (trait prop1) (trait prop2)
                   |Negation prop -> fNegation prop (trait prop)
                in trait;;

(*# val it_prop : (elem -> 'a) -> 'a -> (prop * prop -> 'a -> 'a -> 'a) -> (prop -> 'a -> 'a) -> prop -> 'a = <fun> *)
                                                                                                                  
type plateau = (int * int) -> elem;;

type etat = EtatRobot of plateau * (int * int) * bool * (int * int);;

let eval = it_prop 
