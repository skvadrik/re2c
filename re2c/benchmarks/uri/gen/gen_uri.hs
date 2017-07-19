{-# LANGUAGE LambdaCase #-}

import qualified Test.QuickCheck as Q
import qualified Test.QuickCheck.Monadic as QM
import qualified System.Random as SR
import qualified System.Process as SP
import qualified System.Exit as SE
import qualified Data.ByteString.Char8 as BS
import           Data.Char (chr)
import           Data.List (intercalate)
import           Control.Monad (forM_, when, replicateM)
import           Data.Foldable (foldlM)

type Scheme = String
type User = String
type Password = String
type Host = String
type Port = String
type Path = String
type Query = String
type Fragment = String
data URI = URI Scheme User Password Host Port Path Query Fragment

instance Show URI where
    show (URI sc us pw ho po pa qu fr) = concat
        [ sc
        , ":"
        , if ho == "" then "" else "//"
        , us
        , if us == "" then "" else ":"
        , pw
        , if pw == "" then "" else "@"
        , ho
        , if po == "" then "" else ":"
        , po
        , pa
        , if qu == "" then "" else "?"
        , qu
        , if fr == "" then "" else "#"
        , fr
        ]

lalpha = ['a'..'z']
ualpha = ['A'..'Z']
alpha = lalpha ++ ualpha
digit = ['0'..'9']
hexdigit = ['a'..'f'] ++ ['A'..'F'] ++ digit
alphanum = alpha ++ digit

lstr :: Q.Gen String
lstr = Q.listOf1 (Q.elements lalpha) :: Q.Gen [Char]

anstr :: Q.Gen String
anstr = Q.listOf1 (Q.elements alphanum) :: Q.Gen [Char]

ipv4 :: Q.Gen String
ipv4 = do
    let octet = show <$> (Q.choose (0,255) :: Q.Gen Int)
    intercalate "." <$> replicateM 4 octet

ipv6 :: Q.Gen String
ipv6 = do
    let hexgroup = do
            k <- Q.choose (1, 4) :: Q.Gen Int
            replicateM k (Q.elements hexdigit)
    n <- Q.choose (0, 8) :: Q.Gen Int
    m <- Q.choose (1, n) :: Q.Gen Int
    hh <- replicateM n hexgroup
    return $ (++ "]") . ("[" ++) $ case n of
        8 -> intercalate ":" hh
        _ -> concat [intercalate ":" (take m hh), "::", intercalate ":" (drop m hh)]

hostname :: Q.Gen String
hostname = do
    subdomains <- Q.listOf1 (take 10 <$> lstr)
    return $ intercalate "." $ take 5 subdomains

filepath :: Q.Gen String
filepath = do
    subdirs <- Q.listOf1 lstr
    return $ concat $ map ("/" ++) $ take 10 subdirs

mayb :: Q.Gen String -> Q.Gen String
mayb gen = Q.oneof [gen, pure ""]

instance Q.Arbitrary URI where
    arbitrary = do
        scheme   <- Q.elements ["http", "https", "ftp", "file"]
        user     <- lstr
        password <- anstr
        host     <- Q.frequency [(10, ipv4), (10, hostname), (1, ipv6)]
        port     <- mayb $ show <$> (Q.choose (0, 10000) :: Q.Gen Int)
        path     <- filepath
        query    <- mayb anstr
        fragment <- mayb anstr

        Q.frequency
            [ (1, pure $ URI scheme user  password host port path query fragment)
            , (2, pure $ URI scheme ""    ""       host port path query fragment)
            , (1, pure $ URI scheme ""    ""       ""   ""   path query fragment)
            ]

main = do
    let f = "uri.dat"
    writeFile f ""

    forM_ [0..600000] $ \i -> do
        when (i `mod` 100 == 0) $ print i

        uri <- Q.generate (Q.arbitrary :: Q.Gen URI)
        appendFile f $ show uri ++ "\n"
