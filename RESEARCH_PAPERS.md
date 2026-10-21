# Foundational Reading: Merkle Trees

These papers and technical standards are available from their authors or official publishers.

1. **Ralph C. Merkle — *Protocols for Public Key Cryptosystems* (1979 thesis).**
   An early foundational work in public-key cryptography and authentication structures associated with Merkle's work.
   - Thesis PDF: <https://www.ralphmerkle.com/papers/Thesis1979.pdf>
   - Related paper version: <https://www.ralphmerkle.com/papers/Protocols.pdf>

2. **Scott A. Crosby and Dan S. Wallach — *Efficient Data Structures for Tamper-Evident Logging* (USENIX Security Symposium, 2009).**
   Explains tree-based authenticated structures for proving that logged events remain present and that log versions are consistent. This is especially relevant to the project's integrity-checking motivation.
   - Open-access paper PDF: <https://static.usenix.org/events/sec09/tech/full_papers/crosby.pdf>
   - USENIX publication page: <https://www.usenix.org/conference/usenixsecurity09/technical-sessions/presentation/efficient-data-structures-tamper-evident>

3. **Ben Laurie, Adam Langley, and Emilia Kasper — *Certificate Transparency* (RFC 6962, 2013).**
   A practical specification of Merkle hash trees, inclusion/audit paths, and consistency proofs for append-only certificate logs. Read Section 2.1 first.
   - Official RFC: <https://www.rfc-editor.org/rfc/rfc6962.html>
   - PDF: <https://www.rfc-editor.org/pdfrfc/rfc6962.txt.pdf>

4. **B. Laurie et al. — *Certificate Transparency Version 2.0* (RFC 9162, 2021).**
   A later version of the Certificate Transparency specification. Useful for seeing how Merkle trees are used in a modern, deployed protocol.
   - Official RFC: <https://www.rfc-editor.org/rfc/rfc9162.html>
   - PDF: <https://www.rfc-editor.org/pdfrfc/rfc9162.txt.pdf>

## Suggested reading order

1. Read the Merkle tree definition and examples in RFC 6962, Section 2.1.
2. Read Crosby and Wallach for the broader tamper-evident logging application.
3. Consult RFC 9162 to compare a newer protocol specification.
4. Read Merkle's thesis for historical and cryptographic background.

**Connection to this project:** the code hashes each transaction as a leaf, combines child hashes to compute a Merkle root, and includes that root in a block hash. This educational implementation is not a complete production blockchain or Certificate Transparency implementation; it does not provide signed roots, distributed consensus, or independently trusted root authentication.
