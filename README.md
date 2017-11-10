# Computational Math
## About
Files for a Computational Math course.
<br/>
<br/>
<br/>
<br/>
# CYK.cpp
This is my implementation of the CYK algorithm, an algorithm for finding out wether a word belongs to a certain grammar or not. This input grammar needs to be in Chomsky Normal Form. For best results, compile this program with the c++11 standard or above.

## Usage
For the purposes of this explanation, let's consider the following grammar in Chomsky Normal Form:

S->AB|SS|AC|BD  
A->a  
B->b  
C->SB  
D->SA  

Upon running, the program will first ask to describe all productions of the starting symbol, S.
```
describe the productions of S.
        S->
```
These are expected in the following form, without spaces and separated by pipes, "|".
```
describe the productions of S.
        S->AB|SS|AC|BD
```
For confirming your input, just hit the ENTER key.

Now, you will be asked to describe the productions for all non-terminal symbols present in your previous input. Each of these productions is expected in the same form that you described the productions for S.
```
describe the productions of A
        A->a

describe the productions of B
        B->b

describe the productions of C
        C->SB

describe the productions of D
        D->SA
```
After all non-terminal symbols' productions have been described, the program will now ask for a test word. The word you want to know wether it belongs to the input grammar or not. Word is expected without spaces. Confirm by hitting the ENTER key.
```
cadena:aabbab
```
## Results
The program will start calculating, and display DONE when it finishes. You will now be shown what the upper triangular matrix would look like if you were to do this by hand. And finally, display wether the word belongs to  the input grammar or not. If it does belong, you will also be shown a possible derivation from S to the test word.
```
upper trangular matrix:
A 0 0 S D S
  A S C 0 0
    B 0 0 0
      B 0 0
        A S
          B


aabbab belongs to L(G)!
derivation: S->SS->ACS->ACAB->ASBAB->AABBAB->*aabbab
```
<br/>
<br/>
<br/>
<br/>

# busy_beaver.cpp
.

## Usage
.

## Results
.