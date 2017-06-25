data Exp = Num Int | TRUE | FALSE | Var String | Soma Exp Exp
 | Mult Exp Exp | And Exp Exp | Or Exp Exp | Not Exp | IF Exp Exp Exp
 | Ap Exp Exp | Fun String Tipo Exp | Let String Tipo Exp Exp
 deriving (Eq,Show)
data Tipo = INT | BOOL | F Tipo Tipo
 deriving (Eq, Show)

bigStep :: Exp -> Exp
bigStep (Num e) = Num e
bigStep TRUE = TRUE
bigStep FALSE = FALSE
bigStep (Var "x") = (Var "x")
bigStep (Fun x t e) = (Fun x t e)


-- expressões numéricas
-- ATENÇÃO: não mudar a identação
bigStep (Soma e1 e2) = let
 (Num n1) = bigStep e1
 (Num n2) = bigStep e2
                       in Num (n1+n2)

bigStep (Mult e1 e2) = let
 (Num n1) = bigStep e1
 (Num n2) = bigStep e2
                       in Num (n1*n2)
-- expressões booleanas
bigStep (Not b)
 |b == TRUE = FALSE
 |otherwise = TRUE

bigStep (And b1 b2)
 |b1 == FALSE = FALSE
 |otherwise = bigStep b2

bigStep (Or b1 b2)
 |b1 == TRUE = TRUE
 |otherwise = bigStep b2

-- comandos
bigStep (IF b1 e1 e2)
 |b1 == TRUE = bigStep e1
 |otherwise = bigStep e2


bigStep (Ap (Fun x _ e1) e2) = bigStep (subs x (bigStep e2) e1)
bigStep (Ap e1 e2) = bigStep (Ap (bigStep e1) e2)

bigStep (Let x _ e1 e2) = bigStep (subs x (bigStep e1) e2)

-- testes artiméticos
testeSoma :: Exp
testeSoma = Soma (Num 4) (Num 12)

testeMult :: Exp
testeMult = Mult (Num 4) (Num 3)

testeSomMult :: Exp
testeSomMult = Mult (testeSoma) (testeMult)

-- testes lógicos
testeBool :: Exp
testeBool = Not (Or (And (TRUE) (FALSE)) (And (FALSE) (FALSE)))

-- testes de comandos
testeIf :: Exp
testeIf = IF TRUE testeSoma testeMult

testeAp :: Exp
testeAp = Ap (IF TRUE (Fun "x" INT (Soma (Var "x") (Num 1))) (Fun "x" INT (Soma (Var "x") (Num 2)))) (Num 2)

testeLet :: Exp
testeLet = (Let "x" (F INT INT) (Fun "x" INT (Soma (Var "x") (Num 1))) (Ap (Var "x") (Num 10)))

testeFun :: Exp
testeFun = Ap (Fun "x" INT (Soma (Var "x") (Num 2))) (Num 2)

subs :: String -> Exp -> Exp -> Exp

subs var val (Soma exp1 exp2) = Soma (subs var val exp1) (subs var val exp2)
subs var val (Mult exp1 exp2) = Mult (subs var val exp1) (subs var val exp2)
subs var val (And exp1 exp2) = And (subs var val exp1) (subs var val exp2)
subs var val (Or exp1 exp2) = Or (subs var val exp1) (subs var val exp2)
subs var val (Not exp1) = Not (subs var val exp1)
subs var val (IF b exp1 exp2) = IF (subs var val b) (subs var val exp1) (subs var val exp2)
subs var val (Let x t exp1 exp2) = Let x t (subs var val exp1) (subs var val exp2)
subs var val (Ap exp1 exp2) = Ap (subs var val exp1) (subs var val exp2)
subs var val (Fun x t exp1) = Fun x t (subs var val exp1)

subs x y (Var a)
 | a == x    = y
 | otherwise = (Var a)

subs x y (Num d) = (Num d)
subs x y TRUE = TRUE
subs x y FALSE = FALSE