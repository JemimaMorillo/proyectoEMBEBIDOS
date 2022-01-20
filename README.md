# Proyecto SISTEMAS EMBEBIDOS: Sistema automatizado de control para la incubación de huevos fértiles

El proyecto consiste en realizar un sistema de control capaz de detectar el grado de temperatura y porcentaje de humedad que afectan a los huevos para la emisión de alertas, elevando dicha información hacia una plataforma IoT Ubidots para un monitoreo continuo

## Contenido
- Diagramas esquemáticos(.pdsprj)
- Códigos de funcionamiento (.c/.h/.py)
- Capturas de simulación
- Diagrama PCB (imagen placaPCB.png)
- Modelo 3D (imagen vista3D.png)
#
### Diagramas esquemáticos
- Atmega328P
# ![Image text](https://github.com/JemimaMorillo/proyectoEMBEBIDOS/blob/main/Esquemas/esquema1.jpg)

- Raspberry Pi
# ![Image text](https://github.com/JemimaMorillo/proyectoEMBEBIDOS/blob/main/Esquemas/esquema2.png)

### Capturas de simulación

Mensaje de PELIGRO en pantalla LCD, diodo LED encendido, Speaker activo
# ![Image text](https://github.com/JemimaMorillo/proyectoEMBEBIDOS/blob/main/Capturas%20de%20simulacion/prueba.png)


Alarma desactivada en Ubidots

# ![Image text](https://github.com/JemimaMorillo/proyectoEMBEBIDOS/blob/main/Capturas%20de%20simulacion/ubidots1.png)

 Alarma activada en Ubidots
# ![Image text](https://github.com/JemimaMorillo/proyectoEMBEBIDOS/blob/main/Capturas%20de%20simulacion/ubidots2.png)


### Diagrama PCB

![Image text](https://github.com/JemimaMorillo/proyectoEMBEBIDOS/blob/main/placaPCB.png)
#
### Modelo 3D
![Image text](https://github.com/JemimaMorillo/proyectoEMBEBIDOS/blob/main/vista3D.png)

## NOTA: 
Verificar que los puertos seriales de los COMPIM de ambos proyectos coincidan con el par de puertos creados en el Configure Virtual Serial Port Driver
