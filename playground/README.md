It is a web playground that allows users to try re2c in their browser.

# Implementation details
* The website is client-only
* It uses re2c executable compiled into javascript using Emscripten (the compilation is done by `build.sh` script)
* [Ace.js](https://ace.c9.io/) is used as a code editor

# How to develop the website
* Run `build.sh <git-branch-or-tag-name>` script to update the generated files in the `gen/` folder.
* Open the `index.html` file locally using `python3 -m http.server 8080` command or using any IDE of your choice.

# References
There are similar websites that we used as inspiration:
* https://yhirose.github.io/cpp-peglib/
* https://peggyjs.org/online.html
* https://dreampuf.github.io/GraphvizOnline
