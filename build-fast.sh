#!/bin/sh
gcc -Icodec/ -Ofast encoder.c codec/*.c -o encoder
gcc -Icodec/ -Ofast decoder.c codec/*.c -o decoder
