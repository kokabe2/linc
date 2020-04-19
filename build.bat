@echo off

set PROJECT_NAME=linc
for /F "tokens=*" %%A in ('"git describe HEAD --abbrev=0"') do set PROJECT_VER=%%A

cd %~dp0

set COMPILER=ccrx
set OUTPUT_DIR=bin\%COMPILER%@%PROJECT_VER%
mkdir %OUTPUT_DIR% > NUL 2>&1
%COMPILER% -output=obj -lang=c99 -nostuff -isa=rxv3 -debug -signed_char ^
           -include=v1/,src/,external/ ^
           src/request/default_request.c ^
           src/request/http_method_request.c ^
           src/request/request_base.c ^
           src/responder/default_responder.c ^
           src/responder/responder_base.c ^
           src/response/default_response.c ^
           src/response/response_base.c ^
           src/response/simple_response.c ^
           src/router/default_router.c ^
           src/router/router_base.c ^
           src/server/default_server.c ^
           src/server/server_base.c ^
           src/util/name_resolution_helper.c ^
           src/pdns.c ^
           src/phttp.c
if %errorlevel% neq 0 exit /b

rlink -form=lib -output=%OUTPUT_DIR%/%PROJECT_NAME%.lib *.obj
del *.obj
