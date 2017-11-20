#include <cstdio>
#include <vector>
using namespace std;

class Card{
public:
  vector< vector<int> > instructions;
  Card(int zeroWrite, int zeroMove, int zeroNext,
      int oneWrite, int oneMove, int oneNext) : instructions(2, vector<int>(3)){
    instructions.reserve(3);
    instructions[0][0]=zeroWrite; instructions[0][1]=zeroMove; instructions[0][2]=zeroNext;   // instructions if zero is read
    instructions[1][0]=oneWrite; instructions[1][1]=oneMove; instructions[1][2]=oneNext;      // instructions if one is read
  }
};

int main(){
  int numCards = 5;                                             // states
  vector<Card*> cards(numCards, new Card(-1,-1,-1, -1,-1,-1));  // 4 cards + the final card (state), initially all -1

  vector<short> tape(5000,0);           // pseudo infinite tape filled with zeroes
  cards[1] = new Card(1,1,2, 1,0,2);
  cards[2] = new Card(1,0,1, 0,0,3);
  cards[3] = new Card(1,1,0, 1,0,4);
  cards[4] = new Card(1,1,4, 0,1,1);

  // print all cards
  for(int atCard=0; atCard<numCards; atCard++){
    printf("CARD %d\n", atCard);
    printf("0 %d%d%d\n", cards[atCard]->instructions[0][0],
    cards[atCard]->instructions[0][1],
    cards[atCard]->instructions[0][2]);
    printf("1 %d%d%d", cards[atCard]->instructions[1][0],
    cards[atCard]->instructions[1][1],
    cards[atCard]->instructions[1][2]);
    printf("\n\n");
  }

  int tapePosition = 2500;              // initial position is in the middle of the tape
  int currentCard = 1;                  // initial card
  short read;
  int steps = 0;
  while(true){
    steps++;
    read  = tape[tapePosition];
    tape[tapePosition] = cards[currentCard]->instructions[read][0];
    if(cards[currentCard]->instructions[read][1]==1){
      tapePosition++;                   // move right
    } else {
      tapePosition--;                   // move left
    }
    currentCard = cards[currentCard]->instructions[read][2];
    if(tapePosition<0 || tapePosition>=5000){
      printf("\ntape not big enough, position=%d\n", tapePosition);
    }
    if(currentCard==0){
      printf("\nMACHINE HALT\n");
      int ones = 0;
      for(int i=0; i<tape.size(); i++){
        if(tape[i]==1) ones++;
      }
      printf("ones:%d  steps:%d\n", ones, steps);
      break;
    }
  }
  // for(int card=0; card<numCards; card++){
  //   delete cards[card];
  // }

  printf("--DONE--\n");
  return 0;
}
