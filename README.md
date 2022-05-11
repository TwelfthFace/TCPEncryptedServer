# TCPEncryptedServer
Intended to be a TCP **SECURE** communications server in order to interperate TCP traffic as commands to be ran on a Linux system. E.g. An app from a phone could be used to adjust volume, shutdown/sleep pc, turn off monitors, etc...

In essence, this is a bog standard TCP socket listener with middle layer encryption and decryption functionality, using openssl; a long winded way of not using CSR lol.

New private/public keys should be generated, if ***secure*** usage is intended, with `openssl genrsa -out private.pem 2048` to generate private key and `openssl rsa -in private.pem -pubout -out public.pem` to devise the public key.

### Dependencies
```
openssl-1.1.1
```

<h3>TODO</h3>
<li><s>Create functionality to encrypt/decrypt input.</s></li>
<li>Create TCP Socket for communications.</li>
<li>Enforce RSA Encryption to prevent eavesdropping.</li>
<li>Allow for pointing to pem files.</li>

<h3>Compile Instructions</h3>

```
git clone "..."
cd TCPEncryptedServer
make release
bin/Release/TCPEncryptedServer
```
