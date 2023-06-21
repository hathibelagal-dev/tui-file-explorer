# 🗄️ tui-file-explorer

🖥️ Just a pretty file explorer that runs in the terminal

🔥 Written in pure C, so it's extremely fast and lightweight

🥦 The executable is just *19048 bytes*

🚀 **Rapidly improving**

### Screenshots

Running on Ubuntu 18.04.3 LTS

![Screenshot from 2023-06-15 00-23-05](https://github.com/hathibelagal-dev/tui-file-explorer/assets/42626106/dd88cb2e-4c64-4e91-8fb4-1120c8a54fdd)

![Screenshot from 2023-06-15 00-19-40](https://github.com/hathibelagal-dev/tui-file-explorer/assets/42626106/8b573821-7083-433b-ac9b-bf17b8f18e1a)

Running inside VS Code's terminal

![Screenshot from 2023-06-15 00-23-38](https://github.com/hathibelagal-dev/tui-file-explorer/assets/42626106/50c9e48a-91e8-4684-889f-8571be6b8e1e)

### Build and Run

On Ubuntu

```bash
sudo apt install libmagic-dev
make
bin/fex
```
You can use `make fast` to create a larger, but faster, binary.

### ⌨️ Controls

**w** - go up a file

**s** - go down a file

**t** - toggle between hex and ASCII preview

**space** - select current directory

**p** - go to parent directory

**b** - go back to previous directory

**h** - go to home directory

**r** - redraw (necessary after resizing the terminal window)

**q** - quit

