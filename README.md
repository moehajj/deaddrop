# Deaddrop

Implements cross-core, high-bandwidth (~40000 Bytes/s in our testing),
covert-channel using flush-reload on LLC exploiting zero pages.

Course lab project for UIUC [CS 598CLF Secure Processor Design](http://cwfletcher.net/598fa19.html).

## Build

```sh
mkdir build
cd build
cmake ..
make
```

The build process will build four executables in total: sender and receiver
pair, and the duplex versions: duplex and duplex2. All executables can be
found in ./build/bin directory.

## Run

Sender:
```sh
./sender
```

Receiver:
```sh
./receiver
```

To run the duplex versions:
```
./duplex
```

And in another terminal (the second client):

```
./duplex2
```

The two duplex binaries are compiled from duplex.c but differ in a
configuration variable that is set at compile time.

## LICENSE

Copyright (c) 2019 Mohamad Hadi El Hajj and Sushant Dinesh.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE
OR OTHER DEALINGS IN THE SOFTWARE.
