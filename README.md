# -A-Pull-based-Cache-Invalidation
## Introduction
To simulate a simple IR-based cache invalidation model using [CSIM](http://www.mesquite.com/).
 * Reference paper: [A Scalable Low-Latency Cache Invalidation Strategy for
Mobile Environments](http://www.cs.columbia.edu/~danr/courses/6762/Summer03/week13/mobile-cache.pdf)


 ## Getting Started
 ### Prerequisites
  * install [Code::Blocks](http://www.codeblocks.org/) and [C Programming Language](https://www.geeksforgeeks.org/c-language-set-1-introduction/)
  * install [CSIM](http://www.mesquite.com/)

### System Parameters
|  |  |
| --- | --- |
| Number of clients | 100 |
| Database size | 1000 items |
| Data item size | 1024 bytes |
| Broadcast interval (L) | 20 seconds |
| Broadcast bandwidth | 10000 bits/s |
| Cache size | 50 to 300 items |
| Mean query generate time (T_query) | 25s to 300s |
| Mean update arrival time (T_update) | 20s to 10000s |
| Hot data items | 1 to 50 |
| Cold data items | remainder of DB |
| Hot data access probability | 0.8 |
| Hot data update probability | 0.33|

### Simulation Model and Functions
| | **Main Functions** | **Utility Functions** |
| --- | --- | --- |
| **Server** | void update_data_items() | int is_duplicated() |
|        | void invalidation_report() | int get_list_size() |
|        | void receive_request() | void clear_list() |
|        |  | int get_list_size() |
| **Client** | void generate_query() |  int is_cached() |
|        | void receive_ir() | lnt get_oldest_valid() |
|        |  | int is_cache_full() |
|        |  | int get_oldest_invalid() |

 ### Compilation & Run
 ```python
 csim64.gcc project.c -o project
 ./project
 ```
 To show the simulation is running correctly in the below section, I simplify the parameters according to:
 * Number of clients is **3** 
 * Mean update arrival time (T_update) is **20s**
 * Mean query generate time (T_query) is **100s**
 * Simulation time is **50000**
 * Cache size is **100** items
 
  ### Run Simulation
  
* Specify T_update and T_query.
```python
Enter Mean update arrival time (T_update) in seconds:
20
You've entered T_update: 20
Enter Mean query generate time (T_query) in seconds:
100
You've entered T_query: 100
```

## References
- [CSIM - Official Documents](http://www.mesquite.com/documentation)
- [CSIM - Michigan State University](http://www.cse.msu.edu/~cse808/CSIM_Notes03/cse808/)
- [CSIM - University of Pittsburgh](http://www.pitt.edu/~dtipper/2120/CSIM_tutorial.pdf)
- [CSIM - The Chinese University of Hong Kong](http://www.cse.cuhk.edu.hk/~cslui/CSIM19/index.html)
- [CSIM - U of T](http://www.cs.toronto.edu/~iq/csc354s/)
- [VIM Tutorial](http://www.cse.msu.edu/~cse420/Tutorials/VIM/vim.tutorial)
- [Computer Architecture](https://www.cse.msu.edu/~cse420/)
- [Arrays in C](https://www.cs.swarthmore.edu/~newhall/unixhelp/C_arrays.html)
- [Organizing information in README.md with tables](https://help.github.com/en/articles/organizing-information-with-tables)
- [Markdown Cheatsheet](https://github.com/adam-p/markdown-here/wiki/Markdown-Cheatsheet)
