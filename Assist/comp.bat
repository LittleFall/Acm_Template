:: 在rand.exe存在的情况下,对my.exe和std.exe进行对拍
@echo off  
:loop  
    rand.exe %random% > data.in
    std.exe < data.in > std.out
    my.exe < data.in > my.out
    fc my.out std.out 
if not errorlevel 1 goto loop  
pause
goto loop
