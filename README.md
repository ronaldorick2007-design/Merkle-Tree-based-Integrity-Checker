# Merkle Chain Integrity Checker

A menu-driven C project demonstrating Merkle trees, SHA-256 hashing, a doubly linked block chain, recent-transaction retrieval, and integrity checking. The chain is stored in memory and is lost when the program exits.

## Project files

The source is split into modules:

- `main.c` — menu and application flow
- `merkle.c` / `merkle.h` — SHA-256 helpers and Merkle-tree operations
- `blockchain.c` / `blockchain.h` — block creation and doubly linked chain
- `integrity.c` / `integrity.h` — integrity verification
- `input.c` / `input.h` — input helpers
- `common.h` — shared constants and data structures

Keep all `.c` and `.h` files in the same project directory. The commands below compile all implementation files together; do not compile the header files separately.

## Requirements

- A C compiler (Clang or GCC)
- OpenSSL development files (`libcrypto`)

## Build, compile, and run

Run the commands from the directory containing `main.c`, `merkle.c`, `blockchain.c`, `integrity.c`, and `input.c`.

### macOS

**1. Install dependencies** (requires Homebrew):

```bash
brew install openssl@3
```

**2. Compile:**

```bash
clang -Wall -Wextra -std=c11 \
  main.c merkle.c blockchain.c integrity.c input.c \
  -I"$(brew --prefix openssl@3)/include" \
  -L"$(brew --prefix openssl@3)/lib" \
  -lcrypto -o merkle_chain
```

**3. Run:**

```bash
./merkle_chain
```

### Linux (Debian/Ubuntu)

**1. Install dependencies:**

```bash
sudo apt update
sudo apt install build-essential libssl-dev
```

**2. Compile:**

```bash
cc -Wall -Wextra -std=c11 \
  main.c merkle.c blockchain.c integrity.c input.c \
  -lcrypto -o merkle_chain
```

**3. Run:**

```bash
./merkle_chain
```

### Windows (MSYS2 UCRT64)

**1. Install MSYS2** from <https://www.msys2.org/> and open the **MSYS2 UCRT64** terminal from the Start menu.

**2. Install the compiler and OpenSSL:**

```bash
pacman -S --needed mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-openssl
```

**3. Change to the project directory.** Replace the example path with your actual folder path:

```bash
cd /c/Users/YourName/path/to/merkle_chain_integrity_checker
```

**4. Compile:**

```bash
gcc -Wall -Wextra -std=c11 \
  main.c merkle.c blockchain.c integrity.c input.c \
  -o merkle_chain.exe -lcrypto
```

**5. Run:**

```bash
./merkle_chain.exe
```

Use the **MSYS2 UCRT64** terminal for the Windows commands so GCC can locate the OpenSSL headers and library.

## Research references

See [`RESEARCH_PAPERS.md`](RESEARCH_PAPERS.md) for foundational papers and specifications on Merkle trees, authenticated data structures, and tamper-evident logs.

## Important limitations

- The chain exists only in memory and is lost when the program exits.
- The trusted reference is the original chain in memory. This demo does not authenticate an external root, persist data, sign blocks, or implement a consensus/network protocol.
- The integrity check re-enters all transactions in the same order and independently recomputes candidate Merkle roots and block hashes. The stored chain is not replaced.
- Leaf hashes use `SHA256(0x00 || transaction)`, and internal hashes use `SHA256(0x01 || left_hash || right_hash)`. If a level has an odd number of nodes, the last hash is duplicated. The builder and verifier must use the same conventions.
- This is a teaching project, not production blockchain software.

## Real-world references

- Bitcoin Developer Reference — [Merkle trees](https://bitcoin.org/en/developer-reference#merkle-trees)
- Git object model — [Git Internals: Git Objects](https://git-scm.com/book/en/v2/Git-Internals-Git-Objects)
- IPFS — [Merkle DAG specification](https://github.com/ipfs/specs/blob/main/MERKLE_DAG.md)
- C Merkle-tree library — [isec-tugraz/merkle-tree](https://github.com/isec-tugraz/merkle-tree)
