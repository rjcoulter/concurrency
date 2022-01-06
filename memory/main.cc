/**
 *   C++ Memory model
 * - All data in C++ made up of objects -> "Region of storage"
 *   - some objects are fundemntal values others are user defined types
 * - Objects are stored in one or more memory locations
 *   - Objects can contain subobjects
 * - 4 main takeaways
 *   1) Every variable is an object
 *   2) Every Object occupies at least on memory location
 *   3) Varaiables on fundemental types occupy exactly one memory location
 *   4) Adjacent bit fields are part of the same memory location
 *
 *   Objects, Memory Locations, and Conccurency
 * - Two threads can access seperate memory locations with no problems, if they access the same you have to be careful
 * - Needs to be a defined access pattern, ie a set ordering
 *   - can be done with something like a mutex
 *   - can also use atomic operations
 * - If there is no enforced ordering between two accesses to a single memory location from sperate threads, one or both of those accesses is not atomic, and one or both is a write, this is a race condition and will bring undefined behvaior
 *
 *
 *
 *

 **/
int main() 
{

}
