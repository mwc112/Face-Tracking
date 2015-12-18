instructions to run the test
cd ../wm
cmake .
(if cannot make successfully for c99 reason, open CMakeLists.txt first, do nothing, close window)
make
(if ./runUnitTests have error, go to system Tools/system settings/displays, select display with largest controls.
If already select 'display with largest controls', do nothing and still select apply )
./runUnitTests
