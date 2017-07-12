Arnold Lee
CS 340 Program #2

Read Me file

How to use:

1.) First, you will need to generate a pair of key file. Use the following command:

keygen 

it will prompt you for a pair of prime numbers, or you can tell the program to generate randomly for you.

the public key file will store in file name "pubkey", and private key in file name "prikey".

if you want to supply your prime numbers, use:

keygen prime1 prime2

if you want to randomly generate a pair of prime numbers, use:

keygen -c

if you want to supply file names for the output key files, use

keygen -o (public key file name) (private key file name)

you can also mix between the options above, like:

keygen -c -o f1 f2

that will generate a pair of prime numbers randomly, and the public key will store in file f1, private key in file f2.



2.) Once you have the public and private key files, you can go ahead and encode or decode your message.

use the following command:

endechar -e|-d -f message_file -k key_file -o output_file

use the -e option if you are inputing a plain text file as message, or the -d option to decode a garbled file into plain text.

if the -e or -d option is not chosen, it will automatically assume -e is chosen.

if no file name is entered for any one of the three files required, it will give you an error message and you will need to re-enter
the command. 

if no arguments are being given, it will prompt you for the file names required, along with encode/decode option selection.