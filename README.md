# Audi A4 B5 Bordcomputer

Ein erweiterbares Arduino-Grundgerüst für einen ESP32 und ein 3,2-Zoll-SPI-TFT
mit ILI9341. Die Oberfläche ist auf den Hochkant-Einbau (240 x 320 Pixel)
ausgelegt, verwendet Schrift in `#BF1B2A` auf einem Hintergrund in `#58222F`
und zeigt die Digitalgeschwindigkeit groß in der Mitte. Die Farben werden als
RGB565 quantisiert; die Kanalreihenfolge und Displayrotation verwaltet der
ILI9341-Treiber.

## Aufbau

- `BoardComputer` taktet die Aktualisierung und verbindet Datenquelle und
  Display.
- `ITelemetrySource` ist die Schnittstelle für Fahrzeugdaten. Die aktuelle
  `DemoTelemetrySource` liefert nur simulierte Geschwindigkeit; sie liest keine
  Fahrzeugsignale.
- `IDashboardDisplay` entkoppelt die Anwendung von der Display-Hardware.
- `TftDashboardDisplay` zeichnet die ILI9341-Oberfläche.
- `DisplayConfig.h` enthält die an die konkrete ESP32- und Displayplatine
  anzupassenden GPIOs. GPIO 21 (D21) wird beim Start als Ausgang auf HIGH
  gesetzt und hält damit die Display-Hintergrundbeleuchtung eingeschaltet.
  Für TFT-CS und TFT-DC werden GPIO 27 und GPIO 22 verwendet, um
  ESP32-Strapping-Pins zu vermeiden.

Weitere Messwerte können als Felder in `TelemetryData` ergänzt und über eine
eigene Implementierung von `ITelemetrySource` bereitgestellt werden. So bleibt
die Anzeige unabhängig davon, ob die Daten später von Sensoren, einem
separaten Interface oder einer anderen Quelle kommen.

## Bauen

Das Projekt ist für PlatformIO mit dem Board-Profil `esp32dev` eingerichtet.
Vor dem Bauen die Platinenbelegung in `include/DisplayConfig.h` mit den
tatsächlichen Anschlüssen abgleichen. Im PlatformIO-Projektverzeichnis:

```text
pio run
pio run --target upload
```

## Fahrzeuganschluss

Die aktuelle Demo ist nicht für den Anschluss an Fahrzeugleitungen gedacht.
Fahrzeug-Signale dürfen nicht direkt an ESP32-GPIOs angeschlossen werden.
Eingänge müssen anhand des jeweiligen Signals elektrisch passend geschützt
und auf den zulässigen ESP32-Pegel umgesetzt werden; die konkrete
Signalaufbereitung wird erst mit den später festgelegten Datenquellen ergänzt.
