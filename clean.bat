@echo off
setlocal EnableExtensions EnableDelayedExpansion

REM Run this from the Unreal project root (where the .uproject is)

echo.
echo Cleaning project folders...
call :CleanDir "Build"
call :CleanDir "Binaries"
call :CleanDir "Intermediate"
call :CleanDir "Saved"
call :CleanDir "DerivedDataCache"
call :CleanDir ".vs"

echo.
echo Cleaning solution files...
del /q "*.sln" 2>nul

echo.
echo Cleaning plugin folders (if any^)...
if exist "Plugins\" (
  for /d %%P in ("Plugins\*") do (
    if exist "%%P\" (
      echo.
      echo Plugin: %%~nxP
      pushd "%%P" >nul

      call :CleanDir "Binaries"
      call :CleanDir "Intermediate"
      call :CleanDir "Saved"
      call :CleanDir "DerivedDataCache"
      call :CleanDir "Build"
      call :CleanDir ".vs"
      del /q "*.sln" 2>nul

      popd >nul
    )
  )
)

echo.
echo Done.
endlocal
exit /b 0


:CleanDir
if exist "%~1\" (
  echo Removing "%~1"
  rd /s /q "%~1" 2>nul
) else (
  echo Skipping "%~1" (not found^)
)
exit /b 0
