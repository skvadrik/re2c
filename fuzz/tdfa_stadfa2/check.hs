
import qualified Test.QuickCheck as Q
import qualified Test.QuickCheck.Monadic as QM
import qualified System.Process as SP
import qualified System.Exit as SE
import qualified Data.ByteString.Char8 as BS
import           Data.Char (chr)
import           Control.Monad (when)


data E = A | B | C
       | Empty
       | NA | NB | NC
       | Tag String
       | HTag String
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
    Tag s   -> "@t_" ++ s
    HTag s  -> "#t_" ++ s
    Alt l r -> "(" ++ show l ++ "|" ++ show r ++ ")"
    Cat l r -> "(" ++ show l ++ show r ++ ")"
    Star e  -> "(" ++ show e ++ ")*"
    Plus e  -> "(" ++ show e ++ ")+"
    Mayb e  -> "(" ++ show e ++ ")?"
    FromTo n m e -> "(" ++ show e ++ "){" ++ show n ++ "," ++ show m ++ "}"
    From   n   e -> "(" ++ show e ++ "){" ++ show n ++ ",}"

instance Q.Arbitrary E where
    arbitrary = do
        d <- Q.choose (2, 5) :: Q.Gen Int
        arbitrary_d d


arbitrary_d :: (Enum a, Eq a, Num a) => a -> Q.Gen E
arbitrary_d 0 = do
    tag <- take 5 <$> Q.infiniteListOf (Q.choose (97, 122) :: Q.Gen Int)
    Q.frequency
        [ (1, pure Empty)
        , (1, pure A)
        , (1, pure B)
        , (1, pure C)
        , (1, pure NA)
        , (1, pure NB)
        , (1, pure NC)
        , (2, pure $ Tag $ map chr tag)
        , (2, pure $ HTag $ map chr tag)
        ]
arbitrary_d d = do
    n <- Q.choose (0, 3) :: Q.Gen Int
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
        re2c_flags = " -Werror-undefined-control-flow -ST " -- ++ "--posix-captures "
        cxx = "gcc"
        cxx_flags = " -Werror=incompatible-pointer-types "

    QM.run $ do
        BS.writeFile "a.re" $ BS.pack re_file

    s0 <- QM.run $ do
        SP.system $ concat
            [ "ulimit -t 10 && "
            , re2c ++ re2c_flags ++ " --stadfa a.re -o a.c 2>>re2c_last_warning "
            , "&& " ++ cxx ++ cxx_flags ++ " a.c -o a && ./a "
            , "&& cp a.c b.c"
            ]

    s1 <- QM.run $ do
        SP.system $ concat
            [ "ulimit -t 10 && "
            , re2c ++ re2c_flags ++ " a.re -o a.c 2>>re2c_last_warning "
            , "&& " ++ cxx ++ cxx_flags ++ " a.c -o a && ./a "
            ]
    QM.assert $ s0 `elem` [SE.ExitSuccess, SE.ExitFailure 137]
    QM.assert $ s1 `elem` [SE.ExitSuccess, SE.ExitFailure 137]

    when (s0 == SE.ExitSuccess && s1 == SE.ExitSuccess) $ do
        s01 <- QM.run $ do
            SP.system "s='#define YYKEYTYPE'; a=`grep \"$s\" a.c`; b=`grep \"$s\" b.c`; test \"$a\" = \"$b\""
        when (s01 == SE.ExitSuccess) $ do
            s2 <- QM.run $ do
                SP.system $ concat
                    [ "ulimit -t 10 && "
                    , cxx ++ cxx_flags ++ " b.c -o b && ./b "
                    ]
            QM.assert $ s2 == SE.ExitSuccess


main :: IO ()
main = Q.quickCheckWith Q.stdArgs { Q.maxSuccess = 1000000 } prop_test_re2c
