#include <iostream>
#include <string>
#include <math.h>

using namespace std;

//Everything needed for the Linked List and Node functions in here
class LinkedList{
private:
  struct node{
    string fileName;  //name of program
    bool ocupado; //whether the space is free or not
    int pgNum; //page number in linked list
    node* next; //"next" node pointer
  };

    node* head; //"head" node pointer. Stays at front of list.
    node* curr; //Traversing node pointer
    node* temp; //"Temp" node pointer. Follows curr pointer. Used for comparison

public:
  LinkedList(){ //Constructor statement
    //Initially set all node pointers to NULL
    head = NULL;
    curr = NULL;
    temp = NULL;
  }

  void createNode(string name){ //Used to create the initial Linked List
    node* n = new node; //create new node
    n->next = NULL; //the new node's internal pointer points to nothing
    n->fileName = name; //set the node's name to the name in the parameter
    n->ocupado = false; //the status of the node will be unoccupied; therefore false


    if (head != NULL){ //If the List is not empty
      while(curr->next != NULL){ //if the "curr" pointer isn't pointing to nothing
        curr = curr->next;  //then move onto the next node
      } //when we've reached the end of the list, it's time to add the new node, but first..
      n->pgNum = (curr->pgNum) + 1 ; //..Add 1, so that the correct page number is assigned
      curr->next = n; //now add the node
    }
    else{ //If the List is empty
      n->pgNum = 1;
      head = n; //then the new node created will be where the head points to
      curr = head;
    }
  }

  void waddFile(string name, float size){ //Used to add programs. Worst fit
    //pneeded is how many pages you need as a float value
    float pneeded = (size/4); //divide the float value by 4KB
    //psize is how many pages you need as an int value
    int psize = (int)(ceil(pneeded)); //Round value up and convert to int

    bool bigfoot=false; //true if the program exists already
    int tempL=1; //stores fragment beginning page#
    int permL=1; //stores program beginning page#
    int testF; //stores size of test fragment
    int fitF = 0; //stores size of largest fragment. Initially 0.

    if(name == "Free"){
      printf("%s","Cannot name a program Free\n");
      return;
    }

    curr=head; //go to start
    while(curr){ //so long as we're pointing somewhere
      if(curr->fileName.c_str() == name){ //if the program already exists
        printf("%s %s %s", "Error, Program",name.c_str(),"already running.\n");
        bigfoot = true; //set boolean to true
        break; //exit loop
      }
      curr = curr->next; //move on
    }

    //For God's sake, don't use a while loop. Bad times. Scary terminal.
    if(!bigfoot){ //if program didn't already exist.
      curr = head; //set the "curr" pointer to the front of the list
      while(curr){ //so long as we're pointing at something...
        testF = 0; //with each loop, reset the test size to 0
        //while the current spot is not occupied and is not next to a NULL pointer...
        while(curr != NULL && !curr->ocupado){
          if (testF == 0){ //if testF is 0, then we're at the start of a new fragment
            testF++; //Fragment size goes up by 1
            tempL = curr->pgNum; //The starting location of the fragment is here
          }
          else if(testF != 0){ //if testF is NOT 0, then we're still in the same fragment
            testF++; //and the fragment size goes up again
          }
          curr = curr->next; //advance the list. if it's a NULL, it'll break out of the list
        }
        /*if you've reached this point and testF is still 0, that means you're in
          an occupied space, in which case you advance the list. Otherwise, you'll
          be stuck in an infinite loop*/
        if (testF==0 && curr){
          curr=curr->next;
        }
        //if the test fragment size is larger than the largest recorded fragment
        if (testF > fitF){
          fitF = testF; //then update the largest fragment size
          permL = tempL; //and record where that fragment starts
        }
      } //at this point, you should have the largest fragment size and its location

      curr = head; //go back to the front of the list
      if (fitF >= psize){ //if the largest fragment can fit the program...
        //cycle through the list until you find the location of the largest fragment
        while(curr->pgNum != permL){
          curr = curr->next;
        }
        //once you find the location, add the program the appropriate number of times
        for (int i=1; i<=psize; i++){
          curr->fileName = name;
          curr->ocupado = true; //set the page as occupied
          curr = curr->next; //and then advance
        }
        printf("%s %s %s %d %s", "Program", name.c_str(),"added successfully,", psize ,"page(s) used.\n");
      }
      else{ //if the largest fragment is too big
        printf("%s %s", "Error, not enough memory for Program", name.c_str());
      }
    }
  }

  void killFile(string name){
    int mine = 0; //number of reclaimed pages
    curr=head; //set the "curr" pointer to the beginning
    while(curr){  //while "curr" is pointing something to something
      if(curr->fileName.c_str() == name){ //if the program name is found
        curr->fileName = "Free"; //rename it "Free"
        curr->ocupado = false; //reset the program to being unoccupied
        mine++; //add 1 to the number of reclaimed pages
      }
      curr = curr->next; //advance the list
    }
    printf("%s %s %s %d %s","Program",name.c_str(),"successfully killed",mine,"page(s) reclaimed.\n");
  }

