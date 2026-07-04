zvm-dynamic-core

A low-level register-based Virtual Machine (ZVM) integrated with my custom dynamic block-based memory management library (Blobify). This project demonstrates how I execute dynamic bytecode injected and managed directly within runtime-allocated memory blobs.
 Overview

In this project, I integrated two distinct architectural layers that I built from scratch:

    Blobify: My custom C library for safe dynamic memory block allocation, navigation via cursors, and range-based bounds tracking.

    ZVM: My minimal register-based CPU simulator with custom instructions, register manipulation, and I/O handling.

By merging these layers, I dynamically write bytecode instructions into controlled memory blobs before passing them directly to the execution pipeline of my virtual machine processor.
 Architecture & Integration

My core workflow relies on using Blobify as the dynamic RAM environment and ZVM as the CPU execution core:

    Memory Creation: I initialize a managed blob of a custom size (e.g., 64 bytes).

    Bytecode Injection: I sequentially push instructions (consisting of 4-byte packages: Opcode, Registers, Immediate Values) into the blob using my cursor step functions.

    Execution: The underlying raw base pointer of the validated memory block is handed over to my VM engine (zvm_main) for runtime execution.
