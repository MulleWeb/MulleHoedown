#  MulleHoedown

#### 💃🏼 Markdown support for mulle-objc


Converts [markdown](https://en.wikipedia.org/wiki/Markdown) to HTML.

Build Status | Release Version
-------------|-----------------------------------
[![Build Status](https://travis-ci.org/MulleWeb/MulleHoedown.svg?branch=release)](https://travis-ci.org/MulleWeb/MulleHoedown) | ![Mulle kybernetiK tag](https://img.shields.io/github/tag/MulleWeb/MulleHoedown.svg) [![Build Status](https://travis-ci.org/MulleWeb/MulleHoedown.svg?branch=release)](https://travis-ci.org/MulleWeb/MulleHoedown)


## About

MulleHowdown adds the following conversion method to **NSString**:

```
- (NSString *) hoedownedString;
```

and adds the following conversion method to **NSData**:

```
- (NSData *) hoedownedData;
```

#### Example:

This code

```
NSString   *html;
NSString   *markdown;

markdown = @"# VfL Bochum 1848";
html     = [mardown hoedownedString];
printf( "%s\n", [html UTF8String]);
```

will output the following HTML `<H1>VfL Bochum 1848</H1>`.



## Add

Use [mulle-sde](//github.com/mulle-sde) to add MulleHoedown to your project:

```
mulle-sde dependency add --objc --github MulleWeb MulleHoedown
```

## Install

Use [mulle-sde](//github.com/mulle-sde) to build and install MulleHoedown
and all its dependencies:

```
mulle-sde install --objc --prefix /usr/local \
   https://github.com/MulleWeb/MulleHoedown/archive/latest.tar.gz
```

## Acknowledgements

MulleHoeDown contains  the [hoedown](https://github.com/hoedown/hoedown), which
comes with this copyright and license

```
Copyright (c) 2008, Natacha Porté
Copyright (c) 2011, Vicent Martí
Copyright (c) 2014, Xavier Mendez, Devin Torres and the hoedown authors
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
```

## Authors

[Nat!](//www.mulle-kybernetik.com/weblog) for
[Mulle kybernetiK](//www.mulle-kybernetik.com) and
[Codeon GmbH](//www.codeon.de)
