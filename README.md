# Tower Defence

Tower defence game.

## Install dev environment

### Install setup wxl

Install wxl, open PowerShell with admin

`wxl --install`

In wxl, install developer tools, like gcc and make

`sudo apt install build-essential`

Install SFML

`sudo apt-get install libsfml-dev`

### Install plugins to VSCode

https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-wsl

https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools

### Open project in VS Code

In wxl, navigate to the repo root and

`code .`

## Build and Run

Build using make

`make`

You can also remove object files and the exe by running
`make clean`

Run the game with

`./game`

There is also a script which will build and run:

`./build_and_run.sh`

The script also has an option to rebuild with option `-r`, just clean with `-c` and just building with `-r`. Rebuild and do not run: `-rb`.
