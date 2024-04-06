## DO: Practicum I

### Co-author: Yidan Cong, Quan Yuan(contributed equally)  
CS5600 / Northeastern University  
Spring 2024 / Mar 27, 2024
 
## To run the program from the shell:
1. Choose a cache replacement  mode  
    mode: 0 - random, 1 - LRU  
   `#define CACHE_REPLACEMENT_MODE 0`  
   `//#define CACHE_REPLACEMENT_MODE 1`  
   * Uncomment one mode to use  
        
 3. Run `make`
 4. Run `./practicum`  
 (The program executable is named 'practicum')
 5. Sample test is implemented in 'main.c'
 ## Description:
 *   This program initiates a caching system either using LRU or Random cache replacement strategy.
 *   In the 'main.c', the program conducts 10 rounds of writing and reading messages to disk and cache, each round writes and retrieves 100 messages.
 *   A total of 1,000 messages with unique identifier are created and stored to disk and cache.
 *   A total of 1,000 messages are retrieved randomly.
 *   The overall cache hit, cache misses, and cache hit ratio are displayed in the console.