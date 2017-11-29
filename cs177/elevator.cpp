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
void load_elevator(long pickup, long dropoff, long on_board, long elevatorid);
long group_size();
long loading_time(long num);
long make_destination(long whereami);

// mailbox
mailbox elevatorid_box("id_box");
mailbox pickup_box("pickup");

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
}

// generate groups of new passengers at specified location
void make_passengers(long pickup){
  const char* myName=to_string(pickup).c_str();
  create(myName);

  //run for 1 day in seconds
  while(clock < 86400){
    // exponential interarrivals, mean 10 minutes
    hold(expntl(800));

    // seperate groups of passangers into individual processes
    long group = group_size();
    long dropoff = make_destination(pickup);
    for (long i=0;i<group;i++)
      passenger(pickup, dropoff);
  }
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
	want_up[pickup]++;
  else
    want_down[pickup]++;
  wakeup.set();
  pickup_box.send(pickup);
  pickup_box.send(pickup);
  update_workload.release();

  // 2) wait for correct boarding event
  while((going_up[0].state() == OCC || going_down[0].state() == OCC)&&(going_up[1].state() == OCC || going_down[1].state() == OCC)){}
  if(going_up[0].state() == OCC || going_down[0].state() == OCC)
	  elevatorid = 1;
  else if(going_up[1].state() == OCC || going_down[1].state() == OCC)
	  elevatorid = 0;
  else{
    if(abs(whereami[0]-pickup) > abs(whereami[1]-pickup))
      elevatorid = 1;
    else if(abs(whereami[0]-pickup) < abs(whereami[1]-pickup))
	  elevatorid = 0;
	else if(pickup < dropoff)
		elevatorid = 0;
	else
		elevatorid = 1;
  }
  elevatorid_box.send(elevatorid);

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

	pickup_box.receive(&pickup);

	// if elevator was selected for the pickup request
	long idhold;
	elevatorid_box.receive(&idhold);
	if(elevatorid == idhold){
	  if(elevatorid == 1)
	    cout << "\t\t";
	  cout << "Pick up: " << pickup << endl;
      
	  // travel to pickup location
      hold(5*sqrt(abs(whereami[elevatorid]-pickup)));
	  if(want_up[pickup] != -1)
		on_board = want_up[pickup];
	  else
		  on_board = want_down[pickup];

      // pickup
      hold(2);
      load_elevator(pickup, dropoff, on_board, elevatorid);
	  hold(3);

      // travel to dropoff location
      hold(5*sqrt(abs(pickup-dropoff)));

      // dropoff
      hold(2);
      here_is_floor[elevatorid].set();
      on_board = 0;
      hold(3);

	  // update stop request and elevator location
	  // want_off[elevatorid][dropoff] = 0;
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
void load_elevator(long pickup, long dropoff, long on_board, long elevatorid){
  if(pickup<dropoff){
    while((on_board < MAX_OCCUPANCY) && going_up[elevatorid].wait_cnt() > 0){
      going_up[elevatorid].set();
      on_board++;
    }
  }
  else{
    while((on_board < MAX_OCCUPANCY) && going_down[elevatorid].wait_cnt() > 0){
      going_up[elevatorid].set();
      on_board++;
    }
  }
  hold(loading_time(on_board));
}

long group_size(){
  double x = prob();
  if (x < 0.3) return 1;
  else {
    if (x < 0.7) return 2;
    else return 5;
  }
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
