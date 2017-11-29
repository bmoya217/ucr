#include <iostream>
#include <string.h>
#include <vector>
#include <cmath>
#include "cpp.h"

using namespace std;

#define MAX_OCCUPANCY 6
#define NUM_FLOORS 8
#define NUM_ELEVATORS 2
#define TINY 1.e-20

string people[3] = {"Incoming","Outgoing","Interfloor"};

// data arrays
long whereami[NUM_ELEVATORS];
long want_up[NUM_FLOORS];
long want_down[NUM_FLOORS];

event_set going_up("going up", NUM_ELEVATORS);
event_set going_down("going down", NUM_ELEVATORS);
event_set here_is_floor("get off", NUM_ELEVATORS);

facility update_workload("update workload");
event wakeup("Wakeup");

// processes
void elevator(long elevatorid);
void make_passengers(long pickup);
void passenger(long pickup, long dropoff);

// helper functions
void load_elevator(long pickup, long dropoff, long &on_board, long elevatorid);
long group_size();
long loading_time(long num);
long make_destination(long whereami);
bool moving(long elevatorid,long pickup);
// mailbox
mailbox elevatorid_box("id_box");

extern "C" void sim(){
  create("sim");

  // data arrays
  whereami[0] = 2;
  whereami[1] = 5;
  for(int i = 0; i < NUM_FLOORS; i++){
    want_up[i] = -1;
    want_down[i] = -1;
  }

  //int want_off[NUM_ELEVATORS][NUM_FLOORS];


  // generate elevators
  for(int e = 0; e < NUM_ELEVATORS; e++)
    elevator(e);

  // generate passengers
  for(int f = 0; f < NUM_FLOORS; f++)
    make_passengers(f);

  // let run, print report, terminate sim
  hold (86400);
  report();
  status_mailboxes();
  status_events();
}

// generate groups of new passengers at specified location
void make_passengers(long pickup){
  const char* myName=to_string(pickup).c_str();
  create(myName);
	
	passenger(4, 0);
	passenger(6, 8);
}

// individual passenger process
void passenger(long pickup, long dropoff){
  int type = 2;
  if(pickup == 0)
    type = 0;
  else if(dropoff == 0)
    type = 1;
  const char* myName = people[type].c_str();
  create(myName);

  long elevatorid;

  // 1) wakeup elevator and set call button
  update_workload.reserve();
  if(pickup < dropoff)
    want_up[pickup] = dropoff;
  else
    want_down[pickup] = dropoff;
  wakeup.set();
  update_workload.release();
  hold(TINY);
  // 3) 
  elevatorid_box.receive(&elevatorid);
  
  if(pickup < dropoff)
    going_up[elevatorid].wait();
  else
    going_down[elevatorid].wait();

  // 4) get off on your floor
  here_is_floor[elevatorid].wait();
}

// manage the actions of a single elevator
void elevator(long elevatorid){
  const char* myName = to_string(elevatorid).c_str();
  create(myName);
	whereami[0] = 1;
	whereami[1]= 2;
  long other_elevatator = 0;
  if(elevatorid == 0)
    other_elevatator = 1;

  long on_board;
  long dropoff;
  long pickup;
  bool selected;

  while(1){
    wakeup.wait();
    on_board = 0;
	if(elevatorid == 1)
		cout << "\t\t";
	cout << "Location: " << whereami[elevatorid] << endl;

    update_workload.reserve();
    // get pickup location
	pickup = -1;
    for(int i = 0; i < NUM_FLOORS; i++)
      if(want_down[i]!= -1 || want_up[i]!= -1)
        pickup = i;
	if(pickup == -1)
		cout << "ERROR: PICKUP NOT FOUND\n";

    // compare my distance with the other elevators distance
    selected = true;
    if(going_up[other_elevatator].state()== OCC || going_down[other_elevatator].state() == OCC){
      if(abs(whereami[elevatorid]-pickup) >= abs(whereami[other_elevatator]-pickup))
          selected = false;
      if(abs(whereami[elevatorid]-pickup) == abs(whereami[other_elevatator]-pickup))
        if(elevatorid == 1)
          selected = true;
    }
	
	// send the elevatorid to the passenger
	if(selected == true)
      elevatorid_box.send(elevatorid);
	update_workload.release();
	
	// if elevator was selected for the pickup request
	if(selected){
	  if(elevatorid == 1)
	    cout << "\t\t";
	  cout << "Pick up: " << pickup << endl;
      
	if(want_up[pickup] != -1)
		dropoff = want_up[pickup];
	  else
		dropoff = want_down[pickup];

	  // travel to pickup location
      hold(5*sqrt(abs(whereami[elevatorid]-pickup)));
	  
      // pickup
      hold(2);
	  update_workload.reserve();
      load_elevator(pickup, dropoff, on_board, elevatorid);
	  update_workload.release();
	  hold(loading_time(on_board));
	  hold(3);


	  // reset elevator call
	if(pickup > dropoff)
		want_down[pickup] = -1;
	else
		want_up[pickup]= -1;

      // travel to dropoff location
      hold(5*sqrt(abs(pickup-dropoff)));

      // dropoff
      hold(2);
      here_is_floor[elevatorid].set();
      hold(3);

	  // update stop request and elevator location
      whereami[elevatorid] = dropoff;

	  if(elevatorid == 1)
		cout << "\t\t";
	  cout << "Drop off: " << dropoff << endl;
    }

    // move to better sleeping position
    else{
	  if(elevatorid == 1)
	  cout << "\t\t";
	  cout << "Rest at: 4\n";

      hold(5*sqrt(abs(whereami[elevatorid]-4)));
      whereami[elevatorid] = 4;
    }

	going_up[elevatorid].clear();
	going_down[elevatorid].clear();
  }
}

// might not load all passengers at the spot
void load_elevator(long pickup, long dropoff, long & on_board, long elevatorid){
  if(pickup<dropoff){
    while((on_board < MAX_OCCUPANCY) && going_up[elevatorid].state() == OCC){
      going_up[elevatorid].clear();
	  on_board++;
      hold(TINY);
    }
  }
  else{
    while((on_board < MAX_OCCUPANCY) && going_down[elevatorid].state() == OCC){
      going_down[elevatorid].clear();
      on_board++;
      hold(TINY);
    }
  }
  hold(loading_time(on_board));
}

long group_size(){
  return 1;
  }

long make_destination(long whereami){
  long destination = whereami;
  while(destination == whereami)
    destination = uniform(0, NUM_FLOORS-1);
  return destination;
}

// loading / unloading time for a certain number of people
long loading_time(long num){
  return uniform(5,15);
}
