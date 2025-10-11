@echo off
set PWD=%cd%

cd C:\emsdk\emsdk\
call emsdk_env.bat > nul 2>&1

cd %PWD%
REM echo Current directory: %cd%

emcc main.cpp sloydSdk_exports_js.cpp -s EXPORTED_FUNCTIONS="['_malloc', '_free']" -sEXPORT_NAME=SloydSDK -s MODULARIZE=1 -s NO_EXIT_RUNTIME=1 -fexceptions -pthread -s WASM=1 -s ALLOW_MEMORY_GROWTH -s INITIAL_MEMORY=134217728 -sEXPORTED_RUNTIME_METHODS=wasmMemory compiled_libs/lib_burst_generated_part_0.o compiled_libs/lib_burst_generated_part_0_globals.o compiled_libs/lib_burst_generated_part_0_merged.o -L. -Lcompiled_libs -lburstRTL_web_32 --bind -sEXPORTED_RUNTIME_METHODS=wasmMemory -o build_output/SloydSDK.js
