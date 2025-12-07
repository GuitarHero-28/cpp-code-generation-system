# 🚀 High-Performance C++ Code Generator for Binary Financial Protocols: A Complete Guide

> **Note:** This README was generated with the help of AI — please don't judge me for that 😄

## 💡 Project Overview

This project is a mission-critical **low-latency C++ code generator** designed for binary financial protocols, such as the **Binary Order Entry (BOE)** system used in High-Frequency Trading (HFT) and financial exchanges.

At its core, a **Python script** reads a human-readable **YAML schema** of the protocol and uses the **Jinja2 templating engine** to automatically generate an optimized, header-only C++ library for encoding and decoding BOE messages.

This eliminates manual coding errors, accelerates development, and ensures consistent, high-performance serialization.

---

## ❓ The Problem: Speed vs. Safety

In HFT environments where microseconds matter, manual C++ serialization becomes a liability:

- **Error-Prone:** A single wrong bit-shift corrupts a financial message.
- **Slow to Develop:** Writing encoders/decoders for dozens of message types is tedious.
- **Hard to Maintain:** Protocol upgrades require repeated, error-prone manual updates.

---

## ✅ The Solution: A C++ "Factory"

This project builds a **code generator** that acts like a “factory" for producing C++ message types:

1. **Define** the protocol in YAML.  
2. **Generate** optimized header-only C++ code using Python + Jinja2.  
3. **Use** the generated encoders/decoders directly in trading engines.

A protocol update = update YAML → regenerate → done.

---

## 🛠️ Technology Stack

| Component | Technology | Role |
|----------|------------|------|
| **Generator** | Python 3 | Reads schema and outputs C++ |
| **Templates** | Jinja2 | Converts definitions into real C++ code |
| **Schema** | YAML | Source-of-truth for the entire protocol |
| **Output** | C++14/17 | Header-only, ultra-low-latency codecs |
| **Domain** | HFT / FinTech | Binary serialization under extreme performance constraints |

---

## 🌟 Key Demonstrated Skills

This project highlights:

- System architecture for protocol-driven code generation  
- Metaprogramming and automation using Jinja2  
- Advanced binary serialization concepts  
- C++14/17 compiler-level optimization  
- Real-world FinTech protocol engineering  
- Developer tooling design  

---

## ⚙️ Getting Started (Windows-Focused Guide)

### 1️⃣ Install Prerequisites

- Git  
- Python 3.6+  
- G++ 6.3.0+ or MSYS2/MinGW C++14 compiler  

---

### 2️⃣ Clone the Repository

```powershell
git clone https://github.com/GuitarHero-28/cpp-code-generation-system.git
cd cpp-code-generation-system
```

---

### 3️⃣ Install Python Dependencies

```powershell
python -m pip install -r requirements.txt
```

---

### 4️⃣ Generate the C++ Codec

```powershell
python ./generate_code.py --config c1_boe_2_11_68.yaml --create
```

This reads the YAML and generates the full codec under:

```
codecs/C1/BOE/2_11_68/
```

---

### 5️⃣ Compile the Test Program

```powershell
cd codecs/C1/BOE/2_11_68
g++ -O3 test.cpp -o test.exe
```

---

### 6️⃣ Run the Tests

Each test requires:

```
./test.exe <message_type_decimal> <payload_file>
```

Example: LoginRequest (55 = 0x37)

```powershell
./test.exe 55 tests/LoginRequest.txt
```

Example: NewOrderCross (65 = 0x41)

```powershell
./test.exe 65 tests/NewCrossOrder.txt
```

---

## ✔️ Expected Output (Correct Run)

You should see:

```
# INPUT PAYLOAD -> DECODER -> MSG OBJECT -> ENCODER -> ENCODED PAYLOAD

Original Hex Payload : BABA3D00370000000000303030315445535454455354494E47000000030F00800102014ABB0100020000000008008125030041050B00812C06004107004000  
Encoded  Hex Payload : BABA3D00370000000000303030315445535454455354494E47000000030F00800102014ABB0100020000000008008125030041050B00812C06004107004000

# Result: INPUT PAYLOAD == ENCODED PAYLOAD
```

If both payloads match, your generated encoder/decoder is functioning correctly.

---

## 🎉 Final Notes

This project demonstrates how modern tooling (Python + Jinja2) and system-level C++ can be combined to build **high-speed, future-proof, automatically generated binary protocol handlers**.

It can be extended to:

- FIX / ITCH / OUCH style protocols  
- Multi-exchange HFT infrastructure  
- Larger message suites  
- Cross-language serialization systems  

A scalable foundation for real-world high-performance FinTech engineering.
