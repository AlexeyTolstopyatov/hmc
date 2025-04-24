#include <iostream>
#include <bitset>
#include <cstring>
#include "core/Hamming.hpp"

/// Hamming Boolean vector parameters
/// contains arguments for Decoding/Encoding
/// procedures. If arguments count > 2 =>
/// better use arguments tuple or structure.
struct HammingVectorParameters {
    int iErrorPosition;
    bool bHasError;
    char* pVector;
};

void m_PrintHelpPage();
int m_DecodeRequiredVector(struct HammingVectorParameters* pArgs);
int m_EncodeRequiredVector(char* strVector);

int main(int argc, char ** argv) {
    struct HammingVectorParameters args = {0};
    int i = 1;
    while (i < argc) {
        if (!strcmp(argv[i], "--encode") || !strcmp(argv[i], "-e")) {
            return m_EncodeRequiredVector(argv[i + 1]);
        }
        if (!strcmp(argv[i], "--error-position") || !strcmp(argv[i], "-err")) {
            args.bHasError = false;
            args.iErrorPosition = (atoi(argv[i + 1]) - 1);
        }
        if (!strcmp(argv[i], "--decode") || !strcmp(argv[i], "-d")) {
            return m_DecodeRequiredVector(&args);
        }
        ++i;
    }
    m_PrintHelpPage();
    return 0;
}
/// Calls Hamming class instance and procedures
/// for decoding current Boolean vector from string
/// \return Application's exit state.
int m_DecodeRequiredVector(struct HammingVectorParameters* pArgs) {
    auto pHamming = new CHamming();

    int iVectorSize = sizeof(pArgs->pVector);
    if (pArgs->iErrorPosition < 0 || pArgs->iErrorPosition > iVectorSize){
        delete pHamming;
        return 1;
    }

    std::vector<bool> vForDecoding;
    vForDecoding.emplace_back(pArgs->pVector);

    if (vForDecoding.empty()) {
        delete pHamming;
        return 1;
    }

    if (!pArgs->bHasError){
        vForDecoding[pArgs->iErrorPosition] =!vForDecoding[pArgs->iErrorPosition];
    }

    std::vector<bool> vDecoded =
            pHamming->GetDecodedVector(vForDecoding, pArgs->bHasError);
    pHamming->PrintVector(vDecoded);

    delete pHamming;
    return 0;
}

/// Calls Hamming class instance and procedures
/// for encoding current Boolean vector from string
/// \return Application's exit state.
int m_EncodeRequiredVector(char* strVector) {
    auto pHamming = new CHamming();
    std::vector<bool> vForEncoding;
    vForEncoding.emplace_back(strVector);

    if (vForEncoding.empty()) {
        delete pHamming;
        return 1;
    }

    std::vector<bool> vEncoded = pHamming->GetEncodedVector(vForEncoding);
    pHamming->PrintVector(vEncoded);

    delete pHamming;
    return 0;
}

/// Prints help page in terminal
void m_PrintHelpPage() {
    std::cout
        << "Hamming code implementation" << std::endl
        << "usage:" << std::endl
        << std::endl
        << "hmc --encode <phrase>" << std::endl
        << "hmc --error-position <position integer> --decode <phrase>" << std::endl;

    std::cout << "\t--encode\tEncodes required phrase (next by key)" << std::endl;
    std::cout << "\t--decode\tDecodes required ohrase (next by key)."
        << "If key of error simulation disabled -> phrase means like cleared. (without errors)"
        << std::endl;
    std::cout << "\t--error-position\tError simulation key (optional)." << std::endl;
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