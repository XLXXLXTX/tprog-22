Module BinaryTree where

data Tree t = Empty | Leaf t | Nodo t ( Tree t ) ( Tree t )

instance Show Tree where
show (Empty) = "<>\n"
show (Leaf t) = t++"\n"
show (Node t lc rc) = t ++ "\n|-" ++ show(lc) ++ "\n|-" ++ show(rc)

--Funcion empty: devuelve un arbol vacio, sin ningun elemento
empty :: Tree 
empty = Empty

-- Funcion leaf: devuelve un árbol que consta de una única hoja que contiene el elemento x
leaf :: a -> Tree
leaf a = Leaf a

--Funcion tree: devuelve un árbol que contiene en la raíz el elemento x, con hijo izquierdo lc e
--hijo derecho rc. Tanto el hijo izquierdo como el hijo derecho son nodos del árbol, no elementos del tipo
--de datos genérico
tree :: a -> Tree -> Tree -> Tree
tree x lc rc = Nodo x (lc) (rc)


--Funcion size: Esta función devuelve el número de elementos del árbol
size :: Tree -> Integer
size Empty = 0
| size (Leaf t) = 1
| size (Node x y z) = 1 + size (x) + size(z)


--jodeme mas

