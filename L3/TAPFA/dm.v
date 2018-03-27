Require Import List.
Import ListNotations.
Require Import Omega.
Require Import String.
Set Implicit Arguments.

Module Type TODO.
  Inductive expr :=
    | EConst : nat -> expr
    | EVar : string -> expr
    | EPlus : expr -> expr -> expr
    | EMult : expr -> expr -> expr.
  Inductive op := Plus | Mult.
  Inductive instr :=
    | Const : nat -> instr
    | Var : string -> instr
    | Op : op -> instr.

  Parameter trans : expr -> list instr.
  Parameter parse : list instr -> expr.
  Parameter eval_expr : (string -> nat) -> expr -> nat.
  Parameter eval_instrs : (string -> nat) -> list instr -> nat.
  Parameter optim_instrs : list instr -> list instr.

  Axiom trans_correct:
    forall env e, eval_expr env e = eval_instrs env (trans e).
  Axiom parse_correct:
    forall e, parse (trans e) = e.
  Axiom optim_correct:
    forall env il, eval_instrs env il = eval_instrs env (optim_instrs il).
End TODO.

Module TEST(R: TODO).
  Definition