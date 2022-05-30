module BinaryTree where
import Data.List --importing Data. List module to be able to use sort function

data Tree t = Empty | Leaf t | Node t ( Tree t ) ( Tree t )

instance (Show t) => Show (Tree t)  where
  show ( Empty ) = ""
  show ( Leaf t) = " "++(show t)
  show ( Node x lc rc) = (show x)++"/n |-"++(show lc)++"/n |-"++(show rc)

-------------------------------------------------------------------------
--Arboles binarios de busqueda
-------------------------------------------------------------------------

--Funcion empty: devuelve un arbol vacio, sin ningun elemento
empty :: a -> Tree a
empty _ = Empty

-- Funcion leaf: devuelve un árbol que consta de una única hoja que contiene el elemento x
leaf :: a -> Tree a
leaf a = Leaf a

--Funcion tree: devuelve un árbol que contiene en la raíz el elemento x, con hijo izquierdo lc e
--hijo derecho rc. Tanto el hijo izquierdo como el hijo derecho son nodos del árbol, no elementos del tipo
--de datos genérico
tree :: a -> Tree a -> Tree a -> Tree a
tree x lc rc = Node x (lc) (rc)


--Funcion size: Esta función devuelve el número de elementos del árbol
size :: Tree a -> Integer
size Empty = 0
size (Leaf t) = 1
size (Node x y z) = 1 + (size y) + (size z)

-------------------------------------------------------------------------
--Construccion de arboles binarios
-------------------------------------------------------------------------

--Funcion add: añadir un elemento a un arbol binario
add :: Ord a => Tree a -> a -> Tree a 
add Empty a = Leaf a --Arbol vacio + elemento = Hoja 
add (Leaf a) b  --Arbol con hoja: Caso de insertar en subarbol izq o der
    | b <= a = Node a (Leaf b) (Empty)
    | b > b  = Node a (Empty) (Leaf b)
add (Node x lc rc) b
    | b <= x = Node x (add lc b) rc --Si menor que la raiz, llamada recursiva en add del arbol inicial
    | b > x = Node x lc (add rc b)  --Si mayor que la raiz, ...

--Funcion build: crea un arbol vacio e inserta en el los elementos de una lista
build :: Ord a => [a] -> Tree a
build [] = Empty --Arbol vacio porque es lista vacia
build [a] = Leaf a --Arbol de un solo elemento
build a = buildAux a Empty


buildAux :: Ord a => [a] -> Tree a -> Tree a 
buildAux (x:xs) a = buildAux xs (add a x) 
buildAux (x:[]) a = add a x --Warning ? Pattern match is redundant

-------------------------------------------------------------------------
--Arboles binarios equilibrados
-------------------------------------------------------------------------

--ACABAR

buildBalanced :: Ord a => [a] -> Tree a
build [] = Empty --Arbol vacio porque es lista vacia
build [a] = Leaf a --Arbol de un solo elemento
build a = Node (media) (buildBalanced lc) (buildBalanced rc)
  where
    long = length a
    media = aux (sort a) long
    aux :: [a] -> Int -> a
    aux a long = snd(splitAt(long 'div' 2) a) !! 0
    lc = fst(splitAt(long 'div' 2) a)
    rc =  Data.List.delete media rcaux
    rcaux = snd(splitAt(long 'div' 2) a)




-------------------------------------------------------------------------
--Recorridos de arboles binarios
-------------------------------------------------------------------------

--Funcion que recorre en preorden el arbol y devuelve una lista en ese orden
preorder :: Ord a => Tree a -> [a]
preorder Empty = []
preorder (Leaf a) = [a]
preorder (Node x lc rc) = postorder lc ++ postorder rc ++ [x]

postorder :: Ord a => Tree a -> [a]
postorder Empty = []
postorder (Leaf a) = [a]
postorder (Node x lc rc) = postorder lc ++ postorder rc ++ [x]

inorder :: Ord a => Tree a -> [a]
inorder Empty = []
inorder (Leaf a) = [a]
inorder (Node x lc rc) = inorder lc ++ [x] ++ inorder rc

--ACABAR

balance :: Ord a => Tree a -> Tree a
balance a = buildBalanced (balanceAux a)
  where
    balanceAux :: Ord a => Tree a -> [a]
    balanceAux a = inorder a

-------------------------------------------------------------------------
--Busquedas
-------------------------------------------------------------------------
between :: Ord a => Tree a -> a -> a -> [a]
between Empty _ _ = []
between (Leaf t) xmin xmax = if (t >= xmin && t <= xmax ) then [t] else []
between (Node x lc rc) xmin xmax = if ( x < xmin ) then between rc xmin xmax
                                    else if ( x > xmax ) then between lc xmin xmax
                                    else if (x <= xmin ) then [x] ++ between rc xmin xmax 
                                    else if (x >= xmin ) then [x] ++ between lc xmin xmax 
                                    else between lc xmin xmax ++ [x] ++ between rc xmin xmax