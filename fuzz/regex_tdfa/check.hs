
import qualified Test.QuickCheck as Q
import qualified Test.QuickCheck.Monadic as QM
import qualified System.Process as SP
import qualified System.Exit as SE
import qualified Data.ByteString.Char8 as BS
import           Data.Char (ord)
import qualified Text.Regex.TDFA as X
import qualified Data.Array as A
import           Control.Monad (when)


data E = A | B | C
       | Empty
       | NA | NB | NC
       | Alt E E
       | Cat E E
       | Star E
       | Plus E
       | Mayb E
       | FromTo Int Int E
       | From   Int     E


instance Show E where
  show x = case x of
    A       -> "[a]"
    B       -> "[b]"
    C       -> "[c]"
    Empty   -> "(\"\")"
    NA      -> "[^a]"
    NB      -> "[^b]"
    NC      -> "[^c]"
--    Alt l r -> show l ++ "|" ++ show r
    Alt l r -> "(" ++ show l ++ "|" ++ show r ++ ")"
--    Cat l r -> show l ++ show r
    Cat l r -> "(" ++ show l ++ show r ++ ")"
    Star e  -> "(" ++ show e ++ ")*"
    Plus e  -> "(" ++ show e ++ ")+"
    Mayb e  -> "(" ++ show e ++ ")?"
    FromTo n m e -> "(" ++ show e ++ "){" ++ show n ++ "," ++ show m ++ "}"
    From   n   e -> "(" ++ show e ++ "){" ++ show n ++ ",}"


show_posix :: E -> String
show_posix x = case x of
    A       -> "[a]"
    B       -> "[b]"
    C       -> "[c]"
    Empty   -> "()"
    NA      -> "[^a]"
    NB      -> "[^b]"
    NC      -> "[^c]"
--    Alt l r -> show_posix l ++ "|" ++ show_posix r
    Alt l r -> "(" ++ show_posix l ++ "|" ++ show_posix r ++ ")"
--    Cat l r -> show_posix l ++ show_posix r
    Cat l r -> "(" ++ show_posix l ++ show_posix r ++ ")"
    Star e  -> "(" ++ show_posix e ++ ")*"
    Plus e  -> "(" ++ show_posix e ++ ")+"
    Mayb e  -> "(" ++ show_posix e ++ ")?"
    FromTo n m e -> "(" ++ show_posix e ++ "){" ++ show n ++ "," ++ show m ++ "}"
    From   n   e -> "(" ++ show_posix e ++ "){" ++ show n ++ ",}"


instance Q.Arbitrary E where
    arbitrary = do
        d <- Q.choose (2,4) :: Q.Gen Int
        arbitrary_d d


arbitrary_d :: (Enum a, Eq a, Num a) => a -> Q.Gen E
arbitrary_d 0 = do
    Q.frequency
        [ (1, pure Empty)
        , (1, pure A)
        , (1, pure B)
        , (1, pure C)
        , (1, pure NA)
        , (1, pure NB)
        , (1, pure NC)
        ]


