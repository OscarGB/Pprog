#!/bin/bash

#echo "Initializing the game"

./JuegoConv loader.dat -nr <<EOF

pick lantern
sleep 1
go south
sleep 1
turnon lantern
sleep 1
go west
sleep 1
pick Tnt
sleep 1
go east
sleep 1
go east
open wall with Tnt
go north
pick Ladder
go south
go west
open uncomplete_ladder with Ladder
go up
pick Lobster
go down
go south
open exit with Lobster
go west
EOF


