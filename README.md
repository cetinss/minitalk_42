# minitalk\_42

> A simple client–server messaging system using UNIX signals (SIGUSR1 & SIGUSR2), written in C.\
> Includes optional Unicode (UTF-8) support.

---

## 📖 Overview

`minitalk` is a 42‑Piscine project that teaches you how to communicate between processes on a UNIX/Linux system **without** sockets or shared memory—only **signals**.

- The **server** waits for signals, reconstructs bits into characters, and prints messages.
- The **client** takes a server PID and a text string, then sends each character **bit by bit** using `signal()`.

This README explains every step—from concept to code—so that even a newcomer can understand and run the project.

---

## 🔑 Prerequisites

- UNIX/Linux environment
- C compiler (`gcc` or `cc`)
- Basic terminal usage

---

## ⚙️ How It Works

1. **Bit Encoding**\
   Each character is 8 bits (MSB → LSB).

2. **Signal Mapping**

   - `SIGUSR1` → bit `0`
   - `SIGUSR2` → bit `1`

3. **Client Workflow**

   1. Read **server PID** and **message** from arguments.
   2. For each character:
      - Loop through its bits (MSB to LSB).
      - Use `kill(server_pid, SIGUSR1 or SIGUSR2)` to send each bit.
      - Pause briefly (`usleep()`) to allow the server to process.

4. **Server Workflow**

   1. Set up `signal(SIGUSR1, handler)` and `signal(SIGUSR2, handler)`.
   2. In the handler function:
      - Shift a static accumulator left by one.
      - Add **`0`** or **`1`** depending on which signal arrived.
      - After 8 bits, convert to a character and `write()` to STDOUT.
      - Reset accumulator and bit counter.

---

## 🗂 Project Structure

```
minitalk_42/
├── Makefile
├── minitalk.h
├── server.c
├── client.c
├── server_bonus.c       # Unicode-aware server
├── client_bonus.c       # Unicode-aware client
└── README.md            # ← You are here!
```

- **Makefile**

  - Targets: `all`, `bonus`, `clean`, `fclean`, `re`
  - `all`: builds `server` & `client`
  - `bonus`: builds `server_bonus` & `client_bonus`

- **minitalk.h**: common headers & prototypes

- **server.c / client.c**: mandatory ASCII-only code

- **server\_bonus.c / client\_bonus.c**: adds UTF-8 support

---

## 🛠 Compilation

```bash
# Standard (ASCII only):
make

# With Unicode (UTF-8) support:
make bonus
```

- `make clean`  → remove `.o` files
- `make fclean` → remove executables & `.o` files
- `make re`     → `fclean` then `all`

---

## 🚀 How to use ?

Follow these detailed steps to set up, compile, and run the `minitalk_42` project—even if you have no prior experience:

1. **Clone the repository**
   ```bash
   # Replace <your-path> with the folder where you want the project
   git clone https://github.com/cetinss/minitalk_42.git <your-path>/minitalk_42
   ```

2. **Change into the project directory**
   ```bash
   cd <your-path>/minitalk_42
   ```

3. **Compile the programs**
   - **Standard version (ASCII only):**
     ```bash
     make
     ```
     This creates two executables: `server` and `client`.

   - **Unicode version (UTF‑8 support):**
     ```bash
     make bonus
     ```
     This creates `server_bonus` and `client_bonus`.

4. **Prepare two terminal windows**
   - **Terminal 1:** for running the server.
   - **Terminal 2:** for running the client.

5. **Start the server**
   In Terminal 1, type:
   ```bash
   ./server
   ```
   - The server will output its **Process ID (PID)**, for example:
     ```
     Server PID: 27341
     ```
   - **Note:** Keep this terminal open; it will display incoming messages.

6. **Send a message from the client**
   In Terminal 2, type (replace `27341` with the PID printed above):
   ```bash
   ./client 27341 "Hello, 42!"
   ```

   - The client sends each character to the server bit by bit.
   - Back in Terminal 1, you will see the server print your message:
     ```
     Hello, 42!
     ```

7. **Using the Unicode (bonus) version**
   If you compiled with `make bonus`, use these commands instead:
   - **Start Unicode server** (Terminal 1):
     ```bash
     ./server_bonus
     ```
   - **Send Unicode message** (Terminal 2):
     ```bash
     ./client_bonus 27341 "Merhaba Dünya 🌍"
     ```
   - Terminal 1 will display:
     ```
     Merhaba Dünya 🌍
     ```

8. **Troubleshooting**
   - If you see no output, verify that the **PID** is correct and that the server is still running.
   - If messages appear garbled, increase the `usleep()` delay in `client.c` to give the server more time to process signals.

---

### 🌍 Bonus: Unicode Example

```bash
make bonus
./server_bonus
./client_bonus 27341 "Merhaba Dünya 🌍"
```

Output:

```
Merhaba Dünya 🌍
```

---

## ✅ Allowed Functions & Syscalls

- Signal handling: `signal()`, `kill()`, `getpid()`
- Sync: `pause()`, `usleep()`
- Memory & I/O: `malloc()`, `free()`, `write()`, `exit()`
- Optional: custom `ft_printf`

---

## 🧑‍💻 About Me

I'm a double‐major student in **Electrical & Electronics Engineering** and **Computer Engineering** at **Turkish‐German University**.\
This project was completed at **42 Istanbul** to deepen my understanding of UNIX system programming.

📌 **Explore my other work:** [github.com/cetinss](https://github.com/cetinss)
