# Reto IoT
Repositorio con la solución del reto de la materia de "Implementación del internet de las cosas"

## Ingegrantes
- Karla Mondragón, A01025108
- Andrew Dunkerley, A01025076
- Ana Paula Katsuda, A01025303
- Andreína Sanánez, A01024927
- Julieta Aceves, A01029726

## Introducción
El objetivo del presente proyecto recae en la creación de un dispositivo conectado a internet con la capacidad de medir gases en el aire. En específico, se quiere que dicho dispositivo mida CO y LPG, que se envíe la información a una base de datos y que dicha base de datos se logre visualizar mediante Tableau. Es relevante mencionar que un objeto como el planteado, tiene la posibilidad de contribuir en el mantenimiento de la salud integral del usuario, permitiéndole saber si se encuentra en un entorno con niveles anormales de gases. 

## Secciones
- _Código de Arduino_: incluye el código en Arduino utilizado para configurar los sensores MQ y el código utilizado para obtener mediciones de dichos sensores así como generar "POST requests".
- _Código del servidor_: incluye el código en Python de la creación de la API utilizando la librería FastAPI. En este caso, se utiliza el reverse proxy "ngrok" para permitir el uso de un servidor mediante un navegador. 
- _Visualización de la base de datos_: 
