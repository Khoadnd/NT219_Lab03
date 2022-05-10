#include "../include/Misc.hpp"

#include <cryptopp/files.h>
#include <cryptopp/filters.h>
#include <cryptopp/hex.h>

namespace ECDSA {
namespace Misc {

using CryptoPP::ByteQueue;
using CryptoPP::FileSink;
using CryptoPP::FileSource;
using CryptoPP::HexEncoder;
using CryptoPP::StringSink;
using CryptoPP::StringSource;

string PrettyPrint(string text) {
  string encoded = "";
  encoded.clear();
  StringSource ss(text, true, new HexEncoder(new StringSink(encoded)));
  return encoded;
}

string PrettyPrint(CryptoPP::byte arr[], int arraySize) {
  string encoded = "";
  encoded.clear();
  StringSource ss(arr, arraySize, true,
                  new HexEncoder(new StringSink(encoded)));
  return encoded;
}

void Save(string filePath, const CryptoPP::BufferedTransformation &bt) {
  FileSink file(filePath.c_str());

  bt.CopyTo(file);
  file.MessageEnd();
}

void Load(string filePath, CryptoPP::BufferedTransformation &bt) {
  FileSource file(filePath.c_str(), true);

  file.TransferTo(bt);
  bt.MessageEnd();
}

void SaveSignatureToFile(string filePath, string signature) {
  ByteQueue queue;
  queue.Put((byte *)&signature[0], signature.size());
  Misc::Save(filePath, queue);
}

void LoadSignatureFromFile(string filePath, string &signature) {
  FileSource(filePath.c_str(), true, new StringSink(signature));
}

} // namespace Misc
} // namespace ECDSA