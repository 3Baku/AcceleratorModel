# Akcelerator w salaterce — wersja rozszerzona

## Krótkie omówienie
Model "Akceleratora w salaterce" został wzbogacony o specjalne komponenty, które pozwoliły zamienić go na domowej roboty układ doświadczalny. Miskę będącą główną częścią akceleratora umieszczono w zbudowanej z klocków LEGO ramce z wydłużonymi szynami. Przyczepiono na nich z jednej strony laser, którego wiązka światła padała na umieszczony z drugiej strony fotorezystor. Pośrodku stała salaterka. Całkowita długość konstrukcji wyniosła około 69 cm. Taki układ pozwalał na odczytywanie momentu, w którym kulka przecinała wiązkę. W ten sposób — za pośrednictwem specjalnie napisanego kodu — można było odczytać czas, w którym kulka pokonywała pełne okrążenie. Znając promień, po jakim się poruszała, można było wyznaczyć jej prędkość. Po dokonaniu pomiaru masy kulki (niezbędna do tego będzie precyzyjna waga np. cukiernicza) możliwe jest obliczenie średniej energii kinetycznej tego obiektu podczas ruchu.

Do skonstruowania elektronicznej części układu została użyta lutownica wraz z cyną lutowniczą. Odpowiednie komponenty elektroniczne zostały połączone własnoręcznie na płytce drukowanej. Większość z nich została zakupiona z sklepu internetowego botland.

Wszystkie poniżej wymienione materiały oraz parametry odnoszą się do układu przedstawionego na zdjęciu, który to prezentowany był na II Warszawskiej Konferencji Nauczycieli Fizyki.
## Spis materiałów do podstawowej wersji akceleratora
* Miska typu salaterka (najlepiej z płaskim dnem i kolistym kształtem)
* Taśma miedziana (można znaleźć jako "na ślimaki") [1]
* 6 kabli typu krokodylki
* Maszyna elektrostatyczna
* Piłeczki pingpongowe
* Spray grafitowy [2]
## Spis materiałów do rozszerzonej wersji — pomiar prędkości
* Przewód zasilający sterowanie
* Dioda laserowa 3–5V 5mW czerwona 650nm [3]
* Fotorezystor 100–200k (można dobrać mniejszy) [4]
* Tranzystor NMOS 2N7000 [5]
* Mikrokontroler Xiao ESP32-C3 [6]
* Płytka drukowana do lutowania (opcjonalnie można stworzyć projekt PCB na podstawie pliku KiCad [7]
* Rezystory: jeden 10k, oraz jeden 1k
* Lutownica
* Cyna lutownicza (np. Sn60Pb40)
* Przewody do łączenia pól lutowniczych

## Parametry niezbędne do obliczeń
* Masa kulki — 2,74 g
* Promień salaterki — 6,5 cm

## Zdjęcie układu doświadczalnego

![Zdjecie ukladu z konferencji](/zdjecia/KonferencjaUklad.jpg)
## Linki

[1] [Taśma miedziana](https://allegro.pl/oferta/tasma-miedziana-na-slimaki-odstraszajaca-samoprzylepna-20m-x-25mm-miedz-18013162639?offerId=18013162639&inventoryUnitId=tKgWyfx69Kv0hC4Y1aRx4A&adGroupId=MGM3YjRiNWItN2MwOS00M2FjLTk2YjEtNjk5YjcxOTdhYTlkAA&campaignId=ZmFmODMyM2UtMmZjYi00MWNmLWJmOWQtYTU4NmZkMzhjOGNmAA&clientId=MTYwMzk1MTEA&sig=fe25231b496d8baed176a4169332f38e&utm_feed=cba59b59-8d0f-48d0-98a0-e9d1127523e2&utm_source=google&utm_medium=ads&gad_source=1&gad_campaignid=23234234590&gbraid=0AAAAArAVsh0dIph2UBz0bEM25EgHUYLKB&gclid=Cj0KCQiAoZDJBhC0ARIsAERP-F8FK1X1yBE7Qjkvz_VeEo6FoYsYiZYtjOtQbuMNHZRtRups1mWAWOQaAginEALw_wcB&dd_referrer=https%3A%2F%2Fwww.google.com%2F)

[2] [Spray grafitowy](https://allegro.pl/produkt/farba-przewodzaca-grafitowa-spray-400ml-antystatyczna-ekranujaca-uziemienie-96ab1be1-56a6-4b00-8113-e29869f06b20?srsltid=AfmBOoqWYREXO5kPRHeK8RJEhdIrDtdgziN-W43G7vBF5jUqVc2xdKFs&offerId=16966271625)

[3] [Dioda laserowa](https://botland.com.pl/diody-laserowe/6450-dioda-laserowa-5mw-czerwona-650nm-5v-5904422359782.html?fbclid=IwY2xjawORoTJleHRuA2FlbQIxMQBzcnRjBmFwcF9pZAEwAAEeU0MX-_L_6ckLLX5QRtH2c6XSK5l_QpNnZLTN1bODtjs-2byMYA6vUx8hx94_aem_6dgLEy4zyfoWA5QvmAFC8A)

[4] [Fotorezystor](https://elektronika-sklep.pl/optoelektronika/fotoelementy/fotorezystory/fotorezystor-5mm-100-200k/?fbclid=IwY2xjawORqNhleHRuA2FlbQIxMQBzcnRjBmFwcF9pZAEwAAEeG1kzohAH_HdGkt7z82fvCJQmGnMkdrB9Mw_BGysIL0F0G1z1QGHBzc2wwVo_aem_mB-4tn0mwwQVgGLDJ65VEQ)

[5] [Tranzystor](https://elektronika-sklep.pl/polprzewodniki/tranzystory/tranzystory-unipolarne/tranzystory-z-kanaem-typu-n/2n7000/?fbclid=IwY2xjawORqcJleHRuA2FlbQIxMQBzcnRjBmFwcF9pZAEwAAEeKaQe5YZHMRHeTbCblmyZBrIzwe_R7SG2qjjHs19iOXayLYYCJ6gyZxevm3w_aem_jJXRZwPsxqHWLMGNbZ7itg)

[6] [Mikrokontroler](https://botland.com.pl/moduly-wifi-i-bt-esp32/21859-seeed-xiao-esp32-c3-wifibluetooth-seeedstudio-113991054.html)

[7] [Płytka drukowana do lutowania](l.messenger.com/l.php?u=https%3A%2F%2Fbotland.com.pl%2Fplytki-uniwersalne%2F2744-plytka-drukowana-uniwersalna-dwustronna-40x60mm-5904422303297.html&h=AT0iM1pIM4rylPPTv-ln3OiRvIT1WWi_INN2hKSjnTGUCpENc7v5Qc4CKn1a4ZpNlS-LD7xwWBBMzHVcvjrNCfumq-jdFOZivjr0glafdcMqE_LVTLSooL7hBR4sf2ZCY3R-NQ)


