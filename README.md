# repeat-dna 

This repository contains a set of methos for identify repeats of a string of DNA T\[1,n\].

We use the Burrows-Wheeler Transform (BWT), suffix array (SA) and longest common prefix array (LCP) to identify 2 types of repeats .

## Build requirements

gcc

python3

make

```sh
pip install WordCloud
pip install -U matplotlib
```

## Example

**Compilation:**

```sh
git clone --recursive https://github.com/anabeatrizthezolin/Repeat-DNA.git
make
```

**Available options:**

```sh
-t  input as txt files
-f  input as fasta or fastq files
-o  output converted file
-1  type 1
-2  type 2
-r  repeats
-si size and index
-s  minimum repeat size
-p  print
-k  number of repetitions of _Word_ _Cloud_
-v  verbose output
-h  this help message

```
_Notes:_ 
- Supported extensions are _.txt_, _.fasta_ and _.fastq_.


**Run a test:**

```c
python3 main.py dataset/example.fastq -f -1 -2 -r -s 1 -p
```

**Output:**

```c
Sending logging messages to file: dataset/example.fastq.repeat.log
## gsufsort ##
## store_to_disk ##
dataset/example.fastq.4.sa      156 bytes (n = 39)
dataset/example.fastq.4.lcp     156 bytes (n = 39)
dataset/example.fastq.bwt       39 bytes (n = 39)
malloc_count ### exiting, total: 56.087, peak: 21.192, current: 1.024
Elapsed time: 0.0032

malloc_count ### exiting, total: 124.876, peak: 110.504, current: 108.416
Elapsed time: 0.0039

## Repeat DNA ##
Type 1:
3 A
2 CCT
3 CC
2 CTTT
3 CTT
5 CT
9 C
3 GC
2 GGC
3 GT
8 G
2 TA
2 TCTT
2 TGT
4 TG
3 TTG
3 TTT
8 TT
17 T

Type 2:
2 CCT
2 CTTT
2 GGC
2 TA
2 TCTT
2 TGT
3 TTG
```

<img align="center" src="resources/Word_Cloud.png?raw=true" />
</a>
