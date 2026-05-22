# Controle de Display Nokia 5110 para Raspberry Pi

Projeto desenvolvido para integração e controle do display gráfico Nokia 5110 utilizando Raspberry Pi, permitindo comunicação com hardware embarcado, renderização gráfica e manipulação programática do display LCD.

A solução foi criada para possibilitar experimentação embarcada, desenvolvimento de interfaces gráficas simples, exibição de informações em displays LCD e integração entre software e hardware utilizando Raspberry Pi.

O sistema utiliza comunicação com o display Nokia 5110 através de GPIO, permitindo exibição de textos, gráficos, informações operacionais e dados provenientes de sensores ou aplicações embarcadas.

---

## ✨ Principais Recursos

- Controle de display Nokia 5110
- Integração com Raspberry Pi
- Comunicação via GPIO
- Renderização gráfica em LCD
- Exibição de textos e informações
- Desenvolvimento embarcado
- Manipulação programática do display
- Estrutura modular para expansão
- Integração com hardware eletrônico
- Processamento em tempo real

---

## 📦 Funcionalidades

O sistema permite:

- inicialização do display LCD;
- envio de comandos gráficos;
- renderização de caracteres;
- exibição de textos;
- atualização dinâmica da tela;
- integração com GPIO;
- desenvolvimento de interfaces embarcadas;
- experimentação com displays gráficos.

---

## 🏗️ Arquitetura do Projeto

O projeto foi estruturado para facilitar integração entre Raspberry Pi e o display Nokia 5110.

### Componentes Principais

| Componente | Função |
|---|---|
| `main.c` | Inicialização da aplicação |
| `lcd5110.c` | Controle do display |
| `gpio.c` | Comunicação GPIO |
| `font.c` | Renderização de caracteres |
| `graphics.c` | Rotinas gráficas |
| `config.h` | Configurações da aplicação |

---

## 🔧 Tecnologias Utilizadas

- Raspberry Pi
- Display Nokia 5110
- GPIO
- Linguagem C / C++
- Linux
- Sistemas Embarcados
- Automação Embarcada
- Controle de Hardware

---

## 📂 Estrutura Geral

### Extensões identificadas

- ``: 22 arquivo(s)
- `.a`: 1 arquivo(s)
- `.ac`: 1 arquivo(s)
- `.am`: 3 arquivo(s)
- `.c`: 13 arquivo(s)
- `.cpp`: 10 arquivo(s)
- `.guess`: 1 arquivo(s)
- `.gz`: 1 arquivo(s)
- `.h`: 3 arquivo(s)
- `.hpp`: 6 arquivo(s)
- `.in`: 5 arquivo(s)
- `.jpg`: 1 arquivo(s)
- `.log`: 3 arquivo(s)
- `.m4`: 1 arquivo(s)
- `.md`: 2 arquivo(s)
- `.o`: 8 arquivo(s)
- `.po`: 2 arquivo(s)
- `.sh`: 6 arquivo(s)
- `.status`: 1 arquivo(s)
- `.sub`: 1 arquivo(s)
- `.trs`: 1 arquivo(s)

### Arquivos encontrados

- `.gitignore`
- `AUTHORS`
- `Bitmap_data.hpp`
- `CHANGELOG.md`
- `COPYING`
- `ChangeLog`
- `Criar_NOKIA_5110_RPI.sh`
- `Display_Nokia_5110.sh`
- `Doxyfile.in`
- `INSTALL`
- `LICENSE`
- `Makefile`
- `Makefile`
- `Makefile`
- `Makefile`
- `Makefile`
- `Makefile.am`
- `Makefile.am`
- `Makefile.am`
- `Makefile.in`
- `Makefile.in`
- `Makefile.in`
- `NEWS`
- `NOKIA_5110_Print.cpp`
- `NOKIA_5110_Print.hpp`
- `NOKIA_5110_Print.o`
- `NOKIA_5110_RPI.cpp`
- `NOKIA_5110_RPI.hpp`
- `NOKIA_5110_RPI.o`
- `NOKIA_5110_RPI_Font.cpp`
- `NOKIA_5110_RPI_Font.hpp`
- `NOKIA_5110_RPI_Font.o`
- `NOKIA_5110_graphics.cpp`
- `NOKIA_5110_graphics.hpp`
- `NOKIA_5110_graphics.o`
- `README`
- `README.md`
- `Script_Exemplo.sh`
- `Script_Instalar_Biblioteca_BCM2835.sh`
- `Script_Servico_Nokia_5110.sh`
- `aclocal.m4`
- `backupicon.jpg`
- `bcm2835-1.73.tar.gz`
- `bcm2835.Po`
- `bcm2835.c`
- `bcm2835.h`
- `bcm2835.o`
- `blink.c`
- `compile`
- `config.guess`
- `config.h`
- `config.h.in`
- `config.log`
- `config.status`
- `config.sub`
- `configure`
- `configure.ac`
- `depcomp`
- `event.c`
- `getipv4.cpp`
- `getipv4.hpp`
- `getipv4.o`
- `gpio.c`
- `i2c.c`
- `input.c`
- `install-sh`
- `libbcm2835.a`
- `ltmain.sh`
- `main.cpp`
- `main.cpp`
- `main.cpp`
- `main.cpp`
- `main.cpp`
- `main.o`
- `missing`
- `pwm.c`
- `smi.c`
- `spi.c`
- `spin.c`
- `spiram.c`
- `spiram.h`
- `spiram_test.c`
- `stamp-h1`
- `test`
- `test`
- `test-driver`
- `test-suite.log`
- `test.Po`
- `test.c`
- `test.log`
- `test.o`
- `test.trs`

### Arquivos de código identificados

- `NOKIA_5110_Print.cpp`
- `NOKIA_5110_RPI.cpp`
- `NOKIA_5110_RPI_Font.cpp`
- `NOKIA_5110_graphics.cpp`
- `bcm2835.c`
- `blink.c`
- `event.c`
- `getipv4.cpp`
- `gpio.c`
- `i2c.c`
- `input.c`
- `main.cpp`
- `main.cpp`
- `main.cpp`
- `main.cpp`
- `main.cpp`
- `pwm.c`
- `smi.c`
- `spi.c`
- `spin.c`
- `spiram.c`
- `spiram_test.c`
- `test.c`

---

## 🖥️ Ambiente Operacional

O sistema foi desenvolvido para execução em:

- Raspberry Pi;
- sistemas Linux embarcados;
- laboratórios de eletrônica;
- projetos IoT;
- automação embarcada;
- experimentação com displays LCD.

---

## 📊 Objetivos do Projeto

O projeto foi desenvolvido para:

- integrar displays gráficos ao Raspberry Pi;
- facilitar desenvolvimento embarcado;
- permitir interfaces LCD simples;
- estudar comunicação GPIO;
- desenvolver aplicações eletrônicas;
- experimentar integração hardware/software.

---

## 🚀 Melhorias Futuras

- Interface gráfica avançada
- Suporte a múltiplos displays
- Integração com sensores
- Dashboard embarcado
- Renderização gráfica otimizada
- Controle remoto via rede
- Integração MQTT
- Monitoramento em tempo real

---

## 📄 Licença

Projeto desenvolvido para automação embarcada, integração hardware/software e controle de display Nokia 5110 utilizando Raspberry Pi.
