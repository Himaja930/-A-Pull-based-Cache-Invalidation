/*Himaja_Madala_Project3*/
#include <stdio.h>
#include <stdlib.h>
#include <csim.h>

// Constants for simulation parameters
#define NUM_CLIENTS 5
#define DB_SIZE 500
#define HOT_DATA_PROBABILITY 0.8
#define HOT_DATA_ITEMS 50
#define HOT_DATA_UPDATE_PROBABILITY 0.33
#define DATA_ITEM_SIZE 1024
#define BANDWIDTH 10000
#define CACHE_SIZE 100
#define COLD_DATA_ITEMS (DB_SIZE - HOT_DATA_ITEMS)
#define SIMTIME 50000

int cache[CACHE_SIZE];
int hotData[HOT_DATA_ITEMS];
int coldData[COLD_DATA_ITEMS];
int cachePointer;
int hotDataPointer;
int coldDataPointer;
int cache_hit = 0;
int cache_miss = 0;
double query_delay = 0;

// Function to simulate cache invalidation
void cacheInvalidation() {
  int client = (int)uniform(0, NUM_CLIENTS);
  int cacheIndex = (int)uniform(0, CACHE_SIZE);
  if (cache[cacheIndex] != -1) {
    printf("Client %d: Cache entry %d invalidated.\n", client, cacheIndex);
    cache[cacheIndex] = -1; // Invalidate the cache entry by setting it to -1
  }
}

// Function to simulate query generation
void queryGeneration(double T_query) {
  double queryTime = exponential(T_query);
  hold(queryTime);
}

// Function to simulate cache updates
void cacheUpdate() {
  int client = (int)uniform(0, NUM_CLIENTS);
  double hotDataUpdateProb = uniform(0, 1);
  if (hotDataUpdateProb < HOT_DATA_UPDATE_PROBABILITY) {
    int hotDataIndex = (int)uniform(0, HOT_DATA_ITEMS);
    printf("Client %d: Cache updated with hot data item %d.\n", client, hotData[hotDataIndex]);
    cache[cachePointer] = hotData[hotDataIndex];
    cachePointer = (cachePointer + 1) % CACHE_SIZE; 

  } else {
    int coldDataIndex = (int)uniform(0, COLD_DATA_ITEMS);

    printf("Client %d: Cache updated with cold data item %d.\n", client, coldData[coldDataIndex]);
    cache[cachePointer] = coldData[coldDataIndex];
    cachePointer = (cachePointer + 1) % CACHE_SIZE; 
  }
}



// Function to initialize simulation parameters
void init() {
  int i;

  // Initialize cache entries to -1
  for (i = 0; i < CACHE_SIZE; i++) {
    cache[i] = -1;
  }

  // Generate random hot data items
  for (i = 0; i < HOT_DATA_ITEMS; i++) {
    hotData[i] = (int)uniform(1, DB_SIZE);
  }

  // Generate random cold data items
  for (i = 0; i < COLD_DATA_ITEMS; i++) {
    coldData[i] = (int)uniform(1, DB_SIZE);
  }

  cachePointer = 0; // Reset cache pointer
}

// Function to simulate cache query
void cacheQuery(double T_query) {
  int client = (int)uniform(0, NUM_CLIENTS);
  double start_time = clock;
  queryGeneration(T_query);
  int cacheIndex = (int)uniform(0, CACHE_SIZE);
  if (cache[cacheIndex] == -1) {
    printf("Client %d: Cache miss at cache entry %d.\n", client, cacheIndex);
    cache_miss++;
  } else {
    printf("Client %d: Cache hit at cache entry %d with data item %d.\n", client, cacheIndex, cache[cacheIndex]);
    cache_hit++;
  }
  query_delay += clock - start_time;
}

// Main simulation function
void sim(double T_query, double T_update) {
  create("sim");
  init();
  double next_update_time = exponential(T_update); // Initialize next update time
  while (clock < SIMTIME) {
    if (uniform(0, 1) < 0.5) {
      cacheInvalidation();
    } else {
      cacheUpdate();
    }
    cacheQuery(T_query);

    if (clock >= next_update_time) {
      cacheUpdate();
      next_update_time += exponential(T_update); // Update next update time
    }
  }

  printf("Simulation completed.\n");
  printf("Cache hit ratio: %.2f\n", (double)cache_hit / (cache_hit + cache_miss));
  printf("Cache miss ratio: %.2f\n", (double)cache_miss / (cache_hit + cache_miss));
  printf("Average query delay: %.2f\n", query_delay / (cache_hit + cache_miss));
}


// Main function
int main() {
  double T_query, T_update;
  printf("Enter T_query: ");
  scanf("%lf", &T_query);
  printf("Enter T_update: ");
  scanf("%lf", &T_update);

  sim(T_query, T_update);
  
  hold(SIMTIME);
  
  return 0;
}