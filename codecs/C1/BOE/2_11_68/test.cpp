// 1. Correct relative paths
#include "../../../../common/status.h"
#include "../../../../common/utils.h"

// 2. Include the handler
#include "BOE_Handler.h"

// Original includes
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
#include <sstream> 
#include <algorithm> 

#pragma pack(1)

#define PRECISION microseconds

// Function to read hex payload from a file
std::vector<char> readHexPayloadFromFile(const std::string &filename)
{
    std::ifstream file(filename); // Open in text mode
    if (!file)
    {
        // This is the error that is causing the silent crash
        throw std::runtime_error("Error: Cannot open file " + filename);
    }

    std::string hexString((std::istreambuf_iterator<char>(file)),
                           std::istreambuf_iterator<char>());
    
    // Strip whitespace
    hexString.erase(std::remove(hexString.begin(), hexString.end(), '\n'), hexString.end());
    hexString.erase(std::remove(hexString.begin(), hexString.end(), '\r'), hexString.end());
    hexString.erase(std::remove(hexString.begin(), hexString.end(), ' '), hexString.end());

    // NEW: Add a check for even length
    if (hexString.size() % 2 != 0)
    {
        throw std::runtime_error("Error: Payload file has an odd number of hex characters.");
    }

    return std::vector<char>(hexString.begin(), hexString.end());
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
    decoder.decode(hexPayload, status);
    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
    std::cout << "Time taken by Decoder: " << std::dec << duration.count() << " microseconds" << std::endl;

    status.reset();
    std::vector<char> buffer(hexPayload.size() / 2);

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

// Function to compare hex strings
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

    // *** THIS IS THE NEW, SAFER CODE ***
    try
    {
        // Step 1: Read hex payload from file
        std::vector<char> hexPayload = readHexPayloadFromFile(argv[2]);
        
        // Step 2: Process payload
        Status status;
        std::string encodedPayload = processPayload(hexPayload, status, atoi(argv[1]));
        
        // Step 3: Compare
        compareHexStrings(std::string(hexPayload.begin(), hexPayload.end()), encodedPayload);
    }
    catch (const std::runtime_error& e)
    {
        // This will CATCH the crash and print a friendly message
        std::cerr << "A critical error occurred: " << e.what() << std::endl;
        return 1;
    }
    // *** END OF NEW CODE ***

    return 0;
}
