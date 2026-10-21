# Merkle-Tree-based-Integrity-Checker

Menu-driven educational DSA case study using C and OpenSSL SHA-256.

## Features
1. Build a chain by entering multiple blocks, each with multiple transactions.
2. Add a new block to the chain.
3. Display all blocks, transactions, Merkle roots, previous hashes, and block hashes.
4. Display the Merkle tree for a selected block.
5. Retrieve the most recent N transactions.
6. Check integrity by re-entering candidate data in the original order.
7. Display architecture notes.

## Data structure design
- Blocks are connected in memory as a **doubly linked list** (`prev` and `next` pointers).
- Every block contains several transaction strings.
- Every block has its own binary Merkle tree over those transactions.
- Each block hash commits to its index, previous block hash and Merkle root.
- This reflects the common blockchain pattern: a block links to its predecessor, while its Merkle root commits to the transactions inside that block. The chain itself is not one Merkle tree.

## Build on macOS
Install OpenSSL with Homebrew:
```bash
brew install openssl@3
```
Apple Silicon example:
```bash
clang -Wall -Wextra -std=c11 merkle_chain.c \
  -I/opt/homebrew/opt/openssl@3/include \
  -L/opt/homebrew/opt/openssl@3/lib -lcrypto -o merkle_chain
./merkle_chain
```
On Intel Macs, Homebrew may use `/usr/local` instead of `/opt/homebrew`; adjust paths.

## Build on Ubuntu/Linux
```bash
sudo apt install build-essential libssl-dev
cc -Wall -Wextra -std=c11 merkle_chain.c -lcrypto -o merkle_chain
./merkle_chain
```
## Build on Windows
MSYS2 (Recommended for MinGW-w64 + OpenSSL)
## Open the MSYS2 UCRT64 terminal.

Install GCC and OpenSSL packages:

## Bash
pacman -S mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-openssl
Compile and run:

## Bash
gcc -Wall -Wextra -std=c11 merkle_chain.c -lcrypto -o merkle_chain.exe
./merkle_chain.exe

## Suggested demo
1. Choose option 1; build 2 blocks with 2 transactions each.
2. Choose option 3 to show the linked blocks and hashes.
3. Choose option 4 and display Block 0's Merkle tree.
4. Choose option 5 and request the most recent 3 transactions.
5. Choose option 6 and re-enter all transactions exactly as before. Expected result: `INTEGRITY VERIFIED`.
6. Choose option 6 again, changing one character in one transaction. Expected result: `INTEGRITY CHECK FAILED`.
7. Choose option 2 to add a block and show that it links to the prior block hash.

## Important limitations
- The chain exists only in memory and is lost on exit.
- The trusted reference is the original chain in memory. This demo does not authenticate an external root, persist data, sign blocks, or implement a consensus/network protocol.
- The integrity check re-enters all transactions in the same order and independently recomputes candidate Merkle roots and block hashes. The stored chain is not replaced.
- Leaf hashes use `SHA256(0x00 || transaction)`, and internal hashes use `SHA256(0x01 || left_hash || right_hash)`. If a level has an odd number of nodes, the last hash is duplicated. Exact conventions must be shared by builder and verifier.
- This is a teaching project, not production blockchain software.

## Real-world references
- Bitcoin developer reference: https://bitcoin.org/en/developer-reference#merkle-trees
- Git object model: https://git-scm.com/book/en/v2/Git-Internals-Git-Objects
- IPFS Merkle DAG specification: https://github.com/ipfs/specs/blob/main/MERKLE_DAG.md
- C Merkle-tree library reference: https://github.com/isec-tugraz/merkle-tree

## Suggested genuine commit plan
1. Define block/chain structures and menu.
2. Implement SHA-256 leaf and parent hashing.
3. Implement Merkle-root construction.
4. Implement block creation and previous-hash linkage.
5. Implement display and recent-transaction retrieval.
6. Implement integrity verification.
7. Test edge cases and document design/limitations.

Make commits as the work is developed; don't fabricate contribution history.
