# universityProjects
--Exercicio1
data Arvore = Nodo Int Arvore Arvore | Folha 
				deriving(Eq, Show)


arvore1 :: Arvore 
arvore1 = Nodo 3 (Nodo 2 Folha Folha) (Nodo 4(Nodo 5 Folha Folha) (Nodo 6 Folha Folha))

multArvore :: Arvore -> Arvore
multArvore Folha = Folha
multArvore (Nodo x a1 a2) = (Nodo (2*x) (multArvore a1) (multArvore a2))

--Exercicio2
maior :: Arvore -> Int
maior Folha = 0
maior (Nodo x a1 a2) = (max x (max (maior a1) (maior a2)))

