#include <iostream>
#include "pa2.h"
#include <string>

using namespace std;

int main(int argc, const char* argv[]){

  //if they enter the wrong number of parameters
  if(argc != 2){
    printf("%s", "Wrong number of parameters!\n");
    return -1;
  }

  //if the worst fit option is chosen
  else if(string(argv[1]) == "worst"){
    int userInput = 0;
    string prgName;
    float fileSize;

    //Create the Linked List
    LinkedList* Memory = new LinkedList();
    for(int i=0; i<32; i++){ //Set them as "Free"
      Memory->createNode("Free");
    }
    printf("%s","Using worst fit algorithm\n");

    //While user choice is not 5
    while(userInput != 5){
      menu();
      printf("%s","Choice -");
      cin>>userInput;
      //switch statement to navigate menu
      switch(userInput){
        //add
        case 1: printf("%s","Program name -");
                cin>>prgName;
                printf("%s", "Program size (KB) -");
                cin>>fileSize;
                Memory->waddFile(prgName, fileSize);
                break;
        //KILL
        case 2: printf("%s","Program name -");
                cin>>prgName;
                Memory->killFile(prgName);
                break;
        //fragment
        case 3: Memory->fragCount();
                break;
        //print
        case 4: Memory->printList();
                break;
        //quit
        case 5: break;
        //oops
        default: printf("%s","Invalid choice\n");
      }
    }
  }

  //if the best fit option is chosen
  else if(string(argv[1]) == "best"){
    int userInput = 0;
    string prgName;
    float fileSize;

    //Create the Linked List
    LinkedList* Memory = new LinkedList();
    for(int i=0; i<32; i++){ //Set them as "Free"
      Memory->createNode("Free");
    }
    printf("%s","Using best fit algorithm\n");

    //While user choice is not 5
    while(userInput != 5){
      menu();
      printf("%s","Choice -");
      cin>>userInput;
      //switch statement to navigate menu
      switch(userInput){
        //add
        case 1: printf("%s","Program name -");
                cin>>prgName;
                printf("%s","Program size (KB) -");
                cin>>fileSize;
                Memory->baddFile(prgName, fileSize);
                break;
        //KILL
        case 2: printf("%s","Program name -");
                cin>>prgName;
                Memory->killFile(prgName);
                break;
        //fragment
        case 3: Memory->fragCount();
                break;
        //print
        case 4: Memory->printList();
                break;
        //quit
        case 5: break;
        //oops
        default: printf("%s","Invalid choice\n");
      }
    }
  }

  //If something wonky was inputted
  else{
    printf("%s","Invalid Parameters!\n");
    return -1;
  }

  //if everything worked
  return 0;
}
