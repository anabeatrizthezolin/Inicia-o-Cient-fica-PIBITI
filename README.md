# remap 

This repository contains a set of methos for identify repeats of a string of DNA T\[1,n\].

We use the Burrows-Wheeler Transform (BWT), suffix array (SA) and longest common prefix array (LCP) to identify 2 types of repeats .

## Build requirements

Python3

gcc

## Example

**Compilation:**

```sh
make
```

**Available options:**

```sh
-o  output converted file
-s  minimum repeat size
-1	type 1
-2 	type 2
-r  repeats
-si size and index
-p  print
-v	verbose output
-h	this help message

```
_Notes:_ 
- Supported extensions are _.txt_, _.fasta_ and _.fastq_.


**Run a test:**

```c
python3 main.py example.txt -s 1 -1 -2 -r --print
```

**Output:**

```c
 1 -1 -2 -r --print
Sending logging messages to file: example.txt.repeat.log
## gsufsort ##
## store_to_disk ##
example.txt.4.sa 	76 bytes (n = 19)
example.txt.4.lcp 	76 bytes (n = 19)
example.txt.bwt 	19 bytes (n = 19)
malloc_count ### exiting, total: 55.803, peak: 21.448, current: 1.144
Elapsed time: 0.0017

example.txt.type1
example.txt.type2
malloc_count ### exiting, total: 30.392, peak: 12.120, current: 10.222
Elapsed time: 0.0024

## Repeat DNA ##
Type 1:
anan
ana
an
a
ba

Type 2:
anan
ba
```

