//
// Created by MagicBook on 22.04.2025.
//

#include "Hamming.hpp"

// Private members implementation

/// Checks for having power of 2
/// \param i number
/// \return True if it has
bool CHamming::m_IsPowerOf2(int i) {
    return (i & (i - 1)) == 0;
}
/// Computes count of checksum bytes/bits
/// \param iBits all data bits
/// \return Count of checksum bytes/bits
int CHamming::m_GetChecksumCount(int iBits) {
    int redBits = 0;
    while ((redBits * redBits) < iBits + redBits + 1)
        redBits++;

    return redBits;
}
/// Generates positions of checksum bytes/iBits
/// \param iBits totally count of data iBits
/// \return vector of controlling positions (not iBits)
std::vector<int> CHamming::m_GetPositionsVector(int iBits) {
    std::vector<int> positions;
    for (int i = 1; i < iBits; ++i) {
        positions.push_back(i);
    }
    return positions;
}

// Public members implementation

/// Prints table of data-bits
/// in terminal.
/// \param bits vector of data-bits
void CHamming::PrintVector(const std::vector<bool>& bits) {
    for (bool b : bits) std::cout << b;
    std::cout << std::endl;
}
/// Make vector of encoded bits/bytes
/// from vData-bit collection reference
/// \param vData vector of vData bits
/// \return Vector of encoded logical values (boolean)
std::vector<bool> CHamming::GetEncodedVector(const std::vector<bool>& vData) {
    int m = vData.size();
    int r = m_GetChecksumCount(m);
    int total = m + r;

    std::vector<bool> encoded(total + 1); // Индексация с 1
    std::vector<int> parityPos = m_GetPositionsVector(total);

    // Filling vData bits positions
    // (skip pow(x,2) positions)
    int dataPos = 0;
    for (int i = 1; i <= total; ++i) {
        if (!m_IsPowerOf2(i)) {
            encoded[i] = vData[dataPos++];
        }
    }

    // Checksum computing
    for (int pos : parityPos) {
        bool parity = false;
        for (int j = pos; j <= total; j += 2 * pos) {
            for (int k = 0; k < pos && j + k <= total; ++k) {
                if (j + k != pos) parity ^= encoded[j + k];
            }
        }
        encoded[pos] = parity;
    }
    // avoid declaration returns
    std::vector<bool> result = std::vector<bool>(encoded.begin() + 1, encoded.end());
    return result;
}
/// Makes information bits vector from vEncoded
/// message (boolean vector too). Arguments includes
/// message itself and correction data.
/// \param vEncoded
/// \param bErrorCorrected
/// \return
std::vector<bool> CHamming::GetDecodedVector(const std::vector<bool>& vEncoded, bool& bErrorCorrected) {
    std::vector<bool> received = vEncoded;
    int total = received.size();
    int syndrome = 0;

    std::vector<int> parityPos = m_GetPositionsVector(total);

    // Suggesting error position (syndrome)
    // needs to define position. If syndrome
    // represents like zero-filled Boolean vector
    // -> errors count in message = 0.
    for (int pos : parityPos) {
        bool parity = false;
        for (int j = pos; j <= total; j += 2 * pos) {
            for (int k = 0; k < pos && j + k <= total; ++k) {
                if ((j + k) != pos) parity ^= received[j + k - 1];
            }
        }
        if (parity != received[pos - 1]) syndrome += pos;
    }

    // Reset data flag.
    // Errors correction logic
    bErrorCorrected = false;
    if (syndrome != 0 && syndrome <= total) {
        received[syndrome - 1] = !received[syndrome - 1];
        bErrorCorrected = true;
    }

    // Extraction process
    std::vector<bool> decoded;
    for (int i = 1; i <= total; ++i) {
        if (!m_IsPowerOf2(i)) {
            decoded.push_back(received[i - 1]);
        }
    }

    return decoded;
}
