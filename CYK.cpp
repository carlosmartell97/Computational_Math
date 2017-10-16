#include <string>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cstddef>
#include <queue>

using namespace std;

map<string, string > productions;

vector<string> split(string text, string separators){
  vector<string> result;
  size_t found = text.find_first_of(separators);
  if(found==string::npos){
    result.push_back(text);
    return result;
  }
  int foundInt = static_cast<int>(found);
  while(found!=string::npos){
    result.push_back(
      text.substr(0, foundInt)
    );
    text = text.substr(foundInt+1, text.size()-1);
    found = text.find_first_of(separators);
    foundInt = static_cast<int>(found);
  }
  result.push_back(text);
  return result;
}

class nextSearch{
  public:
    string letter;
    int i, j;
    nextSearch();
    nextSearch(string letter, int i, int j){
      this->letter=letter; this->i=i; this->j=j;
    }
};

pair<nextSearch*, nextSearch*> backtrack(string letter, int i, int j, int size, vector< vector< string > > grid){
  // printf("\n\nbacktrack(). Looking for %s in %d,%d\n", letter.c_str(), i, j);
  pair<nextSearch*, nextSearch*> found;
  string x, y, substrX, substrY, combine;
  for(int atI=i; atI<j; atI++){
    // printf("[%d][%d],", i, atI);
    // printf("[%d][%d]\n", atI+1, j);
    x = grid[i][atI];
    y = grid[atI+1][j];
    for(uint atX=0; atX<x.size(); atX++){
      for(uint atY=0; atY<y.size(); atY++){
        substrX = x.substr(atX,1);
        substrY = y.substr(atY,1);
        combine = x.substr(atX,1)+=y.substr(atY,1);
        // printf("%s<->%s ", substrX.c_str(), substrY.c_str());
        if(productions[combine].find_first_of(letter) != string::npos){
          // printf("PRODUCTION:%s->%s%s\n\t", letter.c_str(), substrX.c_str(), substrY.c_str());
          found.first = new nextSearch(substrX, i, atI);
          found.second = new nextSearch(substrY, atI+1, j);
          return found;
        }
      }
    }
  }
  return found;
}

int main(){
  map<char, short> terminales;
  map<char, short> noTerminales;
  string inputProductions, cadena;

  printf("describe the productions of S.\n\tS->");
  string text;
  // text = "AB|BC";
  cin >> text;
  printf("\n");
  string separators = "|";
  // fill productions map with S
  vector<string> splitted = split(text, separators);
  for(string s : splitted){
    productions[s] = "S";
    for(char c : s){
      // printf("%c", c);
      int ascii = (int)c;
      if( ascii>=65 && ascii<=90 ){
        noTerminales[c] = 1;
      }
      else if( ascii>=97 && ascii<=122 ){
        terminales[c] = 1;
      }
    }
    // printf("_\n");
  }

  // fill productions map with all others
  map<char, short>::iterator it = noTerminales.begin();
  while(it != noTerminales.end()){
    if(it->first!='S'){
      printf("describe the productions of %c\n\t%c->", it->first, it->first);
      cin >> inputProductions;
      vector<string> splittedProductions = split(inputProductions, separators);
      for(string s : splittedProductions){
        if (productions.find(s) != productions.end()){
          productions[s].push_back(it->first);
        } else {
          productions[s] = it->first;
        }
      }
      printf("\n");
    }
    it++;
  }

  printf("cadena:");
  // cadena = "baaba";
  cin >> cadena;
  printf("\nCALCULATING...\n");
  int size = cadena.size();
  string substring, combine;
  vector< vector< string > > grid(size, vector< string >(size));

  for(int t=0; t<size; t++){
    for(int i=0,j=t; i<size-t; i++,j++){
      // printf("[0][%d] ", i);
      // printf("[%d][5] \n", size-1-i);
      if(t==0){
        if(productions.find(cadena.substr(i,1)) != productions.end()){
          // printf("Y%s->%s", cadena.substr(i,1).c_str(), productions[cadena.substr(i,1)].c_str());
          grid[i][j] = productions[cadena.substr(i,1)];
        } else {
          grid[i][j] = "0";
        }
      } else {
        bool possible = 0;
        string possibleWith="";
        for(int l=1; l<=t; l++){

          string x="", y="";
          x = grid[i][j-(t+1-l)];
          y = grid[i+l][j];
          for(uint atX=0; atX<x.size(); atX++){
            for(uint atY=0; atY<y.size(); atY++){
              combine = x.substr(atX,1)+=y.substr(atY,1);
              if(productions.find(combine) != productions.end()){
                possible = 1;
                for(uint p=0; p<productions[combine].size(); p++){
                  string character = productions[combine].substr(p,1);
                  if(possibleWith.find(productions[combine].substr(p,1)) == string::npos){
                    possibleWith += productions[combine].substr(p,1);
                  }
                }
              }
            }
          }
          // printf("([%d][%d],[%d][%d]),", i, j-(t+1-l)/*, grid[i-l][j].c_str()*/, i+l, j/*, grid[i][j+l].c_str()*/);

        }
        grid[i][j] = possible?possibleWith:"0";
        // printf("->");
      }
      // printf("[%d][%d]%s   ", i, j, cadena.substr(j,size-t).c_str());
    }
    // printf("\n\n");
  }
  printf("DONE");

  // print productions
  printf("\n\nproductions:\n");
  map<string, string >::iterator iter = productions.begin();
  while(iter != productions.end()){
    printf("%s -> ", iter->first.c_str());
    for(char c : iter->second){
      printf("%c,", c);
    }
    printf("\n");
    iter++;
  }

  // print grid
  printf("\n\nupper trangular matrix:\n");
  for(int i=0; i<size; i++){
    for(int j=0; j<size; j++){
      if(j>=i)
      // [%d][%d]
        printf("%s ", /*i, j,*/ grid[i][j].c_str());
      else
        printf("  ");
    }
    printf("\n");
  }

  printf("\n\n");
  if(grid[0][size-1].find_first_of("S") != string::npos){
    printf("%s belongs to L(G)!\nderivation: S", cadena.c_str());
    // find a possible derivation
    // printf("size:%d\n", size);
    string x, y, subX, subY, combine, firstHalf, secondHalf;
    queue<nextSearch*> searches;
    vector<string> conversion(size, "");
    searches.push(new nextSearch("S", 0, size-1));
    while(!searches.empty()){
      nextSearch* next = searches.front();
      searches.pop();
      pair<nextSearch*, nextSearch*> result = backtrack(next->letter, next->i, next->j, size, grid);
      // printf("\n____next TRANSITION->%s%s\n", result.first->letter.c_str(), result.second->letter.c_str());
      if(result.first->i != result.first->j){
        searches.push(result.first);
      }
      if(result.second->i != result.second->j){
        searches.push(result.second);
      }
      conversion[result.first->i] = result.first->letter;
      conversion[result.second->i] = result.second->letter;
      printf("->");
      for(int i=0; i<size; i++){
        if(conversion[i]!="") printf("%s", conversion[i].c_str());
      }
      // printf("\n");
    }
  } else {
    printf("%s does not belong to L(G)...\n", cadena.c_str());
  }
  printf("->*%s\n", cadena.c_str());
  return 0;
}
