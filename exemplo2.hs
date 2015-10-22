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
