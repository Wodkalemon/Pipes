mkfifo pipe64
./semcreate
./erzeug pipe64 0 2 5 &
./erzeug pipe64 1 1 4 &
./erzeug pipe64 2 3 2 & 
./verbr	pipe64
rm pipe64
