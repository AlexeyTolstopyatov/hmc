#include <iostream>
#include "core/Hamming.hpp"

void m_PrintHelpPage();

int main(int argc, char ** argv) {
    // ./app --decode/encode <vector> --3c <checkcum chars count>
    if (argc < 5)
        m_PrintHelpPage();
    int count = 0;
    // find CCC
    int i = 1;
    while (i < argc) {
        if (argv[i] == "--3c") {
            count = atoi(argv[i+1]);
            break;
        }
        ++i;
    }

    return 0;
}
/// Prints help page in terminal
void m_PrintHelpPage() {
    std::cout
        << "Hamming code implementation"
        << "usage:" << std::endl
        << std::endl
        << "hmc --3c <checksum chars count (u32)> --to <phrase>" << std::endl
        << "hmc --3c <checksum chars count (u32)> --from <phrase>" << std::endl;
}

void m_UseHammingAlgorithms() {
    CHamming encoder;
    std::vector<bool> data = {1, 0, 1, 1};

    std::vector<bool> encoded = encoder.GetEncodedVector(data);
    std::cout << "Encoded:  ";
    encoder.PrintVector(encoded);

    // errors simulation
    encoded[3] = !encoded[3];
    std::cout << "With error:";
    encoder.PrintVector(encoded);

    bool errorCorrected;
    std::vector<bool> decoded = encoder.GetDecodedVector(encoded, errorCorrected);
    std::cout << "Decoded:   ";
    encoder.PrintVector(decoded);
    std::cout << "Error corrected: " << std::boolalpha << errorCorrected << std::endl;
}