# Attacks-on-RSA

## Problem Statement : 
### Demonstrate and Implement 3 attacks on RSA CryptoSystem in C++. 
 	1.Factorization of Public Key (n) 
 	2.Low Encryption Exponent Attack 
 	3.Chosen Ciphertext Attack

## Solution Plan : 

## Factorization Attack:
The strength of RSA lies on the fact that it is difficult to factorize a large composite integer. RSA's public key consists of the modulus n (n is the product of two large primes) and the encryption exponent e. The private key is the decryption exponent d such that e * d = 1 mod φ(n).<br>
1. Iterative algorithm up to root n to find a factor and obtain the other by dividing it with n.<br>
2. Since n is composed of primes and all primes are odd except 2, we optimized the algorithm 1 to odd primes.<br>
3. Pollard Rho Algorithm, a prime factorization algorithm, particularly fast for a large composite number with small prime factors.<br>

Once we have factored n, p and q values can be found. From p and q,  φ(n) can be found as  φ(n) = (p-1)*(q-1).
This helps Eve to find the decryption exponent d, since it is the inverse of e with respect to φ(n) i.e by using the Extended Euclidean algorithm. Knowing d and n(public key), Eve can easily decrypt the ciphertext to know the original message.
In order to prevent this attack, N must be at least 1024 bits.
		


	
## Low Encryption Exponent Attack:

Alice sends the same message (m) to three different persons with different n values (say n1, n2, n3 which are pairwise coprime) but with a same low public exponent (e) usually 3. Using Chinese Remainder Theorem (C.R.T), we can find the original message without knowing the private keys. <br>
C1 = m<sup>3</sup> mod n1 <br>
C2 = m<sup>3</sup> mod n2 <br>
C3 = m<sup>3</sup> mod n3 <br>
C= C1.n2.n3.((n2.n3)<sup>-1</sup> mod n1) + C2.n3.n1.((n3.n1)<sup>-1</sup> mod n2) + C3.n1.n2.((n1.n2)<sup>-1</sup> mod n3)
cube root of C gives the original message m.



## Chosen Cipher Text Attack

Alice sends a message to Bob encrypted with Bob’s public key (c= m<sup>e</sup> mod n).<br>
Eve is a malicious person who chooses a ciphertext c. Eve encrypts c using a random constant r and sends the new encrypted message c’ to Bob (c’= c x r<sup>e</sup> mod n).<br>
Bob receives the message and tries to decrypt it but, fails to get the message. He sends the decrypted message (c’<sup>d</sup> mod n) to Alice stating that he did not understand it. Eve intervenes and decrypts it by the following computation.<br>
c’<sup>d</sup> mod n = (c x r<sup>e</sup> mod n) <sup>d</sup> mod n = (m.r)<sup>e.d</sup> mod n = m.r mod n <br>
Eve finds the multiplicative inverse of r, multiplies it with m.r mod n and gets the original message m sent by Alice.






