@echo off
setlocal

echo Creating .\bin directory...
if not exist ".\bin" mkdir ".\bin"

make

echo Running RecompModTool...
.\RecompModTool.exe .\mod.toml .\bin
if errorlevel 1 goto error

echo Zipping output file into .\bin...
zip -j ".\bin\tag_anywhere_sparkles.zip" ".\bin\tag_anywhere_sparkles.nrm"
if errorlevel 1 goto error

echo Complete
goto end

:error
echo.
echo [ERROR] Script failed.
exit /b 1

:end
endlocal