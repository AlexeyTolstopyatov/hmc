#include <iostream>
#include <bitset>
#include "core/Hamming.hpp"

/// Hamming Boolean vector parameters
/// contains arguments for Decoding/Encoding
/// procedures. If arguments count > 2 =>
/// better use arguments tuple or structure.
struct HammingVectorParameters {
    int iErrorPosition;
    bool bClearedPhrase;
    char* p_cVectorString;
};

void m_PrintHelpPage();
int m_DecodeRequiredVector(struct HammingVectorParameters* p_args);

int main(int argc, char ** argv) {
    // ./app --decode/encode <vector>
    if (argc < 5)
        m_PrintHelpPage();
    struct HammingVectorParameters args = {};

    int i = 1;
    while (i < argc) {
        if (argv[i] == "--esim") {
            clear = false;
            count = atoi(argv[i + 1]);
        }
        if (argv[i] == "--decode") {
            return m_DecodeRequiredVector(&args);
            break;
        }
        ++i;
    }

    return 0;
}
/// Calls Hamming class instance and procedures
/// for decoding current Boolean vector from string
/// \return Application halt status. (Control of application's behaviour)
int m_DecodeRequiredVector(struct HammingVectorParameters* p_args) {
    auto hammingInstance = new CHamming();

    std::vector<bool> booleanVector;
    booleanVector.emplace_back(p_args->p_cVectorString);

    if (!p_args->bClearedPhrase){
        booleanVector[p_args->iErrorPosition] =!booleanVector[p_args->iErrorPosition];
    }

    std::vector<bool> decoded =
            hammingInstance->GetDecodedVector(booleanVector, p_args->bClearedPhrase);
    hammingInstance->PrintVector(decoded);

    delete hammingInstance;
    return 0;
}

/// Prints help page in terminal
void m_PrintHelpPage() {
    std::cout
        << "Hamming code implementation"
        << "usage:" << std::endl
        << std::endl
        << "hmc --encode <phrase>" << std::endl
        << "hmc --esim <position> --decode <phrase>" << std::endl;

    std::cout << "\t--encode\tEncodes required phrase (next by key)" << std::endl;
    std::cout << "\t--decode\tDecodes required ohrase (next by key)."
        << "If key of error simulation disabled -> phrase means like cleared. (without errors)"
        << std::endl;
    std::cout << "\t--esim\tError simulation key (optional)." << std::endl;
}

void m_UseHammingAlgorithms() {
    CHamming encoder;
    std::vector<bool> data = {true, false, true, true};

    std::vector<bool> encoded = encoder.GetEncodedVector(data);
    std::cout << "Encoded:  ";
    encoder.PrintVector(encoded);

    // errors simulation
    encoded[3] = !encoded[3];
    std::cout << "With error:";
    encoder.PrintVector(encoded);

    bool errorCorrected;
    std::vector<bool> decoded = encoder.GetDecodedVector(encoded, errorCorrected);
    std::cout << "Decoded: ";
    encoder.PrintVector(decoded);
    std::cout << "Error corrected: " << std::boolalpha << errorCorrected << std::endl;
}