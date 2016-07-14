@echo off

set extgen="..\..\Tools\ExtGen"
set target="..\MAE.gmx\extensions "

echo Generating extension...

%extgen%\ExtGen MAE.xml %target% %extgen%\default

if %ERRORLEVEL% EQU 0 (
	echo Done!
) else (
	pause
)
