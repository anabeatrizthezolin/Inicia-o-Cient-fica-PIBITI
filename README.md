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
-1	print the repeats
-2 	print the number of repeats and the maximum length
-v	verbose output
-h	this help message

```
_Notes:_ 
- Supported extensions are _.txt_, _.fasta_ and _.fastq_.


**Run a test:**

```c
./repeat example.txt -s 1 -1
```

**Output:**

```c
Command line:
 ./remap -A 7 -v ../dataset/reads.fastq
d = 10000
N = 946583 bytes
sizeof(int) = 4 bytes
## RANDOM ##
A: G
C: N
G: A
N: C
T: T
##
Number of Lyndon factors: 15
Average length: 63105.53
Maximum length: 605983
##
15	63105.53	605983
```

