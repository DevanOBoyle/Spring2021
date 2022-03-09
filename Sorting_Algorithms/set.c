#include "set.h"

//code provided by Eugene Chou on Piazza

Set set_empty(void) {
    return 0x00000000; //empty set is 0s for each bit
}

bool set_member(Set s, int x) {
    return x & (1 << (x % SET_CAPACITY)); //adds an element x into set s
}

Set set_insert(Set s, int x) {
    return s
           | (1 << (x
                    % SET_CAPACITY)); //returns the union of an element x and s, so as not to have dublicates
}

Set set_remove(Set s, int x) {
    return s & ~(1 << (x % SET_CAPACITY)); //removes the element x from set s
}

Set set_union(Set s, Set t) {
    return s | t; //returns a combined set containing the elements from s and t
}

Set set_intersect(Set s, Set t) {
    return s & t; //returns a set containing elements that are in both s and t
}

Set set_difference(Set s, Set t) {
    return s & ~t; //returns a set containing elements that are in s and not in t
}

Set set_complement(Set s) {
    return ~s; //returns a set containging elements that are not in s a.k.a an empty set
}
