@REM This batch file has been generated by the IAR Embedded Workbench
@REM C-SPY Debugger, as an aid to preparing a command line for running
@REM the cspybat command line utility using the appropriate settings.
@REM
@REM You can launch cspybat by typing the name of this batch file followed
@REM by the name of the debug file (usually an ELF/DWARF or UBROF file).
@REM Note that this file is generated every time a new debug session
@REM is initialized, so you may want to move or rename the file before
@REM making changes.
@REM 


"D:\PROGRAMACION\IAR Systems\common\bin\cspybat" "D:\PROGRAMACION\IAR Systems\arm\bin\armproc.dll" "D:\PROGRAMACION\IAR Systems\arm\bin\armstlink.dll"  %1 --plugin "D:\PROGRAMACION\IAR Systems\arm\bin\armbat.dll" --macro "D:\PROGRAMACION\IAR Systems\arm\config\debugger\ST\Trace_STM32F4xx.dmac" --flash_loader "D:\PROGRAMACION\IAR Systems\arm\config\flashloader\ST\FlashSTM32F4xxx.board" --backend -B "--endian=little" "--cpu=Cortex-M4" "--fpu=VFPv4" "-p" "D:\PROGRAMACION\IAR Systems\arm\CONFIG\debugger\ST\iostm32f4xxx.ddf" "--drv_verify_download" "--semihosting" "--device=STM32F407VG" "--stlink_interface=SWD" "--stlink_reset_strategy=0,0" "--drv_swo_clock_setup=72000000,0,2000000" 


