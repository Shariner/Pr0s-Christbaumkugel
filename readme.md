Bedienungsanleitung Christbaumkugel:
Du benötigst bisher leider noch die App „nRF Connect“.

1.	Verbinde deine Christbaumkugel mit Strom
2.	Starte die nRF Connect App
3.	Suche im Scanner nach „PrinceRuperts Christbaumkugel“ und verbinde dich mit dieser.
4.	Gehe auf der Rechten Seite des Bildschirmes zum Punkt Services.
5.	Du siehst nun 3 Zeilen, in der Pfeile nach oben oder unten zu sehen sind. Zum Senden eines Befehls, klicke auf den Pfeil nach oben (push), gebe den Wert ein, den du senden möchtest und versende diesen Wert als UTF-8 Wert (Die anderen akzeptiert der Arduino nicht).


Erste Zeile: Schaltet die Christbaumkugel an/aus. Mit den Befehlen an, An, on, On oder 1 schaltest du Sie ein, alles andere schaltet Sie aus.

Zweite Zeile: Farbwahl. Mögliche Befehle: red, orange, yellow, green, lime, blue, purple, magenta, jump7, jump, fade – alles andere wird die Kugel weiß setzen.

Dritte Zeile: Animationen. Mögliche Befehle: once, double, strobo, brightfade, rainbow, rainbow-pure


Es gibt ein paar Bugs. Manchmal spinnen die LEDs ein wenig (vllt hab ich doch zu unsauber programmiert), die Sachen wie Rainbow verstehe ich nicht mal (die hab ich einfach aus ner example library kopiert und versucht anzupassen.

TODO: 
-	Mal eine App in Android Studio für den Kram entwickeln (ich wette dazu komme ich nie)
-	Unbedingt nen Schalter dranlöten, denn sonst tiefenentlädt der Arduino innerhalb 24 Stunden den Akku (Ich kam aber nicht dazu, da ich handwerklich wohl nicht begabt bin. Mir ist die Kugel beim Versuch da einen Schalter einzulassen, kaputt gegangen.
-	Ein technisches Bauteil mit verlöten, das den Akku vor Tiefenentladung schützt.
