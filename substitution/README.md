TITLE: Substitution

USAGE: $ ./substitution VCHPRZGJNTLSKFBDQWAXEUYMOI

  plaintext:  hello, world
  
  ciphertext: jrssb, ybwsp
  
This program produces a substitution cipher, were it “encrypts” (i.e., conceals in a reversible way) a message by replacing every letter with another letter.
To do so, it uses a key: in this case, a mapping of each of the letters of the alphabet to the letter it should correspond to when it's encrypted. 
To “decrypt” the message, the receiver of the message would need to know the key, 
so that they can reverse the process: translating the encrypt text (generally called ciphertext) back into the original message (generally called plaintext).
