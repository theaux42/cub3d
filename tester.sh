#!/bin/bash

BIN=./cub3d
MAP_DIR=./maps/bad

for map in "$MAP_DIR"/*.cub; do
	valgrind --show-leak-kinds=all --leak-check=full --track-origins=yes -q $BIN "$map"
	RET=$? 
	if [ $RET -ne 0 ]; then
		echo "OK: Success on map: $map"
	else
		echo "[!] KO: Failed the map: $map"
	fi
	sleep 0.2
done
