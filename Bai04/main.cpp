#include "include/ECDSA_sign.hpp"
#include "include/ECDSA_verify.hpp"
#include "include/Misc.hpp"

#include <cstring>
#include <iostream>
#include <string>

int main(int argc, char **argv) {
  std::cout << "using curve secp256k1\n";

  // usage: ./main <messagePath> <privateKeyPath> sign
  // usage: ./main <messagePath> <signatureFilePath> <publicKeyPath> verify

  if (argc == 1) {
    ECDSA::Sign::Sign("message.txt", "priv.pem");

    std::cout << "verifying signature\n";
    std::string message, signature;
    ECDSA::Sign::LoadMessageFromFile("message.txt", message);
    ECDSA::Misc::LoadSignatureFromFile("signature.bin", signature);

    std::cout << (ECDSA::Verify::Verify(message, signature, "pub.pem")
                      ? "True"
                      : "False");
    return 0;
  }

  if (argc == 4) {
    if (strcmp(argv[3], "sign") == 0) {
      // messasge, private key
      ECDSA::Sign::Sign(argv[1], argv[2]);
    }
    return 0;
  }
  if (argc == 5) {
    if (strcmp(argv[4], "verify") == 0) {
      // message, signature, public key
      std::string message;
      std::string signature;
      ECDSA::Misc::LoadSignatureFromFile(argv[2], signature);
      ECDSA::Sign::LoadMessageFromFile(argv[1], message);
      std::cout << (ECDSA::Verify::Verify(message, signature, argv[3])
                        ? "True"
                        : "False");
    }
    return 0;
  }
  std::cout << "??";

  return 0;
}