# AI Firmware Accessibility Agent (C++ / ECE Focus) 🌐⚡

An advanced C++ application that acts as an automated engineering inspector for embedded systems firmware. This project leverages the **Google Gemini API** to analyze microcontroller source code, optimizing it for safety, non-blocking execution, and interoperability with assistive hardware inputs (e.g., digital sip-and-puff switches, external braille displays, and interrupt-driven tactile buttons).

Designed to highlight the intersection of **Software Engineering (SWE)** and **Electrical & Computer Engineering (ECE)** for the Google Apprenticeship selection workflow.

---

## 🧠 ECE & Core Engineering Concepts Highlighted
- **Firmware Optimization**: Detects rigid polling loops (`delay()`) that cause high latency for assistive external peripherals.
- **Interrupt vs. Polling Architecture**: Assesses bare-metal registers and hardware interrupt service routines (ISRs) to ensure physical accessibility switches capture user inputs in real-time.
- **Embedded Safety**: References compliance rules like **MISRA C**, preventing system freezes or hardware lockouts.

---

## ✨ Features
- **Zero-Dependency Native Architecture**: Direct REST interactions implemented using native standard library constructs, bypassing bloated third-party framework abstraction layers.
- **Low-Latency Analysis**: Configured with strict internal temperature constraints (`0.1`) to prioritize exact, structured engineering formulas over abstract textual summaries.

---

## 🚀 Getting Started

### Prerequisites
- A C++17 compliant compiler (GCC, Clang, or MSVC)
- **OpenSSL** development libraries
- A Google Gemini API Key from [Google AI Studio](https://aistudio.google.com/)

### External Headers Setup
Download the two header files required for networking and data serialization into your project root directory:
```bash
curl -L [https://raw.githubusercontent.com/yhirose/cpp-httplib/master/httplib.h](https://raw.githubusercontent.com/yhirose/cpp-httplib/master/httplib.h) -o httplib.h
curl -L [https://github.com/nlohmann/json/releases/download/v3.11.3/json.hpp](https://github.com/nlohmann/json/releases/download/v3.11.3/json.hpp) -o nlohmann.json
