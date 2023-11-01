# Doxygen

Get dependencies:

```
sudo apt install doxygen graphviz
```

Change directory to this folder and install doxygen-awesome-css:

```
cd docs
npm install https://github.com/jothepro/doxygen-awesome-css#v2.2.1 --save-dev
```

To create the documentation:

```
# run from the docs folder
GIT_TAG=$(git describe --tags --dirty) doxygen
```