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

vector<long> conversionValues(24);
void initializeConversionValues(){
  conversionValues[23]=1;
  conversionValues[22]=conversionValues[23]*5;  conversionValues[21]=conversionValues[22]*2;  conversionValues[20]=conversionValues[21]*2;
  conversionValues[19]=conversionValues[20]*5;  conversionValues[18]=conversionValues[19]*2;  conversionValues[17]=conversionValues[18]*2;
  conversionValues[16]=conversionValues[17]*5;  conversionValues[15]=conversionValues[16]*2;  conversionValues[14]=conversionValues[15]*2;
  conversionValues[13]=conversionValues[14]*5;  conversionValues[12]=conversionValues[13]*2;  conversionValues[11]=conversionValues[12]*2;
  conversionValues[10]=conversionValues[11]*5;  conversionValues[9]=conversionValues[10]*2;  conversionValues[8]=conversionValues[9]*2;
  conversionValues[7]=conversionValues[8]*5;  conversionValues[6]=conversionValues[7]*2;  conversionValues[5]=conversionValues[6]*2;
  conversionValues[4]=conversionValues[5]*5;  conversionValues[3]=conversionValues[4]*2;  conversionValues[2]=conversionValues[3]*2;
  conversionValues[1]=conversionValues[2]*5;  conversionValues[0]=conversionValues[1]*2;
}

vector<short> convertToInstructions(long machineNumber){
  short pos = 0;
  vector<short> result(24, 0);
  while(machineNumber>0){
    if((pos+1)%3==0){
      bool found = 0;
      result[pos] = 0;
      // printf("r[%d]->%d\n", pos, 0);
      for(int i=4; i>=0; i--){
        if(!found && machineNumber>=conversionValues[pos]*i){
          machineNumber-=conversionValues[pos]*i;
          result[pos] = i;
          // printf("r[%d]->%d\n", pos, i);
          found = 1;
        }
      }
    } else {
      if(machineNumber>=conversionValues[pos]){
        machineNumber-=conversionValues[pos];
        result[pos] = 1;
        // printf("r[%d]->%d\n", pos, 1);
      } else {
        result[pos] = 0;
        // printf("r[%d]->%d\n", pos, 0);
      }
    }
    pos++;
  }
  return result;
}

void printValue(vector<short> converted){
  long result = 0;
  for(int i=0; i<converted.size(); i++){
    result+=converted[i]*conversionValues[i];
  }
  printf("\nvalue:%ld\n", result);
}

int main(){
  initializeConversionValues();
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

  for(int i=0; i<conversionValues.size(); i++){
    // printf("cv[%d]:%li\n", i, conversionValues[i]);
  }
  long test = 22563805986;
  // long test = 220;
  vector<short> result = convertToInstructions(test);
  printf("\n%ld -> ", test);
  for(int i=0; i<result.size(); i++){
    printf("%i", result[i]);
  }
  // printValue(result);
  printf("\n--DONE--\n");
  return 0;
}
