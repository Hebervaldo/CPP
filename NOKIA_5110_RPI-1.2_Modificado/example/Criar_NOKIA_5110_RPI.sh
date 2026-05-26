#!/bin/bash

DIRETORIO_PADRAO=$(pwd)

killall -r test
cd ..
make
cd "$DIRETORIO_PADRAO"
chmod +x Script_Instalar_Biblioteca_BCM2835.sh
./Script_Instalar_Biblioteca_BCM2835.sh

make
clear
chmod +x Script_Exemplo.sh
# ./Script_Exemplo.sh
