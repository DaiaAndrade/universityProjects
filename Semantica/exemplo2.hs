--22Out
data Arvore = Nodo Int Arvore Arvore | Folha Int
				deriving(Eq, Show)


arv1 :: Arvore 
arv1 = Nodo 3 (Nodo 9 (Folha 2) (Folha 2)) (Nodo 7 (Folha 1) (Folha 33))

arv2 :: Arvore
arv2 = Nodo 6 (Folha 1) (Nodo 44 (Folha 97) (Folha 92))

somaArvore :: Arvore -> Int
somaArvore (Folha n) = n
somaArvore (Nodo n a1 a2) = n + somaArvore a1 + somaArvore a2

arvoreLista :: Arvore -> [Int]
arvoreLista (Folha n) = [n]
arvoreLista (Nodo n a1 a2) = n : arvoreLista a1 ++ arvoreLista a2

refleteArvore :: Arvore -> Arvore
refleteArvore (Folha n) = Folha n
refleteArvore (Nodo n a1 a2) = Nodo n (refleteArvore a2) (refleteArvore a1)

data E = Num Int | Soma E E | Mult E E
			deriving (Eq, Show)
prog1 :: E
prog1 = Mult (Soma (Num 3) (Num 4)) (Soma (Num 2) (Num 1))

bigStep :: E -> Int
bigStep (Num n) = n
bigStep (Soma e1 e2) = bigStep e1 + bigStep e2
bigStep (Mult e1 e2) = bigStep e1 * bigStep e2

data B = TRUE | FALSE | Nao B | And B B | Ou B B
		deriving (Eq, Show)

bigStep2 :: B -> Bool
bigStep2 TRUE = True
bigStep2 FALSE = False
bigStep2 (Nao TRUE) = False
bigStep2 (Nao FALSE) = True
bigStep2 (Nao b) = not (bigStep2 b)
bigStep2 (And TRUE b2) = bigStep2 b2
bigStep2 (And FALSE _) = False
bigStep2 (And b1 b2) = (bigStep2 b1) && (bigStep2 b2)
bigStep2 (Ou TRUE _) = True
bigStep2 (Ou FALSE b2) = bigStep2 b2
bigStep2 (Ou b1 b2) = (bigStep2 b1) || (bigStep2 b2)

prog2 :: B
prog2 = Nao (Ou (And (TRUE) (FALSE)) (And (FALSE) (FALSE)))
