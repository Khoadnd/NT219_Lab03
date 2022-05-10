#pragma once

#include <cryptopp/eccrypto.h>
#include <cryptopp/sha3.h>
#include <string>

namespace ECDSA {
namespace Verify {

using std::string;
using ECDSA = CryptoPP::ECDSA<CryptoPP::ECP, CryptoPP::SHA3_512>;

bool Verify(string message, string signature, string publicKeyFilePath);
void LoadPublicKey(string filePath, ECDSA::PublicKey &publicKey);

} // namespace Verify
} // namespace ECDSA