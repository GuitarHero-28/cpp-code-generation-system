// 1. FIXED: Changed hardcoded Linux paths to relative paths
#include "../../../../common/status.h"
#include "../../../../common/utils.h"

// 2. FIXED: Added missing include for your CustomHandler
#include "BOE_Handler.h"

// Original includes (correct)
#include "BOE_Msgs.h"
#include "BOE_Decoder.h"
#include "BOE_Encoder.h"
#include <chrono>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <cassert>
#include <sstream> // Needed for std::ostringstream
#include <algorithm> // Needed for std::remove

#pragma pack(1)

// 3. FIXED: Changed PRECISION to a valid chrono type
#define PRECISION microseconds

// Function to read hex payload from a file
std::vector<char> readHexPayloadFromFile(const std::string &filename)
{
    std::ifstream file(filename); // Open in text mode to read chars
    if (!file)
    {
        throw std::runtime_error("Error: Cannot open file " + filename);
    }

    // Read file content into a string first
    std::string hexString((std::istreambuf_iterator<char>(file)),
                           std::istreambuf_iterator<char>());
    
    // 4. ADDED: Strip newlines and spaces, which break hex conversion
    hexString.erase(std::remove(hexString.begin(), hexString.end(), '\n'), hexString.end());
    hexString.erase(std::remove(hexString.begin(), hexString.end(), '\r'), hexString.end());
    hexString.erase(std::remove(hexString.begin(), hexString.end(), ' '), hexString.end());

    // Return the cleaned vector of hex characters
    return std::vector<char>(hexString.begin(), hexString.end());
}

// Function to convert hex string to binary payload (Unused, but OK)
std::vector<char> convertHexToBinary(const std::string &hexPayload)
{
    if (hexPayload.size() % 2 != 0)
    {
        throw std::runtime_error("Error: Hex string length must be even.");
    }
    std::vector<char> payload(hexPayload.size() / 2);
    for (size_t i = 0; i < hexPayload.size(); i += 2)
    {
        payload[i / 2] = static_cast<char>(hexPairToByte(hexPayload[i], hexPayload[i + 1]));
    }
    return payload;
}

// Function to convert binary data to hex string
std::string convertBinaryToHex(std::vector<char> buffer, size_t size)
{
    std::ostringstream oss;
    for (size_t i = 0; i < size; ++i)
    {
        oss << std::uppercase << std::setw(2) << std::setfill('0') << std::hex << static_cast<int>(static_cast<unsigned char>(buffer[i]));
    }
    return oss.str();
}

// Function to decode and then re-encode payload
std::string processPayload(const std::vector<char> &hexPayload, Status &status, int message_type)
{
    Decoder<CustomHandler> decoder;
    Encoder<CustomHandler> encoder;

    auto startTime = std::chrono::high_resolution_clock::now();
    // Decode the binary payload
    decoder.decode(hexPayload, status);
    // End time
    auto endTime = std::chrono::high_resolution_clock::now();
    // Calculate duration in PRECISION
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
    // Output the time taken in PRECISION
    std::cout << "Time taken by Decoder: " << std::dec << duration.count() << " microseconds" << std::endl;

    // Reset status and prepare for encoding
    status.reset();
    std::vector<char> buffer(hexPayload.size() / 2);

    // Retrieve decoded message object and encode it back to buffer
    status.updateNextStart(const_cast<char *>(buffer.data()));

    if (message_type == MessagesEnum::LOGINREQUEST)
    {
        std::cout << "Encoding LoginRequest Message Object\n";
        startTime = std::chrono::high_resolution_clock::now();
        encoder.encode(buffer, decoder.getLoginRequest(), status);
        endTime = std::chrono::high_resolution_clock::now();
    }
    else if (message_type == MessagesEnum::NEWORDERCROSS)
    {
        std::cout << "Encoding NewCrossOrder Message Object\n";
        startTime = std::chrono::high_resolution_clock::now();
        encoder.encode(buffer, decoder.getNewOrderCross(), status);
        endTime = std::chrono::high_resolution_clock::now();
    }
    duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
    std::cout << "Time taken by Encoder: " << duration.count() << " microseconds" << std::endl;

    return convertBinaryToHex(buffer, buffer.size());
}

// Function to compare hex strings and report differences
void compareHexStrings(const std::string &original, const std::string &encoded)
{
    std::cout << "========================================================================" << std::endl;
    std::cout << "INPUT PAYLOAD -> DECODER -> MSG OBJECT -> ENCODER -> ENCODED PAYLOAD" << std::endl;
    std::cout << "========================================================================" << std::endl;

    std::cout << "Original Hex Payload : " << original << std::endl;
    std::cout << "Encoded Hex Payload  : " << encoded << std::endl;

    if (original == encoded)
    {
        std::cout << "\nResult: INPUT PAYLOAD == ENCODED PAYLOAD" << std::endl;
    }
    else
    {
        std::cout << "\nResult: INPUT PAYLOAD != ENCODED PAYLOAD" << std::endl;
    }
    std::cout << "========================================================================" << std::endl;
}

// Main function
int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        std::cerr << "Usage: " << argv[0] << " <message_type>" << " <filename>" << std::endl;
        return 1;
    }
    // Step 1: Read hex payload from file
    std::vector<char> hexPayload = readHexPayloadFromFile(argv[2]);
    // Step 3: Process payload through decode and encode steps
    Status status;
    std::string encodedPayload = processPayload(hexPayload, status, atoi(argv[1]));
    // Step 4: Compare original and encoded payloads
    compareHexStrings(std::string(hexPayload.begin(), hexPayload.end()), encodedPayload);
    return 0;
}