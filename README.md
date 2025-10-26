# High-Performance C++ Code Generator for Binary Financial Protocols

## Project Overview

This project is a sophisticated, low-latency C++ code generator for the **Binary Order Entry (BOE) protocol**, a system used in high-frequency trading (HFT) and financial exchanges.

The core of this project is a **Python script** that parses a human-readable **YAML schema** of the protocol. It uses a **Jinja2 templating engine** to automatically generate a complete, high-performance C++ library for encoding and decoding BOE messages.

This approach solves a critical problem in FinTech: it automates the creation of fast, accurate, and maintainable serialization code, eliminating the risk of manual error and dramatically speeding up development.

## The Problem

In high-frequency trading, every nanosecond matters. Developers must manually write C++ code to serialize (encode) and deserialize (decode) complex, low-latency binary protocols. This manual process is:
* **Error-Prone:** A single mistake in bit-shifting or byte alignment can lead to corrupt data and significant financial loss.
* **Time-Consuming:** Manually coding for dozens of complex message types is a slow, tedious process.
* **Hard to Maintain:** When the exchange updates the protocol, developers must painstakingly find and update every part of the codebase.

## The Solution

This project builds a **code generator** that acts as a "factory" for C++ messaging code.

1.  **Define:** A developer defines the entire protocol in a simple, human-readable YAML file.
2.  **Generate:** The Python script reads this YAML file and automatically generates all the necessary C++ headers (`Encoder.h`, `Decoder.h`, `Messages.h`).
3.  **Use:** The generated C++ code is highly optimized, header-only, and can be directly included in a trading application for ultra-low-latency performance.

If the protocol changes, the developer only needs to update the YAML file and re-run the generator, saving days or weeks of work.

## Technology Stack

* **Core Generator:** **Python**
* **Templating Engine:** **Jinja2**
* **Schema Definition:** **YAML**
* **Generated Code:** **C++ (17/20)**
* **Domain:** **FinTech (High-Frequency Trading)**, Binary Protocols, Low-Latency Systems

## Skills Demonstrated

* **Systems Architecture:** Designing a robust, maintainable system for mission-critical applications.
* **Metaprogramming (Code Generation):** Using code (Python) to write other code (C++), a powerful technique for reducing errors and increasing productivity.
* **Low-Latency C++:** Generating C++ code that is optimized for performance by using modern techniques like `constexpr`, `static polymorphism`, and avoiding runtime overhead.
* **FinTech Domain Knowledge:** Deep understanding of the challenges in high-frequency trading, including binary serialization, protocol specifications, and the critical need for speed and accuracy.
* **Automation:** Building a tool that automates a complex and error-prone manual task, showcasing an ability to improve developer workflows.

## How to Run

1.  **Inspect the Schema:** Review `src/c1_boe_2_11_68.yaml` to see how the BOE protocol is defined.
2.  **Inspect the Templates:** Look at the `.j2` files in `src/templates/` to see the C++ "blueprints."
3.  **Generate the Code:** Run the Python generator script.
    ```bash
    python3 src/generate_codec.py --config src/c1_boe_2_11_68.yaml --create
    ```
4.  **Review the Output:** Observe the generated C++ files inside `src/codecs/C1/BOE/2_11_68/`.
<br>
Arigatoooo! 🙏
