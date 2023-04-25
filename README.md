# Unknown Author

Sistema de análisis, escritura y lectura de datos en OF que complementa a la presentación A/V Unkown Author. 

El programa toma una base de datos conformada por carpetas de imágenes. 

El objetivo del proyecto consiste en dibujar estructuras de datos y manipularlas en vivo por medio de un sistema personalizado de audio y video. 

Para el performance audiovisual, el proyecto utiliza técnicas de live coding. 

Consideramos que el uso de técnicas de live coding puede aportar elementos narrativos a la exploración y ordenamiento de datos en el momento. 

Para el análisis y despliegue de información utilizamos un programa realizado con OpenFrameworks. Para el control y la sonificación utilizamos SuperCollider. 

Hay dos modos principales: el modo de escritura y el modo de lectura.

## Preparación del dataset

### Instalooter e instaloader

Para descargar las imágenes utilizamos instaloader. En algún momento dejó de funcionar y tuvimos que utilizar instalooter. 

Con estos proyectos es posible descargar imágenes, videos y metadatos de publicaciones en Instagram

### Números consecutivos 

Cada cuenta tiene su carpeta. 

Fue necesario renombrar las imágenes con números consecutivos. 

`ls -v | cat -n | while read n f; do mv -n "$f" "$n.png"; done`

### Reducción de imágenes

Manejar un dataset de imágenes tan grande complejiza su despliegue para manipularlas en tiempo real. 

Es necesario utilizar versiones reducidas de las imágenes, así pueden cargarse rápido.

## Análisis

### Color

Reducir el tamaño de la imagen con interpolación permite tener el valor aproximado del promedio de color de la imagen. 

El programa toma las imágenes de la base de datos y las redimensiona a 1x1 pixeles. 

Después extrae los valores de color de la imagen. 

Después almacena estos valores en un vector de colores. 

### Audio 

## Escritura

### Color

Una vez almacenados los valores del promedio de color de las imágenes, estos son guardados de manera individual en CSVs. 

Es necesario "abrir" el archivo, almacenar el dato y "cerrar" el archivo. 

De esta manera almacenamos el dato del promedio de color por carpeta. 

### Notas sobre la escritura de datos

Activar el booleano escritura. 

Las lecturas se guardan en la carpeta csv. 

Es necesario unir los archivos para después leerlos en el modo lectura. 

Para hacer esto es neceario agregarle ceros a los archivos:

`rename 's/\d+/sprintf("%06d",$&)/e' *`

Y luego unirlos en un solo archivo: 

`cat * > nombreDelArchivo.csv`
x
Es necesario copiar el archivo resultante en csv/colorF/

## Lectura

### Imágenes

Para las representaciones en dos dimensiones, datos leídos pueden asignarse a valores en X y Y.

Fue necesario redimensionar las imágenes para poder trabajar con ellas en un espacio virtual. 

Para el caso de representaciones 3d, es posible asignar un posible valor extra. 

Como la representación en 3d no sigue la lógica de coordenadas tridimensionales sino de las coordenadas esféricas, entonces es posible asignar valores en X y Y para que se dibujen en una "esfera". 

Entonces para el caso del espacio tridimensional, el valor extra puede asignarse posición en función del diámetro de la esfera. 

### FFT

El programa hace un análisis de la señal de audio que proviene del exterior o el micrófono. 

Este análisis se pasa al dibujo de varias figuras primitivas en entornos 2d y 3d. 

### Estructura

#### Títulos

Pensar en algo que pueda funcionar como entrada/cortinilla

####  lines

Un plano a nivel de cámara da la sensación de una línea. Esta descopuesto en puntos. 
Utilizar otros elmeentos gráficos que coincidan con la lectura de datos, por ejemplo un ordenamiento en x de los promedios de colores en una cuenta. 
Lectura de moisaicos

#### Escena 2: plane

Dos planos encontrados y alejados que ya interactúan en un entorno 3d. Podría haber una transición entre el anterior punto y este. 
Visibilidad de la lectura de datos

#### Escena 3: sphere

La esfera que responde fft. Interesante sería si esta esfera ya pudiera tener textura o superficie, para eso necesitaríamos luces. 

