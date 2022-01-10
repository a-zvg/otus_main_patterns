@ECHO ON

MKDIR _build
cmake -B _build
cmake --build _build --config Release
