#!/bin/bash

# ./bin/test "Robo Robozinho..."
# ./bin/test "1 - Robo Robozinho... 2 - Robo Robozinho... 3 - Robo Robozinho... 4 - Robo Robozinho... 5 - Robo Robozinho..."
# ./bin/test "Robo Robozinho..." "Robo Robozinho..." "Robo Robozinho..." "Robo Robozinho..." "Robo Robozinho..." 'c' 'r' -1 1
cd bin
chmod +x test
cd ..
killall -r test
./bin/test -r
