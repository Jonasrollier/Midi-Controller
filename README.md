# Midi-Controller

Firmware-project voor een MIDI controller op basis van een **STM32** (STM32CubeMX / STM32CubeIDE projectstructuur).  
Dit project bevat de volledige firmware, drivers en middleware (o.a. USB via TinyUSB) om een MIDI-device te kunnen bouwen.


---

## Inhoud

- [Features](#features)
- [Benodigdheden](#benodigdheden)
- [Project openen & builden](#project-openen--builden)
- [Flashen & debuggen](#flashen--debuggen)
- [Folderstructuur](#folderstructuur)
- [Configuratie (CubeMX)](#configuratie-cubemx)
- [Troubleshooting](#troubleshooting)
- [Licentie](#licentie)

---

## Features

- STM32CubeMX `.ioc` configuratie inbegrepen
- STM32CubeIDE projectbestanden aanwezig (`.project`, `.cproject`, `.settings`)
- Linker scripts voor Flash en RAM builds
- USB stack via TinyUSB (middleware in `Core/Middlewares/...`)

*(Vul gerust aan met je exacte functionaliteit zoals: knoppen, encoders, faders, MIDI CC mapping, LEDs, display, etc.)*

---

## Benodigdheden

- **STM32CubeIDE** (aanbevolen)  
  *(Alternatief: GCC toolchain + make, maar dit repo lijkt vooral CubeIDE-gericht.)*
- **STM32CubeMX** (optioneel, maar handig om `.ioc` te beheren)
- Een STM32 board/target dat overeenkomt met de configuratie (zie `.ioc`)
- Debug probe (optioneel, maar handig): **ST-LINK**

---

## Project openen & builden

1. Clone de repository:
   - Via HTTPS of SSH in GitHub

2. Open in STM32CubeIDE:
   - `File` → `Open Projects from File System...`
   - Selecteer de map: `MIDI controller/`

3. Build:
   - Klik op de build-knop (hamer-icoon) of `Project` → `Build Project`

---

## Flashen & debuggen

- Er staat een launch-config in de repo:
  - `MIDI controller/MIDI controller.launch`

Typisch:
1. Sluit je ST-LINK / board aan
2. `Run` of `Debug` in CubeIDE
3. Kies de bestaande launch-config indien nodig

---

## Folderstructuur

Onderstaande structuur is gebaseerd op wat momenteel in de repo staat:

```text
.
├── README.md
└── MIDI controller/
    ├── .cproject
    ├── .mxproject
    ├── .project
    ├── .settings/
    ├── Core/
    ├── Debug/
    ├── Drivers/
    ├── MIDI controller.ioc
    ├── MIDI controller.launch
    ├── STM32H533RETX_FLASH.ld
    └── STM32H533RETX_RAM.ld
```

### Belangrijkste mappen (kort)

- `MIDI controller/Core/`  
  Applicatiecode, CubeMX gegenereerde code, en (in veel STM32 projecten) ook middleware.  
  In jouw repo zit hier o.a. TinyUSB onder `Core/Middlewares/...` (dieper in de tree).

- `MIDI controller/Drivers/`  
  STM32 HAL/LL drivers en CMSIS (klassieke CubeMX output).

- `MIDI controller/Debug/`  
  Build output (artefacts).  
  **Tip:** meestal zet je build outputs in `.gitignore`, maar soms staat het er bewust in.

---

## Configuratie (CubeMX)

De CubeMX configuratie staat in:

- `MIDI controller/MIDI controller.ioc`

Aanpassingen aan clocks/pins/peripherals doe je meestal in CubeMX via dit bestand.  
Daarna “Generate Code” om de projectbestanden bij te werken.

---

## Troubleshooting

- **Project opent maar build faalt**
  - Check of je STM32CubeIDE de juiste toolchain en device packs heeft.
  - Doe eventueel: `Project` → `Clean...` en build opnieuw.

- **USB/MIDI werkt niet**
  - Controleer clocks en USB-pin mapping in de `.ioc`
  - Controleer of TinyUSB correct geconfigureerd is voor jouw MCU/USB peripheral

---

## Licentie

Nog niet gespecificeerd.  
Kies een licentie (bv. MIT, Apache-2.0, GPL-3.0) en voeg een `LICENSE` bestand toe als je het project wil delen/hergebruiken.
