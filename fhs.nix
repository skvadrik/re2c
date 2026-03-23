{ pkgs ? import <nixpkgs> {} }:

let e =
  pkgs.buildFHSEnv {
    name = "re2c-ghpages-build-env";
    targetPkgs = ps: with ps; [
      # certs for SSL
       cacert

      # tools
      cmake
      git
      ninja
      python3

      # libraries
      zlib
    ];
  };
in e.env
