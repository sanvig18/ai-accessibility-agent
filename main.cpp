#include <iostream>
#include <string>
#include <cstdlib>

#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "httplib.h"
#include "nlohmann/json.hpp"

using json = nlohmann::json;

std::string auditFirmwareAccessibility(const std::string& firmwareCode, const std::string& apiKey) {
    httplib::Client cli("https://generativelanguage.googleapis.com");
    cli.enable_server_certificate_verification(true);

    std::string path = "/v1beta/models/gemini-2.5-flash:generateContent?key=" + apiKey;

    std::string systemInstruction = 
        "You are an expert Firmware and Assistive Technology Engineer at Google. Your job is to analyze "
        "low-level microcontroller or embedded systems C/C++ code to ensure it complies with assistive hardware standards "
        "and embedded safety guidelines (e.g., MISRA C, non-blocking asynchronous loops for hardware switches). "
        "Identify blocking bottlenecks, missing interrupts for accessible interfaces, and output optimized, safe firmware.";

    std::string prompt = 
        "Perform a thorough embedded systems and hardware accessibility audit on this firmware snippet. "
        "Structure your response with:\n"
        "1. Hardware Bottleneck / Safety Violation\n"
        "2. Impact on Assistive Interfaces (e.g., switches, braille displays, sip-and-puff inputs)\n"
        "3. Optimized, Non-Blocking, Hardware-Safe C++ Code\n\n"
        "Target Code:\n" + firmwareCode;

    json requestBody = {
        {"contents", {{
            {"parts", {{
                {"text", prompt}
            }}}
        }}},
        {"systemInstruction", {
            {"parts", {{
                {"text", systemInstruction}
            }}}
        }},
        {"generationConfig", {
            {"temperature", 0.1}
        }}
    };

    auto res = cli.Post(path.c_str(), requestBody.dump(), "application/json");

    if (res && res->status == 200) {
        try {
            auto jsonResponse = json::parse(res->body);
            return jsonResponse["candidates"][0]["content"]["parts"][0]["text"].get<std::string>();
        } catch (...) {
            return "Error parsing response JSON.";
        }
    } else {
        return "HTTP Request Failed. Status: " + (res ? std::to_string(res->status) : "Unknown Error");
    }
}

int main() {
    const char* apiKeyEnv = std::getenv("GEMINI_API_KEY");
    if (!apiKeyEnv) {
        std::cerr << "Error: GEMINI_API_KEY environment variable not set." << std::endl;
        return 1;
    }
    std::string apiKey(apiKeyEnv);

    std::string sampleBadFirmware = 
        "// Poor ECE design: Blocking loop ignores emergency assistive hardware override inputs\n"
        "void readSensors() {\n"
        "    while(true) {\n"
        "        long data = readAdcChannel(0);\n"
        "        delay(5000); // 5-second complete hardware block\n"
        "        if (digitalRead(ASSISTIVE_SWITCH_PIN) == HIGH) {\n"
        "            triggerAction();\n"
        "        }\n"
        "    }\n"
        "}";

    std::cout << "[ECE Agent]: Analyzing hardware firmware and interrupt layers via Gemini..." << std::endl;
    std::string report = auditFirmwareAccessibility(sampleBadFirmware, apiKey);

    std::cout << "\n=== GENERATED EMBEDDED SYSTEM AUDIT REPORT ===\n" << std::endl;
    std::cout << report << std::endl;

    return 0;
}
