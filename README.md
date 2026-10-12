# C++ System Monitor

Monitor de recursos para Linux, desarrollado con C++17.

Lee métricas del sistema directamente desde `/proc` y muestra una vista de terminal sin dependencias externas de ejecución.

## Vista de terminal

![Salida real del monitor en Linux](docs/terminal.webp)

Imagen de la salida real de una ejecución local; los valores dependen del equipo y del momento de muestreo.

## Funciones actuales

- Hostname y fecha/hora local de cada lectura.
- Porcentaje de CPU calculado con dos muestras separadas por 250 ms.
- RAM y swap usadas, totales y porcentajes.
- Carga promedio de 1, 5 y 15 minutos.
- Porcentaje de uso del sistema de archivos raíz.
- Tiempo encendido y conteo de directorios de procesos en `/proc`.
- Lectura única o actualización continua, con opción de conservar lecturas anteriores.

## Requisitos

Linux, compilador compatible con C++17 y CMake 3.16 o superior. Esta implementación utiliza interfaces de Linux; Windows y macOS no están soportados.

## Instalación y uso

```bash
git clone https://github.com/DonMilo-22/Cpp-System-Monitor.git
cd Cpp-System-Monitor
cmake -S . -B build
cmake --build build
./build/system-monitor --once --no-clear
```

## Opciones

| Opción | Uso |
|---|---|
| `--once` | Muestra una lectura y termina. |
| `--interval <segundos>` | Espera entre lecturas; predeterminado 1 y mínimo efectivo 1. |
| `--no-clear` | Conserva las lecturas anteriores en terminal. |

```bash
./build/system-monitor --interval 2 --no-clear
```

Interrumpe el modo continuo con `Ctrl+C`.

## Cómo funciona

Consulta `/proc/stat`, `/proc/meminfo`, `/proc/uptime` y `/proc/loadavg`. RAM usada se calcula restando memoria disponible de la total; la carga promedio no es un porcentaje de CPU. El disco raíz se consulta con `statvfs`.

## Almacenamiento y límites

No almacena métricas. La frecuencia total incluye el muestreo de CPU además de la espera configurada. El programa muestra `GB`, aunque convierte memoria usando divisores binarios. El conteo de procesos refleja directorios numéricos de `/proc`, no únicamente procesos ejecutándose en CPU. En contenedores, la vista de `/proc` puede diferir de los límites asignados al contenedor.

## Comprobaciones

La compilación y `./build/system-monitor --once --no-clear` permiten comprobar una lectura local; no sustituyen una suite automatizada.

## Autor y licencia

Desarrollado por [DonMilo-22](https://github.com/DonMilo-22).

Licencia: MIT.

## Historial

Consulta [CHANGELOG.md](CHANGELOG.md) para ver las actualizaciones.
