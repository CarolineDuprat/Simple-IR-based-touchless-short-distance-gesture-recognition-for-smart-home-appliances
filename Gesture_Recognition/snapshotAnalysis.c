#include "snapshotAnalysis.h"

/**
  * @file After creating the snapshots, you have to analyze them to determine the movement. For this he will have to study the transitions between
  * the different snapshots.
  * To know which movement corresponds to each transition, you will have to create a database with each possible transition
  * First, we will list each possible snapshot ( all_snapshots ). Then determine all the possible transitions from a snapshot ( transitions_pool ).
  * We will then analyze the list of snapshots of our movement. First we will find the position of each snapshot in the list. Then we will find out
  * which movements correspond to each transition. We will do a logical AND between each possible movement to determine the movement
  */
