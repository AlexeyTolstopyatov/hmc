//
// Created by MagicBook on 22.04.2025.
//

#ifndef HMC_HAMMING_HPP
#define HMC_HAMMING_HPP

#include "Framework.hpp"

class CHamming {
private:
    bool m_IsPowerOf2(int i);
    int m_GetChecksumCount(int iBits);
    std::vector<int> m_GetPositionsVector(int iBits);

public:
    std::vector<bool> GetEncodedVector(const std::vector<bool>& vData);
    std::vector<bool> GetDecodedVector(const std::vector<bool>& vEncoded, bool& bErrorCorrected);
    void PrintVector(const std::vector<bool>& bits);
};

#endif //HMC_HAMMING_HPP
