
import qualified Test.QuickCheck as Q
import qualified Test.QuickCheck.Monadic as QM
import qualified System.Process as SP
import qualified System.Exit as SE
import qualified Data.ByteString.Char8 as BS


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
    Empty   -> "\"\""
    NA      -> "[^a]"
    NB      -> "[^b]"
    NC      -> "[^c]"
    Alt l r -> "(" ++ show l ++ "|" ++ show r ++ ")"
    Cat l r -> "(" ++ show l ++ show r ++ ")"
    Star e  -> "(" ++ show e ++ ")*"
    Plus e  -> "(" ++ show e ++ ")+"
    Mayb e  -> "(" ++ show e ++ ")?"
    FromTo n m e -> "(" ++ show e ++ "){" ++ show n ++ "," ++ show m ++ "}"
    From   n   e -> "(" ++ show e ++ "){" ++ show n ++ ",}"

instance Q.Arbitrary E where
    arbitrary = do
        d <- Q.choose (2, 4) :: Q.Gen Int
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
    n <- Q.choose (0, 1) :: Q.Gen Int
    m <- Q.choose (if n < 2 then n + 1 else n, 3) :: Q.Gen Int
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


prop_test_re2c :: E -> E -> Q.Property
prop_test_re2c r1 r2 = QM.monadicIO $ do
    let re_file = unlines [ "/*!re2c"
                          , show r1 ++ " {}"
                          , show r2 ++ " {}"
                          , "\"\" {}"
                          , "*/"
                          ]
        re2c = "../re2c"

    s0 <- QM.run $ do BS.writeFile "a.re" $ BS.pack re_file
                      SP.system $ "ulimit -t 20 && " ++ re2c ++ " --no-lookahead --posix-captures -Werror-undefined-control-flow -ST a.re -o a.c 2>>re2c_last_warning || exit 42 && cp a.c b.c"

    s1 <- QM.run $ do BS.writeFile "a.re" $ BS.pack re_file
                      SP.system $ "ulimit -t 10 && " ++ re2c ++ "                --posix-captures -Werror-undefined-control-flow -ST a.re -o a.c 2>>re2c_last_warning || exit 42 && gcc a.c -o a && ./a && gcc b.c -o b && ./b"

    QM.assert $ s0 `elem` [SE.ExitSuccess, SE.ExitFailure 42]
    QM.assert $ s1 `elem` [SE.ExitSuccess, SE.ExitFailure 42]


main :: IO ()
main = Q.quickCheckWith Q.stdArgs { Q.maxSuccess = 1000000 } prop_test_re2c
