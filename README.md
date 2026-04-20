## Pixel Courier (v1.0.0-beta) — Windows x64

Precompiled beta build of the 2D game **Pixel Courier**.

### What’s included

- Windows x64 build (SFML runtime + assets)

### Download / Run

1. Go to **Releases** and download: `Distribution.PixelCourier.zip`  
   **Important:** Do NOT download “Source code (zip/tar.gz)” — that is not the playable build.
2. Extract the ZIP (do NOT run the game from inside the ZIP).
3. Run `PixelCourier.exe`.

### Windows Defender SmartScreen (Run anyway)
If Windows shows a warning like **“Windows protected your PC”**:
1. Click **More info**
2. Click **Run anyway**

*This is a warning message of unknown app so you can skip it*

### Requirements

- It runs on Win 10 (x64), 11 (x64)
- **Microsoft Visual C++ Redistributable 2015–2022 (x64)**  
  Official download: https://learn.microsoft.com/en-us/cpp/windows/latest-supported-vc-redist?view=msvc-170  
  Or you can download it from  folder `Distribution PixelCourier\Microsoft Visual Redistributions.`

### Folder structure (do not change)

- **Keep all folders and files exactly as they are after extracting the ZIP!**
- **Any change will may crash the game and/or will not start correctly!**
- **Currently the game does not supports shortcut for the `.exe` file!**

### Troubleshooting

- **“VCRUNTIME140.dll was not found” / “MSVCP140.dll was not found”.**

*Install **Microsoft Visual C++ Redistributable 2015–2022 (x64)** and run the game again.*

**“sfml-graphics-2.dll was not found” (or other sfml-.dll missing)**
- Make sure these files are next to `PixelCourier.exe` (same folder):
- `sfml-graphics-2.dll`
- `sfml-window-2.dll`
- `sfml-system-2.dll`
- `sfml-audio-2.dll`
- `sfml-network-2.dll`
- `openal32.dll`

**Important (Debug vs Release DLLs):**
- Release DLLs look like: `sfml-graphics-2.dll` (NO `-d`)
- Debug DLLs look like: `sfml-graphics-d-2.dll` (contains `-d`)  
For distribution you must use **Release DLLs** (NO `-d`).

**Missing sprites / wrong positions**
Keep these folders next to the `.exe`:
- `assets/`
- `fonts/`
- `sounds/`
- `PixelCourier/` (contains the `.txt` config files)

*Changing the `.txt` files will have an unexpected consequences afterwards when starting the game!*

### Controls
- W,A,S,D — Move
