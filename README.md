base64
======

A base64, 32 and 16 encoder and decoder

This is a rewrite of a piece of code I wrote about 6 years ago and was lying in a Subversion repository on my drive. I was just going to push the original code as-is but I decided to tidy it up slightly and once I got a clean spot I had to keep scrubbing.

Once done I have pushed it here.  To see how good mine is (or isn't) I added a drag race between mine and the first result off google.

This is what the results are on my particular system encoding 16 million bytes.

RenÚ Nyffenegger encode elapsed time: 0.241018s
Graham Reeds encode elapsed time: 0.529976s
The encoded files are the same
RenÚ Nyffenegger decode elapsed time: 1.4176s
Graham Reeds decode elapsed time: 1.34872s
The encoded files are the same

I could work on it more and get better code coverage, support other encodings (not just baseN) and maybe I will, but for now I will push it here.
