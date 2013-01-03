pipe="pipe64"
mkfifo $pipe
./semcreate
./erzeug $pipe 0 2 5 &
./erzeug $pipe 1 1 4 &
./erzeug $pipe 2 3 2 &
./verbr $pipe
rm $pipe
