# Arduino-basierte Lichtschranke zum Monitoring von Fledermaus-Kastenquartieren

Dieses Repository enthält die wesentlichen Dateien zum Nachbau eines kostengünstigen, Arduino-Nano-basierten Lichtschrankensystems zur automatisierten Erfassung von Aktivität an Fledermaus-Kastenquartieren.

Das System überwacht einen Infrarot-Lichtstrahl zwischen Sende- und Empfängerdiode. Wird der Lichtstrahl unterbrochen, werden fortlaufend Zeitstempel auf einer SD-Karte gespeichert. Sobald der Lichtstrahl wieder frei ist, endet die Aufzeichnung. Das System ist als Ergänzung zu Sichtkontrollen gedacht; Individuenzahl, Flugrichtung und Art können damit nicht bestimmt werden.

## Inhalt des Repositorys

- `hardware/kicad/` – KiCad-Dateien der Platine
- `hardware/gerber/` – Gerber- und Bohrdateien für die PCB-Fertigung
- `software/` – Arduino-Sketch
- `BOM/` – Stückliste
- `images/` – Fotos und Abbildungen des Aufbaus
- Quick Start Guide – Aufbau, Bedienung und Softwareinstallation

## 1. Platine

Die Platine wurde in KiCad erstellt. Die Datei

`lightbeam.kicad_pcb`

enthält das vollständige Platinenlayout und kann bei Herstellern, die native KiCad-Dateien unterstützen, direkt zur Fertigung verwendet werden.

Zusätzlich stehen Gerber- und Bohrdateien zur Verfügung. Für eine herstellerunabhängige Bestellung kann die Datei

`lightbeam_gerber.zip`

verwendet werden. Sie enthält die Kupferlagen, Lötstoppmasken, Bestückungsdrucke, Platinenkontur sowie PTH- und NPTH-Bohrdateien.

## 2. Hauptkomponenten

Das System besteht im Wesentlichen aus:

- Arduino Nano mit ATmega328P
- Infrarot-Sendediode
- Empfängerdiode
- Status-LED
- Hauptschalter und LED-Schalter
- Step-Down-Spannungswandler
- Real-Time Clock (RTC)
- SD-Karten-Modul
- externer Stromversorgung

Die vollständige Stückliste mit Spezifikationen befindet sich im Ordner `BOM/`.

Beim Anschluss von Sende- und Empfängerdiode unbedingt auf die korrekte Polarität achten. Eine falsche Polung kann die Bauteile beschädigen. Sender und Empfänger müssen mit einem maximalen Abstand von 35 cm direkt aufeinander ausgerichtet werden.

## 3. Arduino-Firmware

Der Sketch befindet sich unter:

`software/Lightbeam.ino`

Benötigte Bibliotheken:

- `Wire.h`
- `SPI.h`
- `SD.h`
- `Sodaq_DS3231.h`


## 4. Echtzeituhr einstellen

Vor dem ersten Einsatz muss die RTC auf Datum und Uhrzeit des Computers gesetzt werden.

Für den ersten Upload diese beiden Zeilen im Sketch aktivieren:

`DateTime dt(__DATE__, __TIME__);`
`rtc.setDateTime(dt);`

Sketch hochladen. Anschließend beide Zeilen wieder auskommentieren:

`//DateTime dt(__DATE__, __TIME__);`
`//rtc.setDateTime(dt);`

Danach den Sketch ein zweites Mal hochladen. So wird verhindert, dass die RTC bei jedem Neustart erneut auf den Zeitpunkt der Kompilierung gesetzt wird.



## 5. Inbetriebnahme

1. SD-Karte einsetzen.
2. Sende- und Empfängerdiode korrekt anschließen und aufeinander ausrichten.
3. Stromversorgung anschließen.
4. Falls nötig, Hauptschalter einschalten.
5. LED-Schalter einschalten und Status prüfen.

Beim Start:

- grün blinkend: SD-Karte wird initialisiert
- rot blinkend: SD-Karte wurde nicht erkannt

Im Messbetrieb:

- LED aus: Lichtstrahl ist frei und Sender/Empfänger sind korrekt ausgerichtet
- grün dauerhaft: Lichtstrahl ist unterbrochen oder Sender/Empfänger sind nicht korrekt ausgerichtet

Nach erfolgreicher Kontrolle kann der LED-Schalter ausgeschaltet werden, um Energie zu sparen. Die Datenerfassung läuft weiter.

Vor dem Entfernen der SD-Karte das System über Hauptschalter A ausschalten. Wird die SD-Karte während des Betriebs entfernt, muss das System anschließend neu gestartet werden.

## 6. Datenspeicherung

Die Daten werden in der Datei

`BATBOX.LOG`

auf der SD-Karte gespeichert und bei jeder neuen Sitzung ergänzt.

Beim Start wird unter anderem ein Eintrag mit `started` geschrieben. Bei einer Unterbrechung wird Datum, Uhrzeit und `interruption` gespeichert, zum Beispiel:

`Date,Time,Light_Beam,Others`
`09.10.2026,18:30:01,,started`
`09.10.2026,19:04:23,interruption,`

Solange der Lichtstrahl unterbrochen bleibt, schreibt der aktuelle Sketch fortlaufend weitere Zeitstempel. Eine längere Unterbrechung erzeugt daher mehrere Einträge. Bei Auswertungen können diese beispielsweise zu Aktivitätsminuten zusammengefasst werden.

Die Logdatei kann als Textdatei geöffnet oder unter anderem in Excel oder R importiert werden.

## 7. Stromversorgung

Das System verwendet einen Step-Down-Spannungswandler, der je nach Spezifikation Eingangsspannungen z.B. von 7–24 V auf die benötigten 5 V reduziert. Im beschriebenen Aufbau wird ein Batteriehalter für acht Mono-D-Batterien verwendet; andere geeignete Spannungsquellen im Bereich von 7–24 V sind ebenfalls möglich.

Handelsübliche Powerbanks sind nur eingeschränkt geeignet, da viele Modelle bei geringer Stromaufnahme automatisch abschalten.

## 8. Grenzen des Systems

Die Lichtschranke erfasst ausschließlich Unterbrechungen des Lichtstrahls. Ohne zusätzliche Beobachtungen lassen sich daraus weder die Anzahl der Tiere noch Ein- und Ausflugrichtung oder Artzugehörigkeit bestimmen. Auch andere Tiere oder Objekte können Ereignisse auslösen.

Das System ist daher als kostengünstige Ergänzung zu weiteren Monitoringmethoden zu verstehen.


## 9. Version, Zitierung und Lizenz

Falls das System für wissenschaftliche Arbeiten verwendet wird, bitte die zugehörige Publikation zitieren:
Bergmann & Knörnschild (2026): Bau Arduino-basierter Lichtschranken zum Monitoring von Kastenquartieren. Nyctalus. 


## Kontakt

Anja Bergmann 
Anja [at] bergmann-email.de

