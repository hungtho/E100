:: E100 LDC

::set LOCAL_DIR=%~d0%~p0
set HEX_VIEW=%~dp0Tools\HexView\hexview.exe
set FBL=%~dp0HexFiles\E100_LDC_FBL.hex
set APPL=%~dp0HexFiles\E100_LDC_APPL.hex
set CRC=%~dp0HexFiles\E100_LDC_APPL.crc
set FBL_CUT=%~dp0HexFiles\FBL_CUT.s19
set FBL_APPL=%~dp0HexFiles\FBL_APPL.s19
set MERGE=%~dp0HexFiles\E100_LDC_Merge.s19

del %MERGE%
del %APPL%
del %CRC%

if not exist "%FBL%" copy %~dp0VFlash\Hex\DemoFbl.hex %FBL%

copy %~dp0build\out.hex %APPL%

%HEX_VIEW% /s %APPL% -e:%~dp0HexFiles\error.txt /cs9:%CRC%
%HEX_VIEW% /s %FBL% /CR:0x00FC8000,0x10 /XS:28:2 -o %FBL_CUT%
%HEX_VIEW% /s %APPL% /MO:%FBL_CUT% /XS:28:2 -o %FBL_APPL%
%HEX_VIEW% /s %FBL_APPL% /FR:0x00FD7FF0,0x08 /FP:0x736A293E00000000 /XS:28:2 -o %MERGE%

del %FBL_CUT%
del %FBL_APPL%

if exist %~dp0HexFiles\error.txt del %~dp0HexFiles\error.txt
if exist %~dp0\D del %~dp0\D

::pause