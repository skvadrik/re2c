import Control.Monad    (forM_)
import Data.List        (intercalate)
import System.Directory (getDirectoryContents, removeFile, createDirectoryIfMissing)
import System.FilePath  (takeExtension, addExtension, combine)


genconfs2 :: String -> [String] -> [String]
genconfs2 conf vals = map (\val -> concat ["re2c:", conf, " = ", val, ";"]) vals

genconfs :: String -> [String] -> [String]
genconfs conf vals = "" : genconfs2 conf vals

eof_conf :: String
eof_conf = "re2c:eof = 0;"

body1 :: [String]
body1 =
    [ "[a] { a }"
    , "*   { x }"
    ]

body2 :: [String]
body2 =
    [ "<c1> [a] :=> c2"
    , "<c2> [b] :=> c1"
    , "<*> * { x }"
    ]

body3 :: [String]
body3 =
    [ "(@p [a])+ { a }"
    , "*         { x }"
    ]

cond_get_decorate :: (String, String, [[String]], [String])
cond_get_decorate =
    let name = "cond_get_decorate"
        ext = "ci"
        confs =
            [ genconfs "define:YYGETCONDITION:naked" ["0", "1"]
            , genconfs "decorate" ["0", "1"]
            ]
    in  (name, ext, confs, body2)

cond_set_decorate :: (String, String, [[String]], [String])
cond_set_decorate =
    let name = "cond_set_decorate"
        ext = "ci"
        confs =
            [ genconfs "define:YYSETCONDITION:naked" ["0", "1"]
            , genconfs "decorate" ["0", "1"]
            ]
    in  (name, ext, confs, body2)

cond_set_placeholder :: (String, String, [[String]], [String])
cond_set_placeholder =
    let name = "cond_set_placeholder"
        ext = "ci"
        confs =
            [ genconfs "define:YYSETCONDITION@cond" ["@@", "#"]
            , genconfs2 "placeholder" ["#", "@@"]
            , genconfs2 "define:YYSETCONDITION" ["\"cond = @@;\"", "\"cond = #;\""]
            ]
    in  (name, ext, confs, body2)

cond_goto_placeholder :: (String, String, [[String]], [String])
cond_goto_placeholder =
    let name = "cond_goto_placeholder"
        ext = "ci"
        confs =
            [ genconfs "cond:goto" ["\"goto #;\"", "\"goto @@;\""]
            , genconfs "cond:goto@cond" ["#", "@@"]
            , genconfs2 "placeholder" ["#", "@@"]
            ]
    in  (name, ext, confs, body2)

cond_divider_placeholder :: (String, String, [[String]], [String])
cond_divider_placeholder =
    let name = "cond_divider_placeholder"
        ext = "ci"
        confs =
            -- do not test default `cond:divider` as it has no placeholder
            [ genconfs2 "cond:divider" ["\"~~~ ## ~~~\"", "\"--- @@ --- @@ ---\""]
            , genconfs "cond:divider@cond" ["#", "@@"]
            , genconfs2 "placeholder" ["#", "@@"]
            ]
    in  (name, ext, confs, body2)

state_get_decorate :: (String, String, [[String]], [String])
state_get_decorate =
    let name = "state_get_decorate"
        ext = "fi"
        confs =
            [ genconfs2 "define:YYGETSTATE:naked" ["0", "1"]
            , genconfs2 "decorate" ["0", "1"]
            ]
    in  (name, ext, confs, body1)

state_set_decorate :: (String, String, [[String]], [String])
state_set_decorate =
    let name = "state_set_decorate"
        ext = "fi"
        confs =
            [ genconfs "define:YYSETSTATE:naked" ["0", "1"]
            , genconfs "decorate" ["0", "1"]
            ]
    in  (name, ext, confs, body1)

