# PCB gateway

Ici se situent les fichiers EAGLE du PCB de la gateway qui se connecte sur une Raspberry Pi B 3+.
Il y a également la BOM et des images.

Travail réalisé à partir du projet [https://github.com/will127534/LoRa-concentrator](https://github.com/will127534/LoRa-concentrator)

## RPi IO Mapping

| Function    | RPi Pin  | RPi IO Names                     |
| ----------- | -------- | -------------------------------- |
| SPI MOSI    | 19       | SPI-MOSI, GPIO10                 |
| SPI MISO    | 21       | SPI-MISO, GPIO9                  |
| SPI SCK     | 23       | SPI-SCLK, GPIO11                 |
| SPI CSN     | 24 OR 26 | SPI-CS0, GPIO8 OR SPI-CS1, GPIO7 |
| Reset       | 22       | GPIO25                           |
| GPS UART TX | 10       | UART0-RX, GPIO15                 |
| GPS UART RX | 8        | UART0-TX, GPIO14                 |
| GPS PPS     | 29       | GPIO5                            |
