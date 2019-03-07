import Control.Monad       (forM_)
import Data.List           (intercalate)
import System.Directory    (getDirectoryContents, removeFile, createDirectoryIfMissing)
import System.FilePath     (takeExtension, addExtension, combine)

confs_cond_set :: (String, [[(Int, String)]], String, String)
confs_cond_set =
    let cond_set =
            [ ""
            , "re2c:define:YYSETCONDITION = \"YYSETCONDITION\";"
            , "re2c:define:YYSETCONDITION = \"cond = @@;\";"
            , "re2c:define:YYSETCONDITION = \"setcondition (#);\";"
            ]
        cond_set_arg =
            [ ""
            , "re2c:define:YYSETCONDITION@cond = @@;"
            , "re2c:define:YYSETCONDITION@cond = #;"
            ]
        cond_set_naked =
            [ ""
            , "re2c:define:YYSETCONDITION:naked = 0;"
            , "re2c:define:YYSETCONDITION:naked = 1;"
            ]
        confs =
            [ [x1, x2, x3]
            | x1 <- zip [1 .. length cond_set]       cond_set
            , x2 <- zip [1 .. length cond_set_arg]   cond_set_arg
            , x3 <- zip [1 .. length cond_set_naked] cond_set_naked
            ]
        body = unlines
            [ "    <c1> \"a\" => c2 { code1 }"
            , "    <c2> \"b\" => c1 { code2 }"
            , "    <*> * { def }"
            ]
        ext = ".ci"
    in  ("cond_set", confs, body, ext)

confs_state_set :: (String, [[(Int, String)]], String, String)
confs_state_set =
    let state_set =
            [ ""
            , "re2c:define:YYSETSTATE = \"YYSETSTATE\";"
            , "re2c:define:YYSETSTATE = \"state = @@;\";"
            , "re2c:define:YYSETSTATE = \"setstate_\xFF;\";"
            ]
        state_set_arg =
            [ ""
            , "re2c:define:YYSETSTATE@state = @@;"
            , "re2c:define:YYSETSTATE@state = \"\xFF\";"
            ]
        state_set_naked =
            [ ""
            , "re2c:define:YYSETSTATE:naked = 0;"
            , "re2c:define:YYSETSTATE:naked = 1;"
            ]
        confs =
            [ [x1, x2, x3]
            | x1 <- zip [1 .. length state_set]       state_set
            , x2 <- zip [1 .. length state_set_arg]   state_set_arg
            , x3 <- zip [1 .. length state_set_naked] state_set_naked
            ]
        body = unlines
            [ "    \"a\" { code }"
            , "    * { def }"
            ]
        ext = ".fi"
    in  ("state_set", confs, body, ext)

confs_fill :: (String, [[(Int, String)]], String, String)
confs_fill =
    let fill =
            [ ""
            , "re2c:define:YYFILL = \"YYFILL\";"
            , "re2c:define:YYFILL = \"fill (@@)\";"
            , "re2c:define:YYFILL = \"fill (@@);\";"
            , "re2c:define:YYFILL = \"{ YYFILL (need); }\";"
            ]
        fill_arg =
            [ ""
            , "re2c:define:YYFILL@len = @@;"
            , "re2c:define:YYFILL@len = need;"
            ]
        fill_arg_use =
            [ ""
            , "re2c:yyfill:parameter = 0;"
            , "re2c:yyfill:parameter = 1;"
            ]
        fill_naked =
            [ ""
            , "re2c:define:YYFILL:naked = 0;"
            , "re2c:define:YYFILL:naked = 1;"
            ]
        confs =
            [ [x1, x2, x3, x4]
            | x1 <- zip [1 .. length fill]         fill
            , x2 <- zip [1 .. length fill_arg]     fill_arg
            , x3 <- zip [1 .. length fill_arg_use] fill_arg_use
            , x4 <- zip [1 .. length fill_naked]   fill_naked
            ]
        body = unlines
            [ "    \"a\" { code }"
            , "    * { def }"
            ]
        ext = ".i"
    in  ("fill", confs, body, ext)

content :: [String] -> String -> String
content xs body =
    let ys = filter (/= "") xs
    in  unlines
            [ "/* autogen */"
            , unlines $ map ("// " ++) ys
            , "/*!re2c"
            , unlines $ map ("    " ++) ys
            , body
            , "*/"
            ]

gen :: (String, [[(Int, String)]], String, String) -> IO ()
gen (name, confs, body, ext) = do
    createDirectoryIfMissing False name
    files <- getDirectoryContents name
    let cleanup =
            ( map (combine name)
            . filter (\f -> takeExtension f == ".re")
            ) files
    mapM_ removeFile cleanup
    forM_ confs $ \ conf -> do
        let (xs, ys) = unzip conf
            file =
                ( combine name
                . (`addExtension` ".re")
                . (`addExtension` ext)
                . intercalate "_"
                . map show
                ) xs
        writeFile file $ content ys body

main :: IO ()
main = do
    let groups =
            [ confs_cond_set
            , confs_state_set
            , confs_fill
            ]
    mapM_ gen groups
