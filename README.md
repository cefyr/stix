# stix
usage: stix /path/to/pattern/pattern.stix

Stix is a program for keeping count of cable knitting patterns. It is written 
in Python and uses termbox for the graphics parts. The point of it is to
highlight the current row in a knitting pattern and save it when it changes.

### The .stix format
Stix needs a text file as an argument. (I like using the .stix extension 
because it makes it obvious what the file is for.) The .stix format means the
first line of the file is the number of the last finished row of the pattern.
The rest of the file should contain the pattern, written from the bottom up.
In theory, this pattern can be written using any kind of language/symbols, but
it might be most practical to let one character symbolise one stitch.

Symbol | Translation 
------ | -------------
   V   | knit stitch (in front, if in a cable part)
   v   | knit stitch behind, in cable part
  \*   | purl stitch (in front, if in a cable part)
   .   | purl stitch behind, in cable part
   p   | increase to the right (see below)
   q   | increase to the left (see below)
   /   | k2tog on RS, p2tog on WS
   \   | s1k1psso (ödhpt) on RS, 2p twisted on WS
   ´   | p2 twisted on RS, s1k1psso (ödhpt) on WS
  \`   | (accent grave) p2tog on RS, k2tog on WS
       | no stitch, blank space added to make the pattern more easily read

### p/q increasing
After knitting/purling the stitch marked with a q, do the stitch under it as 
well, either knitting or purling it depending on how the stich will be handled 
in the next row. The p stitch only differs in that the increase comes before
the stitch instead of after.
