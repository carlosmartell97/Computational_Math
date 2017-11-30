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
This program is my silumation for an universal 4-state Turing machine, for arbitrary machine configurations. By trying different configurations, we can see which machine prints the maximum number of 1s on a tape that is initially filled with 0s, the famous Busy Beaver problem. You can learn more about the Busy Beaver problem here https://www.youtube.com/watch?v=CE8UhcyJS0I
<br/>
<br/>
Extending the idea of a "card" as a representation for a state as explained in the video above, we can think of each of our four states as the following
```
__________________________________
|             CARD n             |
|________________________________|
| read     write  move  nextCard |
| read     write  move  nextCard |
|________________________________|
```
So, an example of a card (state) could be
```
__________________________________
|             CARD 1             |
|________________________________|
|   0            0     1    1    |
|   1            1     0    4    |
|________________________________|
```
which would mean that in state 1: if a 0 is read on the tape, write 0, move right and transition to card 1 (itself). Or if a 1 is read on the tape, write 1, move left and transition to card 4.
<br/>
<br/>
Here, I'm considering the card 0 to be the halting card. So, how many Turing machines can me made with these 4 states? Well, with only one card, if we read 0, we can only have 2 possible values for "write" and "move" (we can only write either 0 or 1, and move either left or right). And, we can only have 5 values for "nextCard", we can only transition to cards 0(halt), 1, 2, 3 or 4. So, we have
```
2*2*5
```
possibilities. And the same happens for reading a 1, so we have
```
(2*2*5)^2
```
Now, since we have 4 cards just like this one, this gives us
```
((2*2*5)^2)^4
```
That's right... there are 25,600,000,000 possible 4-state Turing machines!
<br/>
<br/>
Out of all these possible machines, there's at least one that performs quite well, printing thirteen 1s on the tape before halting, in just 107 steps. This machine looks as follows:
```
__________________________________
|             CARD 1             |
|________________________________|
|   0            0     1    1    |
|   1            1     1    4    |
|________________________________|

__________________________________
|             CARD 2             |
|________________________________|
|   0            1     0    4    |
|   1            1     1    0    |
|________________________________|

__________________________________
|             CARD 3             |
|________________________________|
|   0            0     0    3    |
|   1            1     0    1    |
|________________________________|

__________________________________
|             CARD 4             |
|________________________________|
|   0            1     0    2    |
|   1            1     1    2    |
|________________________________|
```
How can my universal Turing machine test for all these different configurations? Well, for that I first convert from integer numbers to turing machine instructions (cards). This way, there is a unique machine configuration for each integer in the range of possible machines (0-24,599,999,999). These configurations are stored in a 24-block vector, so that the card configuration for the cards above (machine #8943228657) is
```
[0,1,1,1,1,4,1,0,4,1,1,0,0,0,3,1,0,1,1,0,2,1,1,2]
```
and the configuration corresponding to machine #0 is just
```
[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
```
and the configuration for the last possible machine, #24599999999, is
```
[1,1,4,1,1,4,1,1,4,1,1,4,1,1,4,1,1,4,1,1,4,1,1,4]
```
Many of these configurations would just go on forever, by either moving right or left indefinitely without halting or by looping in a right-left motion without halting. So, if any machine reaches the left or right end of my tape (a 10,000,000 block tape) or has had more than 5,000,000 iterations, the machine is just ignored and it continues on to the next one. Also, if no card has a transition to the halting card, that particular machine is ignored from the very beginning.

## Usage
You can try this out yourself, choosing a range between 0 and 24,599,999,999 for the machines you want to test. My universal Turing machine will try all these different configurations and write out the results to a file busy_beaver_results.txt. When the program finishes, you'll know all machines that printed the maximum amount of 1s on the tape. Hopefully you'll find a machine that prints out thirteen 1s! Be careful, though, the bigger the range of machines, the more time it will take to test them all. Just change the value for variables firstMachine and lastMachine, compile with c++11 standard and run the program.

## Results
.
