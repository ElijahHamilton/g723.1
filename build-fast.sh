#!/bin/sh
gcc -Icodec/ -O3 encoder.c codec/*.c -o encoder
gcc -Icodec/ -O3 decoder.c codec/*.c -o decoder
