@echo off
set PWD=%cd%

REM replace with our emsdk path
cd C:\emsdk\emsdk\
call emsdk_env.bat > nul 2>&1

cd %PWD%
REM echo Current directory: %cd%
cd ..\..\source

REM Add files here if needed
set FILES=RenderingPlugin.cpp RenderAPI.cpp RenderAPI_OpenGLCoreES.cpp
set OUTPUT_PATH=..\build\WebGL\libRenderingPlugin2.bc
emcc %FILES% -L. -DSUPPORT_OPENGL_ES=1 -DSUPPORT_VULKAN=0 -DUNITY_WEBG=1 -shared -o "%OUTPUT_PATH%"

pause