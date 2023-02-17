@echo off

set "folder_path=../bin"

if not exist "%folder_path%" (
  mkdir "%folder_path%"
  echo Bin Folder created.
) else (
  echo Bin Folder already exists.
)

cd ../bin/
cmake ..
PAUSE