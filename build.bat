@echo off

set PROJECT_NAME=linc
for /F "tokens=*" %%A in ('"git describe HEAD --abbrev=0"') do set PROJECT_VER=%%A

cd %~dp0

set COMPILER=ccrx
set OUTPUT_DIR=bin\%COMPILER%@%PROJECT_VER%
mkdir %OUTPUT_DIR% > NUL 2>&1
%COMPILER% -output=obj -lang=c99 -nostuff -isa=rxv3 -debug -signed_char ^
           -include=v1/,external/ ^
           src/response/simple_response.c
if %errorlevel% neq 0 exit /b

rlink -form=lib -output=%OUTPUT_DIR%/%PROJECT_NAME%.lib *.obj
del *.obj
