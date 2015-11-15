import qualified Snap.Http.Server    as Snap
import qualified Snap.Util.FileServe as Snap

main :: IO ()
main =
    let config
            = Snap.setPort      8000
            $ Snap.setAccessLog Snap.ConfigNoLog
            $ Snap.setErrorLog  Snap.ConfigNoLog
            $ Snap.emptyConfig
    in  Snap.httpServe config $ Snap.serveDirectory "obj/src"

