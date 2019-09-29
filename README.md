# Automatisation d'un pont tournant FLEISCHMANN 6152 (HO) en WiFi avec un ESP32

<img src="https://github.com/BOBILLEChristophe/pont_fleischmann_6152_ESP_32/blob/master/pont_fleischmann_6152_ESP_32/pont_tournant_fleischmann_v_5_bb.jpg">

Le pont se pilote à partir d'un navigateur. L'application web est une simple page HTML qui communique en websockets et qui est copiée dans la SPIFFS de l'ESP32.

J'ai placé sous le pont un module de prototypage ESP32 et une carte moteur Pololu A4990.

Le programme sur l'ESP32 est écrit en C/C++ au travers de l'IDE Arduino.

Le programme cherche à chaque fois le chemin le plus court pour se rendre d'une porte à une autre. Il gère le retournement, c'est à dire qu'une locomotive entrée en avant sur une voie peut sortir en arrière sur une autre. Dans ce cas, la polarité des rails est automatiquement inversée.

A voir sur Youtube : https://youtu.be/Rx7vND9eew4

