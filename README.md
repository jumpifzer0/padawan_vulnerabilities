# padawan_vulnerabilities

This repo consists of some applications that contain vulnerabilities that can lead to exploitation.
The list of vulnerable topics that can be exploited are listed below.

## Examples for Following Topics
```
Consideration : Some of the applications have been designed to be able to be exploited using multiple techinques, e.g. Direct Ret/SEH and/or Return Object Programming (ROP)

To increase difficulty, can consider implement DEP/ASLR
```

[yz] 1. (Linear) Stack Buffer Overflow 

[jz] 2. (Linear) Heap Buffer Overflow

[jz] 3. (Non-Linear) Out-Of-Bounds Writes (OOB-W)

[yz] 4. Integer Overflow / Underflow

[yz] 5. Other Integer Issues

[jz] 6. Uninitialized Data Access

[yz] 7. Race Condition

[jz] 8. Use-After-Free

[jz] 9. Type Confusion

[yz] 10. Information Disclosure 

## Repo Structure
```
For each vuln topic 1 folder 
    - A folder that contains the C code (src)
    - A folder that contains the vulnerable application (dist)
    - Short write up on what the vuln is 
```

## Compilation Description 
Compiler Version : gcc version 6.3.0
WITHOUT DEFENSES - DEP/ASLR/STACK CANARIES/CFI