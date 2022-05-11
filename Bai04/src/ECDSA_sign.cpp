#include "../include/ECDSA_sign.hpp"
#include "../include/Misc.hpp"

#include <cryptopp/config_int.h>
#include <cryptopp/eccrypto.h>
#include <cryptopp/files.h>
#include <cryptopp/filters.h>
#include <cryptopp/oids.h>
#include <cryptopp/osrng.h>

#include <cryptopp/queue.h>

namespace ECDSA {
namespace Sign {

using CryptoPP::AutoSeededRandomPool;
using CryptoPP::byte;
using CryptoPP::ByteQueue;
using CryptoPP::FileSource;
using CryptoPP::SignerFilter;
using CryptoPP::StringSink;
using CryptoPP::StringSource;

ECDSA::PrivateKey genKey() {
  AutoSeededRandomPool rng;
  ECDSA::PrivateKey privateKey;
  privateKey.Initialize(rng, CryptoPP::ASN1::secp256k1());
  bool result = privateKey.Validate(rng, 3);
  if (!result) {
    throw std::runtime_error("Invalid private key");
  }

  return privateKey;
}

string Sign(string messageFilePath, string privateKeyFilePath) {
  AutoSeededRandomPool rng;
  ECDSA::PrivateKey privateKey;

  if (privateKeyFilePath.empty())
    privateKey = genKey();
  else
    LoadPrivateKeyFromFile(privateKeyFilePath, privateKey);

  ECDSA::Signer signer(privateKey);
  ECDSA::PublicKey publickey;
  signer.AccessKey().MakePublicKey(publickey);
  CryptoPP::byte *pub;

  string message;
  LoadMessageFromFile(messageFilePath, message);

  string signature;

  StringSource ss(message, true,
                  new SignerFilter(rng, signer, new StringSink(signature)));

  if (!privateKeyFilePath.empty())
    WritePrivateKeyToFile(privateKey, "priv.pem");
  WritePublicKeyToFile(publickey, "pub.pem");
  Misc::SaveSignatureToFile("signature.bin", signature);
  return signature;
}

void WritePublicKeyToFile(ECDSA::PublicKey key, string filePath) {
  ByteQueue queue;
  key.Save(queue);

  Misc::Save(filePath, queue);
}

void WritePrivateKeyToFile(ECDSA::PrivateKey key, string filePath) {
  ByteQueue queue;
  key.Save(queue);

  Misc::Save(filePath, queue);
}

void LoadMessageFromFile(string filePath, string &message) {
  FileSource(filePath.c_str(), true, new StringSink(message));
}

void LoadPrivateKeyFromFile(string filePath, ECDSA::PrivateKey &privateKey) {
  ByteQueue queue;
  AutoSeededRandomPool rng;

  Misc::Load(filePath, queue);
  privateKey.Load(queue);
  if (privateKey.Validate(rng, 3) == false) {
    throw std::runtime_error("Invalid private key");
  }
}

} // namespace Sign
} // namespace ECDSA