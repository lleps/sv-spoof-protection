Este programa hace un intento por defender tu servidor del query-spoofing mencionado en www.github.com/lleps/sv-spoof-attacker. Lo hace de la siguiente manera: 

Primero, necesita conocer la información real del servidor. En la carpeta "fs" vas a encontrar los archivos .pwn y .amx de un script que necesitas cargar en el servidor, el cual le informa al programa el estado del servidor (jugadores, hostname, etc). Lo hace por medio de un archivo (si, es una mierda, pero pawn no soporta sockets y no quiero incluir ningún plugin aparte).

El programa, tiene un loop que se ejecuta cada un segundo. Lo que hace, es grabar en una lista todas las requests de clientes y les manda los datos reales al cliente, intentando ser más rapido que el servidor que le manda los datos falsos. Toda la lógica esta en main.cpp, las otras clases son para escuchar y enviar queries.

NOTA IMPORTANTE: Ejecutar el programa como root, de lo contrario no va a tener acceso a escuchar los paquetes, y no va a funcionar.

Otra cosa, es muy importante usar ese FS, de lo contrario el server no va a saber cómo componer la query.
