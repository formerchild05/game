# 🐍 Snake Game - Two Player Edition

A classic Snake game built with C++ and SDL2, featuring two-player gameplay with different controls and special power-ups.

![Snake Game](https://img.shields.io/badge/Language-C++-blue.svg)
![SDL2](https://img.shields.io/badge/Graphics-SDL2-green.svg)
![Platform](https://img.shields.io/badge/Platform-Windows-lightgrey.svg)

## 🎮 Game Features

- **Two-Player Gameplay**: Battle against a friend!
- **Player 1 (Blue Snake)**: Arrow keys control
- **Player 2 (Red Snake)**: WASD keys control
- **Special Power-ups**:
  - 🍎 **Red Apple**: Normal food (+1 segment)
  - 🥇 **Golden Apple**: Appears every 5 segments (+3 segments)
  - 🍃 **Green Apple**: Appears every 3 segments (removes opponent's segment)
- **Audio**: Background music and sound effects
- **Volume Control**: Adjustable in-game volume controls

## 📋 System Requirements

### **Essential Requirements**

1. **Operating System**: Windows (tested on Windows 10/11)
2. **Visual Studio Code**: Latest version recommended
3. **C++ Compiler**: MinGW-w64 (GCC) or equivalent
4. **Minimum RAM**: 512 MB
5. **Disk Space**: ~50 MB

### **What's Already Included**

✅ **SDL2 Libraries** (in `depen/` folder)  
✅ **SDL2 Runtime DLLs** (in root folder)  
✅ **Game Assets** (images, sounds)  
✅ **Build Configuration** (VS Code tasks)

## 🚀 Quick Start Guide

### **Step 1: Install Prerequisites**

1. **Download and Install Visual Studio Code**
   - Visit: https://code.visualstudio.com/
   - Download and install for Windows

2. **Install MinGW-w64 (C++ Compiler)**
   
   **Option A - MSYS2 (Recommended):**
   - Download from: https://www.msys2.org/
   - Install and run these commands:
   ```bash
   pacman -S mingw-w64-x86_64-gcc
   pacman -S mingw-w64-x86_64-gdb
   ```
   - Add `C:\msys64\mingw64\bin` to your Windows PATH

   **Option B - Pre-built MinGW:**
   - Download from: https://winlibs.com/
   - Extract and add to Windows PATH

3. **Verify Installation**
   ```powershell
   g++ --version
   ```
   Should display GCC version information.

### **Step 2: Set Up the Project**

1. **Clone or Download** this repository
2. **Open in VS Code**: 
   - Launch VS Code
   - File → Open Folder
   - Select the `snake` project folder

### **Step 3: Build and Run**

#### **Method 1: Using VS Code Tasks (Easiest)**

1. **Build the Game:**
   - Press `Ctrl+Shift+B` (Build shortcut)
   - Or: `Ctrl+Shift+P` → "Tasks: Run Build Task"

2. **Run the Game:**
   - Press `Ctrl+Shift+P`
   - Type "Tasks: Run Task"
   - Select **"run snake"**

#### **Method 2: Using Terminal**

1. **Open Terminal in VS Code:** `Ctrl+`` (backtick)

2. **Build:**
   ```powershell
   g++ -Idepen/include src/main.cpp -Ldepen/lib -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -o snake.exe
   ```

3. **Run:**
   ```powershell
   ./snake.exe
   ```

## 🎯 How to Play

### **Game Controls**
- **Player 1 (Blue Snake)**: Arrow Keys (←↑↓→)
- **Player 2 (Red Snake)**: WASD Keys
- **Menu**: Click "Play" button with mouse
- **Volume**: Click volume up/down/mute buttons
- **Quit**: Press Space during win screen or close window

### **Game Rules**
1. **Objective**: Grow your snake by eating apples
2. **Avoid**: Hitting walls, yourself, or your opponent
3. **Win Conditions**:
   - Opponent hits a wall or snake body
   - Head-to-head collision (longer snake wins)
4. **Power-ups**:
   - Every 5th segment: Golden apple appears (+3 segments)
   - Every 3rd segment: Green apple appears (shrinks opponent)

## 🔧 Troubleshooting

### **Common Issues**

**"g++ is not recognized"**
- Solution: Add MinGW-w64 to Windows PATH
- Verify: `where g++` should show compiler location

**"SDL.h: No such file or directory"**
- This shouldn't happen as SDL2 is bundled
- Verify `depen/include/` folder exists

**Game crashes on startup**
- Ensure all DLL files are in the root folder
- Check that all image/sound files are present

**No sound/music**
- Verify audio files (.wav, .mp3) are in root folder
- Check Windows audio settings

### **Build Errors**
If you encounter build errors, try:
1. Clean build: Delete `snake.exe` and rebuild
2. Check file paths are correct
3. Ensure all source files are present

## 📁 Project Structure

```
snake/
├── README.md                 # This file
├── snake.exe                 # Compiled game (after build)
├── *.png, *.jpg             # Game graphics
├── *.wav, *.mp3             # Game audio
├── *.dll                    # SDL2 runtime libraries
├── .vscode/
│   └── tasks.json           # VS Code build configuration
├── depen/
│   ├── include/             # SDL2 header files
│   └── lib/                 # SDL2 library files
└── src/
    ├── main.cpp             # Main game file
    ├── main.h               # Main headers
    ├── snake.h              # Snake class definitions
    ├── function.h           # Game logic functions
    └── input_map.txt        # Input configuration
```

## 🛠️ Development

### **Recommended VS Code Extensions**
- C/C++ (Microsoft) - IntelliSense and debugging
- C/C++ Themes - Better syntax highlighting
- Code Runner - Quick code execution

### **Modifying the Game**
- **Graphics**: Replace PNG/JPG files with same names
- **Audio**: Replace WAV/MP3 files with same names  
- **Game Logic**: Edit files in `src/` folder
- **Controls**: Modify input handling in `snake.h`

## 🤝 Contributing

1. Fork the repository
2. Create a feature branch
3. Make your changes
4. Test thoroughly
5. Submit a pull request

## 📄 License

This project is open source. Feel free to use, modify, and distribute.

## 🏆 Credits

- **SDL2**: Graphics and audio library
- **Game Assets**: Custom sprites and sounds
- **Development**: Built with C++ and love ❤️

---

**Enjoy the game! 🐍🎮**

*For issues or questions, please check the troubleshooting section above.*
