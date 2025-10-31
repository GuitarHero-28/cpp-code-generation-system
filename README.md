High-Performance C++ Code Generator for Binary Financial Protocols

Project Overview

This project is a sophisticated, low-latency C++ code generator for the Binary Order Entry (BOE) protocol, a system used in high-frequency trading (HFT) and financial exchanges.

The core of this project is a Python script that parses a human-readable YAML schema of the protocol. It uses a Jinja2 templating engine to automatically generate a complete, high-performance C++ library for encoding and decoding BOE messages.

This approach solves a critical problem in FinTech: it automates the creation of fast, accurate, and maintainable serialization code, eliminating the risk of manual error and dramatically speeding up development.

The Problem: Speed vs. Safety

In high-frequency trading, every nanosecond matters. Developers must manually write C++ code to serialize (encode) and deserialize (decode) complex, low-latency binary protocols. This manual process is:

Error-Prone: A single mistake in bit-shifting or byte alignment can lead to corrupt data and significant financial loss.

Time-Consuming: Manually coding for dozens of complex message types is a slow, tedious process.

Hard to Maintain: When the exchange updates the protocol, developers must painstakingly find and update every part of the codebase.

The Solution: A C++ "Factory"

This project builds a code generator that acts as a "factory" for C++ messaging code. The workflow is simple:

Define: A developer defines the entire protocol in a simple, human-readable YAML file (.yaml).

Generate: The Python script reads this YAML and uses Jinja2 templates to automatically generate all the necessary C++ headers (Encoder.h, Decoder.h, Messages.h).

Use: The generated C++ code is highly optimized, header-only, and can be directly included in a trading application for ultra-low-latency performance.

If the protocol changes, the developer only needs to update the YAML file and re-run the generator, saving days or weeks of work.

Technology Stack

Core Generator: Python 3

Templating Engine: Jinja2

Schema Definition: YAML

Generated Code: C++14 (or newer)

Domain: FinTech (High-Frequency Trading), Binary Protocols, Low-Latency Systems

Skills Demonstrated

Systems Architecture: Designing a robust, template-driven architecture for mission-critical applications.

Metaprogramming: Using Python and Jinja2 as a powerful code-generation engine to write high-performance C++, eliminating manual error.

Cross-Compiler C++: Generating C++ code that is compatible with both modern (C++17) and older (C++14) compilers by using techniques like std::enable_if.

FinTech Domain Knowledge: Demonstrates a deep understanding of the challenges in HFT, including binary serialization and the critical need for speed.

Automation & Tooling: Building a complete developer tool that automates a complex, error-prone manual task, dramatically improving the development workflow.

How to Run

Here is the complete guide to clone, generate, compile, and run the project.

1. Prerequisites

Before you begin, ensure you have the following tools installed and added to your system's PATH:

Git: For cloning the repository.

Python: (Version 3.6 or newer).

A C++14 Compiler: A G++ compiler (from MinGW-w64 or MSYS2 on Windows) that supports C++14. G++ 6.3.0 or newer is sufficient.

2. Clone the Repository

Open your terminal (PowerShell, cmd, or bash) and clone the project.

git clone [https://github.com/GuitarHero-28/cpp-code-generation-system.git](https://github.com/GuitarHero-28/cpp-code-generation-system.git)
cd cpp-code-generation-system


3. Install Python Dependencies

Install the required Python packages for the generator script.

# 'python' or 'python3' depending on your system
python -m pip install -r requirements.txt


4. Generate the C++ Codec

Run the Python generator script. This reads the c1_boe_2_11_68.yaml file and creates all the C++ header files.

# Note: We must use the config with underscores for the script to parse it
python ./generate_code.py --config c1_boe_2_11_68.yaml --create


5. Compile the C++ Test Program

Navigate into the newly generated directory and compile the test.cpp file.

# Navigate to the generated code
cd codecs/C1/BOE/2_11_68

# Compile the C++ test file
# The code is C++14 compatible, so G++ 6.3.0 will work.
# Use -o test.exe on Windows
g++ -O3 test.cpp -o test.exe

# On Linux or macOS, use:
# g++ -O3 test.cpp -o test.out


6. Run the Tests!

You can now run your compiled program. The test.cpp file is designed to read a message type and a payload file from the command line.

# Run the LoginRequest test
# (55 is the decimal for 0x37, the LoginRequest message type)
./test.exe 55 tests/LoginRequest.txt

# Run the NewOrderCross test
# (65 is the decimal for 0x41, the NewOrderCross message type)
./test.exe 65 tests/NewOrderCross.txt


What to Expect (Successful Output)

If everything works, you will see the full test results printed to your terminal, ending with:

...
========================================================================
INPUT PAYLOAD -> DECODER -> MSG OBJECT -> ENCODER -> ENCODED PAYLOAD
========================================================================
Original Hex Payload : BABA001D37000000000053303120544553545041535331323334353600
Encoded Hex Payload  : BABA001D37000000000053303120544553545041535331323334353600

Result: INPUT PAYLOAD == ENCODED PAYLOAD
========================================================================