  void fragCount(){
    int frags = 0; //number of fragments
    curr = head; //go to start of list
    while(curr){ //while you're pointing at something
      if(curr->pgNum == 1){ //use this for the beginning of the list, as the temp pointer hasn't been set yet
        if(!curr->ocupado){ //if the space is not occupied
          frags++; //add to the number of fragments
          temp = curr; //set the temp pointer to the curr pointer's current position
          curr = curr->next; //and advance the curr pointer. Now we have the temp pointer behind the curr pointer
        }
        else{ //if the space IS occupied
          //still gotta move that list up
          temp = curr;
          curr = curr->next;
        }
      }
      else{ //if we're not at the beginning of the list
        if(!curr->ocupado && temp->ocupado){ //if the current spot is empty and the previous isn't...
          frags++; //then we're at the start of a new fragment! fun stuff.
          //gotta advance that list
          temp = curr;
          curr = curr->next;
        }
        else{ //in any other situation..
          //..just move the list
          temp = curr;
          curr = curr->next;
        }
      }
    }
    //When all's said and done, print out the appropriate statement
    printf("%s %d %s","There are",frags,"fragment(s)\n");
  }

  void printList(){
    curr = head; //set the "curr" pointer to the front of the list
    printf("%s", "\n");
    while(curr != NULL){ //so long as it's pointing at something...
      for(int i=0; i<8; i++){ //when 8 names are printed..
        printf("%s %s", curr->fileName.c_str(), ""); //print the name within
        curr = curr->next; //and advance the list
      }
      printf("%s", "\n"); //move to the next line
    }
  }

  void baddFile(string name, float size){ //Used to add programs. Best fit
    //pneeded is how many pages you need as a float value
    float pneeded = (size/4); //divide the float value by 4KB
    //psize is how many pages you need as an int value
    int psize = (int)(ceil(pneeded)); //Round value up and convert to int

    bool bigfoot=false; //true if the program exists already
    int tempL=1; //stores fragment beginning page#
    int permL=1; //stores program beginning page#
    int testF; //stores size of test fragment
    int fitF = 99999999; //stores size of best fragment. Initially some absurdly larger number.

    if(name == "Free"){
      printf("%s","Cannot name a program Free\n");
      return;
    }

    curr=head; //go to start
    while(curr){ //so long as we're pointing somewhere
      if(curr->fileName.c_str() == name){ //if the program already exists
        printf("%s %s %s", "Error, Program",name.c_str(),"already running.\n");
        bigfoot = true; //set boolean to true
        break; //exit loop
      }
      curr = curr->next; //move on
    }

    //For God's sake, don't use a while loop. Bad times. Scary terminal.
    if(!bigfoot){ //if program didn't already exist.
      curr = head; //set the "curr" pointer to the front of the list
      while(curr){ //so long as we're pointing at something...
        testF = 0; //with each loop, reset the test size to 0
        //while the current spot is not occupied and is not next to a NULL pointer...
        while(curr!= NULL && !curr->ocupado){
          if (testF == 0){ //if testF is 0, then we're at the start of a new fragment
            testF++; //Fragment size goes up by 1
            tempL = curr->pgNum; //The starting location of the fragment is here
          }
          else if(testF != 0){ //if testF is NOT 0, then we're still in the same fragment
            testF++; //and the fragment size goes up again
          }
          curr = curr->next; //advance the list. if it's a NULL, it'll break out of the list
        }
        /*if you've reached this point and testF is still 0, that means you're in
          an occupied space, in which case you advance the list. Otherwise, you'll
          be stuck in an infinite loop*/
        if (testF==0 && curr){
          curr=curr->next;
        }
        //if the test fragment size is a better fit than the previous fragment
        if ((testF - psize) < (fitF - psize) && (testF - psize) >= 0){
          fitF = testF; //then update the best fragment's size
          permL = tempL; //and record where that fragment starts
        }
      } //at this point, you should have the best fragment and its location

      curr = head; //go back to the front of the list
      if (fitF >= psize){ //if the fragment can fit the program...
        //cycle through the list until you find the location of the largest fragment
        while(curr->pgNum != permL){
          curr = curr->next;
        }
        //once you find the location, add the program the appropriate number of times
        for (int i=1; i<=psize; i++){
          curr->fileName = name;
          curr->ocupado = true; //set the page as occupied
          curr = curr->next; //and then advance
        }
        printf("%s %s %s %d %s", "Program", name.c_str(),"added successfully,", psize ,"page(s) used.\n");
      }
      else{ //if the fragment is too big
        printf("%s %s", "Error, not enough memory for Program", name.c_str());
      }
    }
  }
};

//Menu display
void menu(){
  printf("%s","1. Add program\n");
  printf("%s","2. Kill program\n");
  printf("%s","3. Fragmentation\n");
  printf("%s","4. Print memory\n");
  printf("%s","5. Exit\n");
}
