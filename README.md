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
<li><s>Create TCP Socket for communications.</s></li>
<li><s>Enforce RSA Encryption to prevent eavesdropping.</s></li>
<li>Allow for pointing to pem files.</li>
<li>Create client counter part.</li>

<h3>Compile Instructions</h3>

```
git clone "..."
cd TCPEncryptedServer
make release
bin/Release/TCPEncryptedServer
```
### Bugs
<li>When decrypting base64 sometimes random text will be dumped into the terminal. Possible unsafe read.</li>



### Netcat Test

```
netcat 127.0.0.1 54000
J4tmiTnsumVsIjjNLHQDRi/gsrAoJoa98WbT96TEB1kE6yqAvALlf4dwRnbJIRpkPbS5dU2mQMwei5bl0syCYIxIjXhw8UkMxIavKZT4/NPV7ETSBv0yPatMQyDrLVFX5sl8XmvKGM1LBmRdk+VsF89BDWpoQvIjfcQMhdMEVSxMtiVabS7HS7GZXdcRadPDMtq8/EAsGn7RQBRwGFOUJAJlc4P5cm9yO5kE0nu0cGprpVgwpnUylkwR2nrn2qv19dKKZZmnMcWYdK+KKjXGZ5DC00iVZbr+hl9DSl+d5yZAU4M6Cgam63yiG3pEDesFnn90MbU12nmkZCzOCzGU4w==
```
