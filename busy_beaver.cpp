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
  int numCards = 4;
  vector<Card*> cards(numCards, new Card(0,0,0, 0,0,0));  // 4 cards, initially all zeroes
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
  for(int card=0; card<numCards; card++){
    delete cards[card];
  }
  printf("--DONE--\n");
  return 0;
}
