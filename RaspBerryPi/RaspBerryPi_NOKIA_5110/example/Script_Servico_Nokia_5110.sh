#!/bin/bash

diretorio_Padrao=$(pwd)

chmod +x Criar_NOKIA_5110_RPI.sh
"$diretorio_Padrao/Criar_NOKIA_5110_RPI.sh"

echo '[Unit]
Description=Display_Nokia_5110
After=multi-user.target

[Service]
Type=simple
ExecStart='"$diretorio_Padrao/bin/test -r"'
Restart=on-abort

[Install]
WantedBy=multi-user.target' > "/lib/systemd/system/display_Nokia_5110.service"

chmod 644 /lib/systemd/system/display_Nokia_5110.service
systemctl daemon-reload
systemctl enable display_Nokia_5110.service
systemctl start display_Nokia_5110.service
