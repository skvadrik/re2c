#!/usr/bin/env bash

source "`dirname ${BASH_SOURCE[0]}`/../utils.sh"

if [[ $# -eq 0 ]]; then
  echo "Usage: $0 <git-branch-or-tag-name>"
  exit 1
fi

readonly buildDir="$gitRepoRoot/temp_build_playground"
readonly re2cBranchOrTagName="$1"

# Remove build artifacts from a previous build
rm -rf "$buildDir"
mkdir -p "$buildDir"
mkdir -p "$currentScriptDir/gen"

# Download and configure Emscripten
git clone --depth=1 https://github.com/emscripten-core/emsdk.git "$buildDir/emsdk"
"$buildDir/emsdk/emsdk" install latest
"$buildDir/emsdk/emsdk" activate latest
source "$buildDir/emsdk/emsdk_env.sh"

# Download and build re2c to generate "gen/re2c.js".
# Clone the repository fully because we need to get the nearest tag later to generate version.
git clone --branch "$re2cBranchOrTagName" --single-branch "$gitRepoUrl" "$buildDir/re2c"
# Flags with `-s` are Emscripten compile settings described: https://emscripten.org/docs/tools_reference/settings_reference.html
# Rationale why some flags are chosen:
# * INVOKE_RUN - we don't need re2c to start automatically when the page is loaded.
# * SINGLE_FILE - just a convenience. Otherwise, it will generate 2 files: js and wasm.
# * EXPORT_ES6 - produce a js module file. It is more convenient and doesn't pollute the global namespace when imported.
# * FORCE_FILESYSTEM - generate FileSystem functions because we need them to interact with re2c.
# * ALLOW_MEMORY_GROWTH - without this flag, re2c fails with an "out of memory" error for some examples.
# * EXTRA_EXPORTED_RUNTIME_METHODS - each method needs to be explicitly exposed. Otherwise, it will not be accessible from the javascript.
# * w - turn off warnings to not pollute the output.
emcmake cmake \
  -G Ninja \
  -S "$buildDir/re2c" \
  -B "$buildDir/re2c-build" \
  -D CMAKE_CXX_FLAGS=" \
    -s INVOKE_RUN=0 \
    -s SINGLE_FILE \
    -s ENVIRONMENT=web \
    -s EXPORT_ES6=1 \
    -s FORCE_FILESYSTEM=1 \
    -s ALLOW_MEMORY_GROWTH=1 \
    -s EXTRA_EXPORTED_RUNTIME_METHODS=[FS,callMain] \
    -w" \
  -D RE2C_BUILD_RE2D=0 \
  -D RE2C_BUILD_RE2GO=0 \
  -D RE2C_BUILD_RE2HS=0 \
  -D RE2C_BUILD_RE2JAVA=0 \
  -D RE2C_BUILD_RE2JS=0 \
  -D RE2C_BUILD_RE2OCAML=0 \
  -D RE2C_BUILD_RE2PY=0 \
  -D RE2C_BUILD_RE2RUST=0 \
  -D RE2C_BUILD_RE2V=0 \
  -D RE2C_BUILD_RE2ZIG=0 \
  -D RE2C_BUILD_TESTS=0
emmake cmake --build "$buildDir/re2c-build"
cp --force "$buildDir/re2c-build/re2c.js" "$currentScriptDir/gen/"

# Generate "gen/re2cExamples.js"
# The following code goes through all *.re files inside the re2c/examples folder and creates a javascript module like:
# export default {
#   "languageName": {
#     "exampleName": {
#       "content": "content of an example file",
#       "extraCommandLineArguments": "extra command line arguments needed for this example"
#     },
#     ...
# }
python3 - <<END
import json
import re
from pathlib import Path

examples_folder_full_name = "${buildDir}/re2c/examples"
re2c_examples_js_file_full_name = "${currentScriptDir}/gen/re2cExamples.js"

re2c_examples_data = {}
for example_file in list(Path(examples_folder_full_name).rglob("*.re")):
  # relative_path will have a value like "c/fill/01_fill.re"
  relative_path = example_file.relative_to(Path(examples_folder_full_name))

  # Split relative_path into two parts. The first part is always the name of the language.
  language_name = relative_path.parts[0]
  example_name = "/".join(relative_path.parts[1:])

  content = Path(example_file).read_text()

  # The first line of every example might contain extra command line arguments.
  # These lines look like "// re2v INPUT -o OUTPUT -i".
  # We take everything that is after "OUTPUT".
  # Special case: for Ocalm the line looks like "(* re2ocaml INPUT -o OUTPUT -i *)". Thus the "*)" needs to be ignored.
  match = re.search(r"OUTPUT ([^\)*]+)", content.splitlines()[0])
  re2cExtraCommandLineArgs = match.group(1) if match else ""

  re2c_examples_data.setdefault(language_name, {})[example_name] = { "content": content, "extraCommandLineArguments": re2cExtraCommandLineArgs }

# Deserialize the data into JSON and add "export default" to make it a Javascript module that can be imported using an "import" keyword.
json_data = "export default " + json.dumps(re2c_examples_data, indent=2)
with open(re2c_examples_js_file_full_name, 'w', encoding='utf-8') as f:
  f.write(json_data)
END

# Generate re2cVersion.js
readonly re2cShortGitCommitHash=`git -C "$buildDir/re2c" rev-parse --short HEAD`
readonly re2cNearestTagName=`git -C "$buildDir/re2c" describe --tags --abbrev=0`
echo "export default '$re2cNearestTagName~$re2cShortGitCommitHash'" > "$currentScriptDir/gen/re2cVersion.js"
