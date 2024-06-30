@echo on 
setlocal  
  
:: 假设当前目录是包含CMakeLists.txt的目录  
:: 获取当前目录的父目录  
set SOURCE_DIR=%~dp0
set TOP_DIR=%~dp0..

:: 设置构建目录为父目录下的build子目录  
set BUILD_DIR=%TOP_DIR%\cmake-build
set BUILD_DEST_LIB_DIR_RELDEB=%BUILD_DIR%\lib\RelWithDebInfo
set BUILD_DEST_LIB_DIR_DEBUG=%BUILD_DIR%\lib\Debug
set DIR_3RDPARTY_LIB=%TOP_DIR%\ThridParty-binAndLib

:: 如果构建目录不存在，则创建它  
if exist "%BUILD_DIR%" (
    echo Deleting directory %BUILD_DIR% and all its contents...
    for /d %%d in ("%BUILD_DIR%\*") do rmdir /S /Q "%%d"
    del /S /Q "%BUILD_DIR%\*"
    rmdir /S /Q "%BUILD_DIR%"
) else (
    echo Directory %BUILD_DIR% does not exist.
)

if not exist "%BUILD_DIR%\" mkdir "%BUILD_DIR%"
if not exist "%BUILD_DEST_LIB_DIR_RELDEB%\" mkdir "%BUILD_DEST_LIB_DIR_RELDEB%"
if not exist "%BUILD_DEST_LIB_DIR_DEBUG%\" mkdir "%BUILD_DEST_LIB_DIR_DEBUG%"

:: 转到构建目录    
cd /d "%BUILD_DIR%"

:: 转到构建目录后，运行cmake指向源目录（.. 表示上一级目录）  
:: cmake "/path/cmake/",这个语句意思是cmakelist.txt的来源位置,构建地点在当前所在目录
:: 如果你希望确保构建目录和源代码目录分开，你还可以定义一个额外的变量来指定构建目录，比如BUILD_DIR，并且在调用cmake时使用-B选项来指定构建目录
:: cmake -B%BUILD_DIR% %SOURCE_DIR%
cmake %SOURCE_DIR% -A x64 -DCMAKE_CONFIGURATION_TYPES=RelWithDebInfo;Debug

:: 如果你想要直接构建（使用MSBuild），可以添加以下行  
:: msbuild MyProject.sln /p:Configuration=Release /p:Platform="x64"  


set DIR_OPENCV_LIB=%DIR_3RDPARTY_LIB%\opencv
xcopy "%DIR_OPENCV_LIB%\*" "%BUILD_DEST_LIB_DIR_RELDEB%" /E /I /Y
xcopy "%DIR_OPENCV_LIB%\*" "%BUILD_DEST_LIB_DIR_DEBUG%" /E /I /Y

endlocal