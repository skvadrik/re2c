#!/bin/bash

if [[ "${BASH_SOURCE[0]}" == "${0}" ]]; then
  echo "This script must be sourced. Use 'source ${0}' to use this script"
  exit 1
fi

# The following section is needed to make scripts more robust and easier to debug.
set -o xtrace   # Print every command that is being executed
set -o errexit  # Exit immediately if a command exits with a non-zero status
set -o nounset  # Treat unset variables like `unset variable_name` as an error and exit immediately
set -o pipefail # Fail the entire pipeline if any command in it fails

# folder of the parent script that will source this one
readonly currentScriptDir=`dirname "$(realpath -s "${BASH_SOURCE[1]}")"`

# folder where utils.sh script is located. It is also the root of the repo
readonly gitRepoRoot=`dirname "$(realpath -s "${BASH_SOURCE[0]}")"`

# the remote url of the repository
readonly gitRepoUrl=`git remote get-url origin`