state_set_placeholder :: (String, String, [[String]], [String])
state_set_placeholder =
    let name = "state_set_placeholder"
        ext = "fi"
        confs =
            [ genconfs "define:YYSETSTATE@state" ["@@", "\"\xFF\""]
            , genconfs2 "placeholder" ["\"\xFF\"", "@@"]
            , genconfs2 "define:YYSETSTATE" ["\"state = @@;\"", "\"state = \xFF;\""]
            ]
    in  (name, ext, confs, body1)

tags_expr_placeholder :: (String, String, [[String]], [String])
tags_expr_placeholder =
    let name = "tags_expr_placeholder"
        ext = "i--tags"
        confs =
            [ genconfs "tags:expression" ["\"xyz->#\"", "\"@@\""]
            , genconfs "placeholder" ["#", "@@"]
            ]
    in  (name, ext, confs, body3)

fill_placeholder :: (String, String, [[String]], [String])
fill_placeholder =
    let name = "fill_placeholder"
        ext = "i"
        confs =
            [ genconfs "define:YYFILL@len" ["@@", "need"]
            , genconfs2 "placeholder" ["need", "@@"]
            , genconfs2 "define:YYFILL" ["\"fill(@@)\"", "\"fill(need);\""]
            ]
    in  (name, ext, confs, body1)

fill_decorate :: (String, String, [[String]], [String])
fill_decorate =
    let name = "fill_decorate"
        ext = "i"
        confs =
            [ genconfs "define:YYFILL:naked" ["0", "1"]
            , genconfs "yyfill:parameter" ["0", "1"]
            , genconfs "decorate" ["0", "1"]
            ]
    in  (name, ext, confs, body1)

fill_check :: (String, String, [[String]], [String])
fill_check =
    let name = "fill_check"
        ext = "i"
        confs = [ genconfs "yyfill:check" ["0", "1"] ]
    in  (name, ext, confs, body1)

fill_check_state :: (String, String, [[String]], [String])
fill_check_state =
    let (name, _, confs, body) = fill_check
    in  (name, "fi", confs, body)

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

wrap_re2c :: String -> [String] -> [String]
wrap_re2c kind xs = ["/*!" ++ kind] ++ xs ++ ["*/"]

gen_block :: [String] -> [String] -> [String]
gen_block body confs =
    let maybe_eof_rule = case elem eof_conf confs of
            True  -> ["$ { eof }"]
            False -> []
    in  concat [confs, maybe_eof_rule, body]

re2c_gen_block :: String -> [String] -> [String] -> String
re2c_gen_block kind body confs = unlines $ concat
    [ (map comment . nonempty) confs
    , ((wrap_re2c kind) . map indent . nonempty) (gen_block body confs)
    ]

re2c_block = re2c_gen_block "re2c"

re2c_rules_block body = re2c_gen_block "rules:re2c" body []

re2c_use_block confs = re2c_gen_block "use:re2c" [] confs

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

-- use "reuse" mode
gen3 :: (String, String, [[String]], [String]) -> IO ()
gen3 (name, ext, confs, body) = do
    writeFile (gen_fname name ("r" ++ ext) []) $
        let confgroups = map (snd . unzip) $ combine_confs confs
        in  unlines $ (re2c_rules_block body) : map re2c_use_block confgroups

gen4 :: (String, String, [[String]], [String]) -> IO ()
gen4 (name, ext, confs, body) = do
    writeFile (gen_fname name ext []) $
        let confgroups = map (snd . unzip) $ combine_confs confs
        in  unlines $ map (re2c_block body) confgroups

main :: IO ()
main = do
    cleanup

    gen3 cond_get_decorate
    gen3 cond_set_decorate
    gen3 cond_set_placeholder
    gen3 cond_goto_placeholder
    gen3 cond_divider_placeholder

    gen1 state_get_decorate
    gen4 state_set_decorate
    gen4 state_set_placeholder

    gen3 tags_expr_placeholder

    gen3 fill_check
    gen2 fill_check_state
    gen3 fill_placeholder
    gen3 fill_decorate
    gen3 $ eof_variant fill_check
    gen2 $ eof_variant fill_check_state
    gen3 $ eof_variant fill_placeholder
    gen3 $ eof_variant fill_decorate
