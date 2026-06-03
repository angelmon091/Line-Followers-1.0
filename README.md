# Line Follower 1.0

![Arduino](https://img.shields.io/badge/Arduino-00979D?logo=arduino&logoColor=white) ![C/C++](https://img.shields.io/badge/C%2B%2B-00599C?logo=c%2B%2B&logoColor=white) ![KiCad](https://img.shields.io/badge/KiCad-FCA326?logo=kicad&logoColor=white) ![Gerber](https://img.shields.io/badge/Gerber-FF6A00?logo=gerber&logoColor=white)


Robot seguidor de línea — código Arduino, esquemas KiCad y Gerbers listos para fabricación.

Qué es:
- Código, PCB y archivos Gerber para un robot seguidor de línea (ejemplos en `CODE/Main Code/`).

Cómo reproducir (resumen):
1. Materiales: placa Arduino (Uno/Nano/Pro Mini), motores, driver de motores, sensores IR, batería, cables, PCB o protoboard.
2. Abrir el ejemplo: `CODE/Main Code/<ejemplo>/*.ino`.
3. Instalar librerías desde `CODE/Libreria/` y seleccionar la `board` correcta en Arduino IDE/PlatformIO.
4. Compilar y subir al microcontrolador.
5. Montar la electrónica según `ESQUEMA Y PCB/` y/o fabricar la PCB usando `Archivos Gerber PCB/gerbers/` (enviar a fabricante).


Notas importantes:
- Verificar voltaje y polaridad de la batería.
- Calibrar sensores antes de pruebas.
- Revisar conexiones del driver de motores para evitar cortocircuitos.

Estructura del proyecto (estilo `eza --tree`):
```
.
├─ CODE/
│  ├─ Libreria/
│  └─ Main Code/
│     ├─ Codigo Carro V1.0/
│     │  └─ Programacion.ino
│     ├─ Ejemplo de Lectura y Posicion/
│     │  └─ LECTURA_Y_POSICION.ino
│     └─ Ejemplo de Motores y Rotacion/
│        └─ Motores.ino
├─ ESQUEMA Y PCB/
│  ├─ asda.kicad_pcb
│  └─ asda.kicad_sch
├─ Archivos Gerber PCB/
│  └─ gerbers/
│     ├─ asda-F_Cu.gbr
│     └─ asda-job.gbrjob
├─ GErber con Turbina/
└─ README.md
```


