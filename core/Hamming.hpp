//
// Created by MagicBook on 22.04.2025.
//

#ifndef HMC_HAMMING_HPP
#define HMC_HAMMING_HPP

#include <iostream>
#include <vector>

class CHamming {
private:
    bool m_IsPowerOf2(int n);
    int m_GetChecksumCount(int dataBits);
    std::vector<int> m_GetPositionsVector(int bits);

public:
    std::vector<bool> GetEncodedVector(const std::vector<bool>& data);
    std::vector<bool> GetDecodedVector(const std::vector<bool>& encoded, bool& errorCorrected);
    void PrintVector(const std::vector<bool>& bits);
};

#endif //HMC_HAMMING_HPP
