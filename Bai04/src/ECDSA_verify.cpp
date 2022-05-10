#include "../include/ECDSA_verify.hpp"
#include "../include/Misc.hpp"

#include <cryptopp/files.h>
#include <cryptopp/filters.h>

namespace ECDSA {
namespace Verify {

using CryptoPP::ArraySink;
using CryptoPP::byte;
using CryptoPP::ByteQueue;
using CryptoPP::FileSource;
using CryptoPP::SignatureVerificationFilter;
using CryptoPP::StringSink;
using CryptoPP::StringSource;

bool Verify(string message, string signature, string publicKeyFilePath) {
  bool result;

  ECDSA::PublicKey publicKey;
  LoadPublicKey(publicKeyFilePath, publicKey);
  ECDSA::Verifier verifier(publicKey);

  StringSource ss(
      signature + message, true,
      new SignatureVerificationFilter(
          verifier, new ArraySink((byte *)&result, sizeof(result))));
  return result;
}

void LoadPublicKey(string filePath, ECDSA::PublicKey &publicKey) {
  ByteQueue queue;
  Misc::Load(filePath, queue);

  publicKey.Load(queue);
}

void Load(string filePath, CryptoPP::BufferedTransformation &bt) {
  FileSource file(filePath.c_str(), true);

  file.TransferTo(bt);
  bt.MessageEnd();
}

} // namespace Verify
} // namespace ECDSA