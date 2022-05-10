#pragma once
#include <cryptopp/eccrypto.h>
#include <cryptopp/sha3.h>
#include <string>

namespace ECDSA {
namespace Sign {
using std::string;
using ECDSA = CryptoPP::ECDSA<CryptoPP::ECP, CryptoPP::SHA3_512>;

ECDSA::PrivateKey genKey();

string Sign(string messageFilePath, string privateKeyFilePath = "");

void LoadMessageFromFile(string filePath, string &message);
void WritePrivateKeyToFile(ECDSA::PrivateKey key, string filePath);
void WritePublicKeyToFile(ECDSA::PublicKey key, string filePath);

void LoadPrivateKeyFromFile(string filePath, ECDSA::PrivateKey &privateKey);

} // namespace Sign
} // namespace ECDSA