arbitrary_d d = do
    n <- Q.choose (0,1) :: Q.Gen Int
    m <- Q.choose (if n == 0 then 1 else n, 3) :: Q.Gen Int
    Q.frequency
        [ (1, pure Empty)
        , (1, pure A)
        , (1, pure B)
        , (1, pure C)
        , (1, pure NA)
        , (1, pure NB)
        , (1, pure NC)
        , (30,  Alt <$> arbitrary_d d' <*> arbitrary_d d')
        , (30,  Cat <$> arbitrary_d d' <*> arbitrary_d d')
        , (10, Star <$> arbitrary_d d')
        , (10, Plus <$> arbitrary_d d')
        , (10, Mayb <$> arbitrary_d d')
        , (10, FromTo n m <$> arbitrary_d d')
        , (10, From   n   <$> arbitrary_d d')
        ]
        where d' = pred d


parse_input :: Int -> IO [(BS.ByteString, [Int], [BS.ByteString], X.MatchArray)]
parse_input ncaps = do
    let step :: BS.ByteString -> BS.ByteString -> (BS.ByteString, [Int], [BS.ByteString], X.MatchArray, BS.ByteString)
        step input key =
            let ns'@(n1:n2:_:ns) = reverse $ BS.foldl' (\xs c -> ord c : xs) [] key
                s = BS.take n2 input
                ss = split ns s
                ar = A.listArray (0, ncaps) (split2 ns s)
                rest = BS.drop n1 input
            in (s, ns', ss, ar, rest)

        go :: [BS.ByteString] -> BS.ByteString -> [(BS.ByteString, [Int], [BS.ByteString], X.MatchArray)]
        go [] _ = []
        go (key:keys) input =
            let (s, ns, ss, ar, rest) = step input key
            in (s, ns, ss, ar) : go keys rest

        split :: [Int] -> BS.ByteString -> [BS.ByteString]
        split [] _ = []
        split (n1:n2:ns) s = (BS.drop n1 . BS.take n2) s : split ns s
        split _ _ = error "uneven number of keys"

        split2 :: [Int] -> BS.ByteString -> [(Int, Int)]
        split2 [] _ = []
        split2 (n1:n2:ns) s = case (n1, n2) of
            (255, 255)                 -> (-1, 0) : split2 ns s
            _ | n1 /= 255 && n2 /= 255 -> (n1, n2 - n1) : split2 ns s
            _                          -> error $ "bad re2c result: " ++ show (n1, n2)
        split2 _ _ = error "uneven number of keys"

        split_at :: Int -> BS.ByteString -> [BS.ByteString]
        split_at _ s | s == BS.empty = []
        split_at n s | BS.length s < n = error "bad tail"
        split_at n s = BS.take n s : split_at n (BS.drop n s)

        ncaps' = 2 * (ncaps + 1) + 3

    input <- BS.readFile "a.c.line1.input"
    keys <- split_at ncaps' <$> BS.readFile "a.c.line1.keys"
    return $ go keys input


prop_test_re2c :: E -> Q.Property
prop_test_re2c r1 = QM.monadicIO $ do
    let portable_empty = "[a]{0}"
        re_file = "/*!re2c " ++ show r1 ++ "|" ++ portable_empty ++ " {} */"
        re_posix = "^" ++ show_posix r1 ++ "|" ++ portable_empty
        rr = X.makeRegex re_posix :: X.Regex
        ncaps = length $ filter (== '(') re_posix
        re2c = "../re2c"

    ok0 <- QM.run $ do
        BS.writeFile "a.re" $ BS.pack re_file
        SP.system $ "ulimit -t 10 && " ++ re2c
            ++ " --posix-captures -Werror-undefined-control-flow -ST a.re -o a.c 2>>re2c_last_warning"
            ++ " || exit 42 && gcc a.c -o a && ./a"
    QM.assert $ ok0 `elem` [SE.ExitSuccess, SE.ExitFailure 42]
    when (ok0 == SE.ExitFailure 42) $ do
        QM.run $ print re_posix
    when (ok0 == SE.ExitSuccess) $ do
        ss <- QM.run $ parse_input ncaps
        mapM_ (\(s, ns, xs, ar) -> do
                let s1 = map BS.unpack xs
                    s2 = ((\x -> if x == [] then [] else head x) . X.match rr . BS.unpack) s
                    ar' = (X.match rr . BS.unpack) s :: X.MatchArray
                    ok = (ar == ar' && s1 == s2) || (BS.filter (== '\n') s) /= BS.empty
                QM.run $ when (not ok) $ do
                    print re_posix
                    print ncaps
                    print $ BS.unpack s
                    print ns
                    print s1
                    print s2
                    print ar
                    print ar'
                QM.assert ok
            ) ss


main :: IO ()
main = Q.quickCheckWith Q.stdArgs { Q.maxSuccess = 1000000 } prop_test_re2c
