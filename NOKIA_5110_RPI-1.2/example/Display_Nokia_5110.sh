#!/bin/bash

# ./bin/test "Robozinho Chiquititozinho..."
# ./bin/test "1 - Robozinho Chiquititozinho... 2 - Robozinho Chiquititozinho... 3 - Robozinho Chiquititozinho... 4 - Robozinho Chiquititozinho... 5 - Robozinho Chiquititozinho..."
# ./bin/test "Robozinho Chiquititozinho..." "Robozinho Chiquititozinho..." "Robozinho Chiquititozinho..." "Robozinho Chiquititozinho..." "Robozinho Chiquititozinho..." 'c' 'r' -1 1
cd bin
chmod +x test
cd ..
killall -r test
./bin/test -r
