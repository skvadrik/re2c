#!/bin/sh

# On NixOS, Wine cannot find DLLs by their absolute paths in /nix/store,
# so find and copy them in the same directory with re2c.exe.

uname -a | grep -q NixOS || exit 0

test -e re2c.exe || \
    { echo "$0 must be ran from the build directory containing re2c.exe"; exit 1; }

nix_wine="$(nix-build --no-link '<nixpkgs>' -A wine)"
nix_mcfgthreads="$(nix-build --no-link '<nixpkgs>' -A pkgsCross.mingw32.windows.mcfgthreads)"

uname -a | grep -q NixOS && (
    cp -f "$nix_mcfgthreads/bin/mcfgthread"*".dll" .
    cp -f "$nix_wine/lib/wine/i386-windows/win32u.dll" .
    cp -f "$nix_wine/lib/wine/i386-windows/user32.dll" .
    cp -f "$nix_wine/lib/wine/i386-windows/gdi32.dll" .
)
