rm -rf android-build
mkdir android-build
cd android-build
qmake CONFIG+="release" ..
mingw32-make
mingw32-make INSTALL_ROOT=build install
androiddeployqt.exe --input android-libqfootballstat.so-deployment-settings.json --output build --ant D:\adt-bundle-windows-x86_64-20140702\eclipse\plugins\org.apache.ant_1.8.3.v201301120609\bin\ant.bat --jdk "C:/Program Files/Java/jdk1.8.0_25"
cd ..
