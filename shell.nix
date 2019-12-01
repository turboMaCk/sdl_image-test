{ pkgs ? import <nixpkgs> {} }:
with pkgs;
mkShell {
  buildInputs = [
    gcc
    gdb
    SDL2
    SDL2_image
  ];
}
