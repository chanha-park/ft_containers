{-# OPTIONS_GHC -Wall -Wextra -Werror #-}

-- Referece:
-- https://doi.org/10.1017/S0956796899003494
-- https://abhiroop.github.io/Haskell-Red-Black-Tree/
-- https://opendatastructures.org/ods-java/9_2_RedBlackTree_Simulated_.html
-- https://azrael.digipen.edu/~mmead/www/Courses/CS280/Trees-Mapping2-3-4IntoRB.html
-- https://stackoverflow.com/questions/35955246/converting-a-2-3-4-tree-into-a-red-black-tree
-- https://www.cs.purdue.edu/homes/ayg/CS251/slides/chap13b.pdf

empty :: Tree a
empty = E

-- type Set a = Tree a

member :: Ord a => a -> Tree a -> Bool
member _ E = False
member x (Tree _ a y b)
  | x < y = member x a
  | x > y = member x b
  | otherwise = True

data Color = Red | Black
  deriving (Show)

data Tree a = E | Tree Color (Tree a) a (Tree a)
  deriving (Show)

balance :: Color -> Tree a -> a -> Tree a -> Tree a
balance Black (Tree Red (Tree Red a x b) y c) z d = Tree Red (Tree Black a x b) y (Tree Black c z d)
balance Black (Tree Red a x (Tree Red b y c)) z d = Tree Red (Tree Black a x b) y (Tree Black c z d)
balance Black a x (Tree Red (Tree Red b y c) z d) = Tree Red (Tree Black a x b) y (Tree Black c z d)
balance Black a x (Tree Red b y (Tree Red c z d)) = Tree Red (Tree Black a x b) y (Tree Black c z d)
balance col a x b = Tree col a x b

makeBlack :: Ord a => Tree a -> Tree a
makeBlack E = E
makeBlack (Tree _ a y b) = Tree Black a y b

insert :: Ord a => a -> Tree a -> Tree a
insert x = makeBlack . ins
  where
    ins E = Tree Red E x E
    ins (Tree col a y b)
      | x < y = balance col (ins a) y b
      | x > y = balance col a y (ins b)
      | otherwise = Tree col a y b

-- insert x s = makeBlack . ins $ s

delete :: Ord a => a -> Tree a -> Tree a
delete x s = makeBlack (del x s)

del :: Ord a => a -> Tree a -> Tree a
del _ E = E
del x t@(Tree _ a y b)
  | x < y = delL x t
  | x > y = delR x t
  | otherwise = fuse a b
  where
    delL = undefined
    delR = undefined
    fuse = undefined
