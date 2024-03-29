# solitaire

A version of Bruce Schneier's [Solitaire]()
algorithm written in C.

## license

ISC / public domain (although if you are using this in any sort of serious
capacity, you really should reconsider everything you are doing.)

--------------------------------------------------------------------------------

the ISC license:
Copyright (c) 2011 Kyle Isom &lt;coder@kyleisom.net&gt;

Permission to use, copy, modify, and distribute this software for any
purpose with or without fee is hereby granted, provided that the above 
copyright notice and this permission notice appear in all copies.

THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE. 

--------------------------------------------------------------------------------

You may choose to follow this license or public domain. My intent with
dual-licensing this code is to afford you, the end user, maximum freedom
with the software. If public domain affords you more freedom, use it.


## usage
`deckgen -o <deck_file>`

`solitaire -e msg.txt -o msg.enc -k deck_file`

`solitaire -d msg.enc -o msg.txt -k deck_file`


## dependencies
The unit tests rely on [CUnit](http://cunit.sourceforge.net/).

