# CalcPI
Testing multithreading for MC calculation of PI

Works with gcc 6.3.0
Needs boost for mt19337 random number generation
in the Makefile, replace my boost installation with a path to your own

to compile:
make

to run:
./bin/calcPi.exe <precision>

note that precision > .0001 will take more than the average computer can uhh do by Poisson statistics (unless something in my current code is very inefficient)

Warning - Currently hardcoded for four threads. Make sure you have four cores or turn off some threads

to clean:
make clean
