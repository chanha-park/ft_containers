{-# OPTIONS_GHC -Wall -Wextra -Werror #-}

-- Referece:
-- https://doi.org/10.1017/S0956796899003494
-- https://abhiroop.github.io/Haskell-Red-Black-Tree/
-- https://opendatastructures.org/ods-java/9_2_RedBlackTree_Simulated_.html
-- https://azrael.digipen.edu/~mmead/www/Courses/CS280/Trees-Mapping2-3-4IntoRB.html
-- https://stackoverflow.com/questions/35955246/converting-a-2-3-4-tree-into-a-red-black-tree
-- https://www.cs.purdue.edu/homes/ayg/CS251/slides/chap13b.pdf

data Color = Red | Black
  deriving (Show)

data Tree a = E | Tree Color (Tree a) a (Tree a)
  deriving (Show)

instance Functor Tree where
  fmap _ E = E
  fmap f (Tree col l x r) = Tree col (fmap f l) (f x) (fmap f r)

-- instance Applicative Tree where
--   pure f = Tree Black E f E
--   (<*>) _ _ = E

empty :: Tree a
empty = E

member :: Ord a => a -> Tree a -> Bool
member _ E = False
member x (Tree _ a y b)
  | x < y = member x a
  | x > y = member x b
  | otherwise = True

getColor :: Ord a => Tree a -> Color
getColor E = Black
getColor (Tree x _ _ _) = x

getHeight :: Ord a => Tree a -> Integer
getHeight E = 0
getHeight (Tree _ l _ r) = 1 + max (getHeight l) (getHeight r)

getBlackHeight :: Ord a => Tree a -> Integer
getBlackHeight E = 0
getBlackHeight (Tree Red l _ r) = max (getBlackHeight l) (getBlackHeight r)
getBlackHeight (Tree Black l _ r) = 1 + max (getBlackHeight l) (getBlackHeight r)

compareHeight :: Ord a => Tree a -> ((Integer, Integer), (Integer, Integer))
compareHeight E = ((0, 0), (0, 0))
compareHeight (Tree _ l _ r) = ((getHeight l, getHeight r), (getBlackHeight l, getBlackHeight r))

-- isBalanced :: Ord a => Tree a -> Bool
-- isBalanced E = True
-- isBalanced (Tree _ l _ r) = (abs (getHeight l - getHeight r)) <= 1

balance :: Color -> Tree a -> a -> Tree a -> Tree a
balance Black (Tree Red (Tree Red a x b) y c) z d = Tree Red (Tree Black a x b) y (Tree Black c z d)
balance Black (Tree Red a x (Tree Red b y c)) z d = Tree Red (Tree Black a x b) y (Tree Black c z d)
balance Black a x (Tree Red (Tree Red b y c) z d) = Tree Red (Tree Black a x b) y (Tree Black c z d)
balance Black a x (Tree Red b y (Tree Red c z d)) = Tree Red (Tree Black a x b) y (Tree Black c z d)
balance col a x b = Tree col a x b

--             z
--         y         d      ->            y
--    x       c                      x          z
--   a b                          a    b     c      d

--             z
--         x         d      ->            y
--    a       y                      x          z
--           b c                  a    b     c      d

--             x
--         a         z      ->            y
--                 y   d             x          z
--                b c             a    b     c      d

--             x
--         a         y      ->            y
--                b    z             x          z
--                    c d         a    b     c      d

balance' :: Color -> Tree a -> a -> Tree a -> Tree a
-- Imperative version
-- color flips
balance' Black (Tree Red a@(Tree Red _ _ _) x b) y (Tree Red c z d) = Tree Red (Tree Black a x b) y (Tree Black c z d)
balance' Black (Tree Red a x b@(Tree Red _ _ _)) y (Tree Red c z d) = Tree Red (Tree Black a x b) y (Tree Black c z d)
balance' Black (Tree Red a x b) y (Tree Red c@(Tree Red _ _ _) z d) = Tree Red (Tree Black a x b) y (Tree Black c z d)
balance' Black (Tree Red a x b) y (Tree Red c z d@(Tree Red _ _ _)) = Tree Red (Tree Black a x b) y (Tree Black c z d)

--       y                                Ry
--  Rx          Rz        ->         x         z
-- Ra b       c  d                  a b       c d

--       y                                Ry
--  Rx          Rz        ->         x         z
-- a Rb       c  d                  a b       c d

--       y                                Ry
--  Rx          Rz        ->         x         z
-- a b        Rc  d                 a b       c d

--       y                                Ry
--  Rx         Rz        ->          x         z
-- a b        c  Rd                 a b       c d

-- single rotations
balance' Black (Tree Red a@(Tree Red _ _ _) x b) y c = Tree Black a x (Tree Red b y c)
balance' Black a x (Tree Red b y c@(Tree Red _ _ _)) = Tree Black (Tree Red a x b) y c

--       y                              x
--  Rx         c        ->          a         Ry
-- Ra b                                      b  c

--       x                              y
--   a       Ry          ->        Rx         c
--          b Ra                  a  b

-- double rotations
balance' Black (Tree Red a x (Tree Red b y c)) z d = Tree Black (Tree Red a x b) y (Tree Red c z d)
balance' Black a x (Tree Red (Tree Red b y c) z d) = Tree Black (Tree Red a x b) y (Tree Red c z d)

--       z                              y
--   Rx       d          ->        Rx          Rz
--  a  Ry                         a  b        c  d
--    b  c

--       x                              y
--   a         Rz          ->      Rx          Rz
--          Ry    d               a  b        c  d
--         b  c

-- no balancing
balance' col a x b = Tree col a x b

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

inOrder :: (Ord a, Show a) => Tree a -> IO ()
inOrder E = return ()
inOrder (Tree col l x r) = inOrder l >> (putStr . show $ col) >> (putStr ": ") >> (putStrLn . show $ x) >> inOrder r

-- insert from last element of the list
listToTree :: Ord a => [a] -> Tree a
listToTree = foldr insert E
