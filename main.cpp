#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>

std::string getOutputFileName(const std::string& inputFile) {
    // Find the last dot in the filename to replace the extension
    size_t lastDot = inputFile.find_last_of(".");
    std::string outputFile = inputFile;

    if (lastDot != std::string::npos) {
        outputFile = outputFile.substr(0, lastDot) + ".txt"; // Replace extension with "_output.txt"
    }
    else {
        outputFile += "_output.txt"; // Append if no extension
    }

    return outputFile;
}

void convertToHex(const std::string& inputFile) {
    std::ifstream inFile(inputFile, std::ios::binary);
    if (!inFile) {
        std::cerr << "Error opening input file: " << inputFile << std::endl;
        return;
    }

    // Read the entire file into a vector
    std::vector<unsigned char> buffer((std::istreambuf_iterator<char>(inFile)),
        std::istreambuf_iterator<char>());
    inFile.close();

    // Generate output file name
    std::string outputFile = getOutputFileName(inputFile);

    std::ofstream outFile(outputFile);
    if (!outFile) {
        std::cerr << "Error opening output file: " << outputFile << std::endl;
        return;
    }

    // Write the output as an array of hex values
    outFile << "unsigned char hexArray[] = { ";
    for (size_t i = 0; i < buffer.size(); ++i) {
        outFile << "0x" << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(buffer[i]);
        if (i < buffer.size() - 1) {
            outFile << ", ";
        }
    }
    outFile << " };" << std::endl;

    outFile.close();
    std::cout << "Conversion complete! Check " << outputFile << std::endl;
}

int main() {
    std::string inputFile;

    std::cout << "Enter the path of the input TIM file: ";
    std::getline(std::cin, inputFile);

    convertToHex(inputFile);

    return 0;
}
