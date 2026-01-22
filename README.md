# 🧩 WordSearch Generator

A basic word search and solution generater.

## ✨ Features

- **Custom Dimensions:** Generate grids of any size (e.g. 10x10 or 50x50).
- **Batch Word Loading:** Import word lists directly from `.txt` files.
- **Supports Many Formats:** No specific format required for the input file.
- **Dual Ouput:** Automatically exports two files:
    1. `word_search.txt`: The playable puzzle filled with random characters.
    2. `solution.txt`: The answer key showing only the hidden words.

---

## 🚀 Getting Started

### Compilation

1. **Create and enter teh build directory:**
```bash
mkdir build && cd build
```

2. **Configure the project:**
```bash
cmake ..
```

3. **Build the executable**
```bash
cmake --build .
```

*Note: The executable `wordSearch.exe` will be located in the `build/` folder (or `build/Debug/` on Windows).*

## 💻 Usage

```bash
./wordSearch.exe <width> <height> <path to words> <output path>
```

### Example

```bash
./wordSearch.exe 20 20 words.txt ./output
```

## 📄 Input File Format

The program automatically identifies the words in the file which you provide. So no format needed!

## 🖼️ Example Output

#### word_search.txt

```
B K R B C ...
U S N P X ...
Y C T X Y ...
H A Z Q H ...
O E V E D ...
...
```

#### solution.txt

```
. . . . . ...
. . . . . ...
. . . . . ...
H . . . . ...
O . . . . ...
...
```

## ⚠️ Known Limitations

- Ensure the grid is larger than the longest word