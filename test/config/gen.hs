import Control.Monad    (forM_)
import Data.List        (intercalate)
import System.Directory (getDirectoryContents, removeFile, createDirectoryIfMissing)
import System.FilePath  (takeExtension, addExtension, combine)


genconfs2 :: String -> [String]
genconfs2 conf =
    [ "re2c:" ++ conf ++ " = 0;"
    , "re2c:" ++ conf ++ " = 1;"
    ]

genconfs :: String -> [String]
genconfs conf = "" : genconfs2 conf

eof_conf :: String
eof_conf = "re2c:eof = 0;"

body1 :: [String]
body1 =
    [ "[a] { a }"
    , "*   { x }"
    ]

body2 :: [String]
body2 =
    [ "<c1> [a] => c2 { a }"
    , "<c2> [b] => c1 { b }"
    , "<*> *          { x }"
    ]

cond_get_decorate :: (String, String, [[String]], [String])
cond_get_decorate =
    let name = "cond_get_decorate"
        ext = ".ci"
        confs =
            [ genconfs2 "define:YYGETCONDITION:naked"
            , genconfs2 "decorate"
            ]
    in  (name, ext, confs, body2)

cond_set_param :: (String, String, [[String]], [String])
cond_set_param =
    let name = "cond_set_param"
        ext = ".ci"
        confs =
            [ [ "re2c:define:YYSETCONDITION = \"cond = @@;\";"
              , "re2c:define:YYSETCONDITION = \"cond = #;\";"
              ]
            , ["", "re2c:define:YYSETCONDITION@cond = #;"]
            ]
    in  (name, ext, confs, body2)

cond_set_decorate :: (String, String, [[String]], [String])
cond_set_decorate =
    let name = "cond_set_decorate"
        ext = ".ci"
        confs =
            [ genconfs "define:YYSETCONDITION:naked"
            , genconfs "decorate"
            ]
    in  (name, ext, confs, body2)

state_get_decorate :: (String, String, [[String]], [String])
state_get_decorate =
    let name = "state_get_decorate"
        ext = ".fi"
        confs =
            [ genconfs2 "define:YYGETSTATE:naked"
            , genconfs2 "decorate"
            ]
    in  (name, ext, confs, body1)

state_set_param :: (String, String, [[String]], [String])
state_set_param =
    let name = "state_set_param"
        ext = ".fi"
        confs =
            [ [ "re2c:define:YYSETSTATE = \"state = @@;\";"
              , "re2c:define:YYSETSTATE = \"state = \xFF;\";"]
            , ["", "re2c:define:YYSETSTATE@state = \"\xFF\";"]
            ]
    in  (name, ext, confs, body1)

state_set_decorate :: (String, String, [[String]], [String])
state_set_decorate =
    let name = "state_set_decorate"
        ext = ".fi"
        confs =
            [ genconfs "define:YYSETSTATE:naked"
            , genconfs "decorate"
            ]
    in  (name, ext, confs, body1)

fill :: (String, String, [[String]], [String])
fill =
    let name = "fill"
        ext = ".i"
        confs =
            [ [ "re2c:define:YYFILL = \"fill(@@)\";"
              , "re2c:define:YYFILL = \"fill(need);\";"
              ]
            , ["", "re2c:define:YYFILL@len = need;"]
            , genconfs2 "yyfill:check"
            ]
    in  (name, ext, confs, body1)

fill_state :: (String, String, [[String]], [String])
fill_state =
    let (name, _, confs, body) = fill
    in  (name, ".fi", confs, body)

fill_decorate :: (String, String, [[String]], [String])
fill_decorate =
    let name = "fill_decorate"
        ext = ".i"
        confs =
            [ genconfs "define:YYFILL:naked"
            , genconfs "yyfill:parameter"
            , genconfs "decorate"
            ]
    in  (name, ext, confs, body1)

eof_variant :: (String, String, [[String]], [String])
            -> (String, String, [[String]], [String])
eof_variant (name, ext, confs, body) =
    let name'  = name ++ "_eof"
        confs' = [eof_conf] : confs
    in  (name', ext, confs', body)

combine_confs :: [[String]] -> [[(Int, String)]]
combine_confs xss =
    let g xs = zip [1 .. length xs] xs
        f []       ys = ys
        f (xs:xss) ys = f xss $ case ys of
            [] -> [[x] | x <- g xs]
            _  -> [x:y | x <- g xs, y <- ys]
    in  f (reverse xss) []

indent :: String -> String
indent = ("  " ++)

comment :: String -> String
comment =("// " ++)

nonempty :: [String] -> [String]
nonempty = filter (/= "")

wrap_re2c :: [String] -> [String]
wrap_re2c xs = ["/*!re2c"] ++ xs ++ ["*/"]

gen_block :: [String] -> [String] -> [String]
gen_block body confs =
    let maybe_eof_rule = case elem eof_conf confs of
            True  -> ["$ { eof }"]
            False -> []
    in  concat [confs, maybe_eof_rule, body]

re2c_block :: [String] -> [String] -> String
re2c_block body confs = unlines $ concat
    [ (map comment . nonempty) confs
    , (wrap_re2c . map indent . nonempty) (gen_block body confs)
    ]

gendirname :: String
gendirname = "autogen"

gen_fname :: String -> String -> [Int] -> String
gen_fname name ext numbers =
    ( combine gendirname
    . (`addExtension` ".re")
    . (`addExtension` ext)
    . intercalate "_"
    . (name:)
    . map show
    ) numbers

cleanup :: IO ()
cleanup = do
    createDirectoryIfMissing False gendirname
    files <- getDirectoryContents gendirname
    mapM_ removeFile $
        ( map (combine gendirname)
        . filter (\f -> takeExtension f == ".re")
        ) files

gen1 :: (String, String, [[String]], [String]) -> IO ()
gen1 (name, ext, confs, body) = do
    forM_ (combine_confs confs) $ \confgroup -> do
        let (numbers, confs) = unzip confgroup
        writeFile (gen_fname name ext numbers) $
           re2c_block body confs

gen2 :: (String, String, [[String]], [String]) -> IO ()
gen2 (name, ext, confs, body) = do
    forM_ (combine_confs confs) $ \confgroup -> do
        let (numbers, confs) = unzip confgroup
        writeFile (gen_fname name ext numbers) $
           re2c_block body confs

gen3 :: (String, String, [[String]], [String]) -> IO ()
gen3 (name, ext, confs, body) = do
    writeFile (gen_fname name ext []) $
        let confgroups = map (snd . unzip) $ combine_confs confs
        in  unlines $ map (re2c_block body) confgroups

main :: IO ()
main = do
    cleanup

    gen1 cond_get_decorate
    gen2 cond_set_param
    gen3 cond_set_decorate

    gen1 state_get_decorate
    gen2 state_set_param
    gen3 state_set_decorate

    gen2 fill
    gen2 fill_state
    gen3 fill_decorate
    gen2 $ eof_variant fill
    gen2 $ eof_variant fill_state
    gen3 $ eof_variant fill_decorate
