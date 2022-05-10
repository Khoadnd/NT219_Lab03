#pragma once

#include <cryptopp/eccrypto.h>
#include <string>

namespace ECDSA {
namespace Misc {

using std::string;
using byte = unsigned char;

string PrettyPrint(string text);
string PrettyPrint(byte arr[], int arraySize);
void Load(string filePath, CryptoPP::BufferedTransformation &bt);
void Save(string filePath, const CryptoPP::BufferedTransformation &bt);

void SaveSignatureToFile(string filePath, string signature);
void LoadSignatureFromFile(string filePath, string &signature);
} // namespace Misc
} // namespace ECDSA