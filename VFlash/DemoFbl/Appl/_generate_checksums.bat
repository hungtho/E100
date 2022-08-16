:: Create checksums for Vector SLP3 deliveries
@echo off
if "%1" == "" goto usage

echo.
echo Generate checksum (CRC32) for Vector SLP3
echo deliveries.
echo.
echo CRC (Security model NONE)          :
echo %~d1%~p1%~n1.crc
echo.

set local_dir=%~d0%~p0

:: Please configure the following variables
:: Root directory
set root_dir=%local_dir%..\..\..
:: Hexview executable
set hexview_exe=%root_dir%\Misc\Hexview\hexview.exe

echo Calculate CRC...
%hexview_exe% %1 /S -e:%local_dir%error.txt /cs9:%~n1.crc


echo ...finished.
echo.
goto end

:usage
echo "Please call with a hex file as parameter."
pause

:end
if exist %local_dir%\error.txt del %local_dir%\error.txt
