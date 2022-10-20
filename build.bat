@echo off


IF NOT EXIST .\build mkdir .\build
pushd .\build

SET CommonCompilerFlags=-Zi -Od
cl %CommonCompilerFlags% ..\main.cpp
popd