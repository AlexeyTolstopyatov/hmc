//
// Created by MagicBook on 22.04.2025.
//

#include "Hamming.hpp"

// Private members implementation

/// Checks for having power of 2
/// \param n number
/// \return True if it has
bool CHamming::m_IsPowerOf2(int n) {
    return (n & (n - 1)) == 0;
}
/// Computes count of checksum bytes/bits
/// \param dataBits all data bits
/// \return Count of checksum bytes/bits
int CHamming::m_GetChecksumCount(int dataBits) {
    int redBits = 0;
    while ((redBits * redBits) < dataBits + redBits + 1)
        redBits++;

    return redBits;
}
/// Generates positions of checksum bytes/bits
/// \param bits totally count of data bits
/// \return vector of controlling positions (not bits)
std::vector<int> CHamming::m_GetPositionsVector(int bits) {
    std::vector<int> positions;
    for (int i = 1; i < bits; ++i) {
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
/// from data-bit collection reference
/// \param data vector of data bits
/// \return Vector of encoded logical values (boolean)
std::vector<bool> CHamming::GetEncodedVector(const std::vector<bool>& data) {
    int m = data.size();
    int r = m_GetChecksumCount(m);
    int total = m + r;

    std::vector<bool> encoded(total + 1); // Индексация с 1
    std::vector<int> parityPos = m_GetPositionsVector(total);

    // Filling data bits positions
    // (skip pow(x,2) positions)
    int dataPos = 0;
    for (int i = 1; i <= total; ++i) {
        if (!m_IsPowerOf2(i)) {
            encoded[i] = data[dataPos++];
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
/// Makes information bits vector from encoded
/// message (boolean vector too). Arguments includes
/// message itself and correction data.
/// \param encoded
/// \param errorCorrected
/// \return
std::vector<bool> CHamming::GetDecodedVector(const std::vector<bool>& encoded, bool& errorCorrected) {
    std::vector<bool> received = encoded;
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

    // Errors correction logic
    errorCorrected = false;
    if (syndrome != 0 && syndrome <= total) {
        received[syndrome - 1] = !received[syndrome - 1];
        errorCorrected = true;
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
