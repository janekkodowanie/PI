#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_REL_SIZE 100
#define MAX_RANGE 100

typedef struct {
    int first;
    int second;
} pair;

// Add pair to existing relation if not already there

int add_relation(pair*, int, pair);
// Case 1:

#define true 1
#define false 0

// The relation R is reflexive if xRx for every x in X
int is_reflexive(const pair* relation, int n) {
    for(int i = 0; i < n; i++) {
        int xRx = false;
        for(int j = 0; j < n; j++) {
            if((relation + j)->first == (relation + i)->first && (relation + j)->first == (relation + j)->second) {
                xRx = true;
                break;
            }
        }
        if(xRx == false) {
            return false;
        }
    }
    return true;
}

// The relation R on the set X is called irreflexive
// if xRx is false for every x in X
int is_irreflexive(const pair* relation, int n) {
    for(int i = 0; i < n; i++) {
        if((relation + i)->first == (relation + i)->second) {
            return false;
        }
    }
    return true;
}

// A binary relation R over a set X is symmetric if:
// for all x, y in X xRy <=> yRx
int is_symmetric(const pair* relation, int n) {
    for(int i = 0; i < n; i++) {
        int symmetric = false;
        for(int j = 0; j < n; j++) {
                                  /* xRy */                                          /* yRr */
            if((relation + i)->first == (relation + j)->second && (relation + j)->first == (relation + i)->second) {
                symmetric = true;
            }
        }
        if(symmetric == false) {
            return false;
        }
    }
    return true;
}

// A binary relation R over a set X is antisymmetric if:
// for all x,y in X if xRy and yRx then x=y
int is_antisymmetric(const pair* relation, int n) {

    for(int i = 0; i < n; i++) {
        int symmetric = false;
        for(int j = 0; j < n; j++) {
            /* xRy */                                                                /* yRr */
            if((relation + i)->first == (relation + j)->second && (relation + j)->first == (relation + i)->second) {
                if((relation + i)->first != (relation + i)->second) {
                    symmetric = true;
                }
            }
        }
        if(symmetric == true) {
            return false;
        }
    }
    return true;
}

// A binary relation R over a set X is asymmetric if:
// for all x,y in X if at least one of xRy and yRx is false
int is_asymmetric(const pair* relation, int n) {
    return (is_antisymmetric(relation, n) == true && is_irreflexive(relation, n) == true)
    ?
    true : false;
}

// A homogeneous relation R on the set X is a transitive relation if:
// for all x, y, z in X, if xRy and yRz, then xRz
int is_transitive(const pair* relation, int n) {
    int transitive;
    for(int i = 0; i < n; i++) {
        int x = (relation + i)->first;
        int y = (relation + i)->second;
        for(int j = 0; j < n; j++) {
            if((relation + j)->first == y) {
                int z = (relation + j)->second;
                transitive = false;
                for(int k = 0; k < n; k++) {
                    if((relation + k)->first == x && (relation + k)->second == z) {
                        transitive = true;
                    }
                }
                if(transitive == false) {
                    return false;
                }
            }
        }
    }
    return true;
}

// Case 2:

// A partial order relation is a homogeneous relation that is
// reflexive, transitive, and antisymmetric
int is_partial_order(const pair* relation, int n) {
    return (is_reflexive(relation, n) == true &&
            is_transitive(relation, n) == true &&
            is_antisymmetric(relation, n) == true)
    ?
    true : false;
}

// Relation R is connected if for each x, y in X:
// xRy or yRx (or both)
int is_connected(const pair* relation, int n) {
    int xRy, yRx;
    for(int i = 0; i < n; i++) {
        int x = (relation + i)->first;
        for(int j = 0; j < n; j++) {
            xRy = yRx = false;
            int y = (relation + j)->first;
            for(int k = 0; k < n; k++) {
                if((relation + k)->first == x && (relation + k)->second == y) {
                    xRy = true;
                    break;
                }
                if((relation + k)->first == y && (relation + k)->second == x) {
                    yRx = true;
                    break;
                }
            }
        }
        if(xRy == false && yRx == false) {
            return false;
        }
    }
    return true;
}

// A total order relation is a partial order relation that is connected
int is_total_order(const pair* relation, int n) {
    return is_partial_order(relation, n) && is_connected(relation, n) ? true : false;
}

int cmpf(const void * a, const void * b) {
    return (*(int *) a - *(int *) b);
}

int find_max_elements(const pair* relation, int n, int* maxElements) {
    int idx = 0, counter, alreadyIn;
    for(int i = 0; i < n; i++) {
        counter = 0;
        int x = (relation + i)->second;
        for(int j = 0; j < n; j++) {
            if((relation + j)->first == x && (relation + j)->first != (relation + j)->second) {
                counter++;
            }
        }
        if(counter != 0) {
            continue;
        }

        alreadyIn = false;
        for(int j = 0; j < idx; j++) {
            if(maxElements[j] == x) {
                alreadyIn = true;
            }
        }
        if(alreadyIn == false) {
            maxElements[idx++] = x;
        }
    }

    qsort(maxElements, idx, sizeof(int), cmpf);
    return idx;
}

int find_min_elements(const pair* relation, int n, int* minElements) {
    int idx = 0, counter, alreadyIn;
    for(int i = 0; i < n; i++) {
        counter = 0;
        int x = (relation + i)->first;
        for(int j = 0; j < n; j++) {
            if((relation + j)->second == x && (relation + j)->first != (relation + j)->second) {
                counter++;
            }
        }
        if(counter != 0) {
            continue;
        }

        alreadyIn = false;
        for(int j = 0; j < idx; j++) {
            if(minElements[j] == x) {
                alreadyIn = true;
            }
        }
        if(alreadyIn == false) {
            minElements[idx++] = x;
        }
    }

    qsort(minElements, idx, sizeof(int), cmpf);
    return idx;
}

int get_domain(const pair* relation, int n, int* domain) {
    int idx = 0, add;
    for(int i = 0; i < n; i++) {
        add = true;
        for(int j = 0; j < idx; j++) {
            if((relation + i)->first == *(domain + j)) {
                add = false;
            }
        }
        if(add == true) {
            domain[idx++] = (relation + i)->first;
        }

        add = true;
        for(int j = 0; j < idx; j++) {
            if((relation + i)->second == *(domain + j)) {
                add = false;
            }
        }
        if(add == true) {
            domain[idx++] = (relation + i)->second;
        }
    }

    qsort(domain, idx, sizeof(int), cmpf);
    return idx;
}

// Case 3:

int composition (const pair* R, int n1, const pair* S, int n2, pair* RmS) {
    int idx = 0, x, y, z, alreadyIn;

    for(int i = 0; i < n1; i++) {
        x = (R + i)->first;
        y = (R + i)->second;
        for(int j = 0; j < n2; j++) {
            if((S + j)->first == y) {
                z = (S + j)->second;
                alreadyIn = false;
                for(int k = 0; k < idx; k++) {
                    if((RmS + k)->first == x && (RmS + k)->second == z) {
                        alreadyIn = true;
                    }
                }

                if(alreadyIn == false) {
                    (RmS + idx)->first = x;
                    (RmS + idx)->second = z;
                    idx++;
                }
            }
        }
    }
    return idx;
}

// Add pair to existing relation if not already there
int add_relation (pair *tab, int n, pair new_pair) {
    for(int i = 0; i < n; i++) {
        if((tab + i)->first == new_pair.first && (tab + i)->second == new_pair.second) {
            return -1;
        }
    }
    tab[n] = new_pair;
    return 0;
}

// Read number of pairs, n, and then n pairs of ints
int read_relation(pair *relations) {
    int n;
    scanf("%d", &n);
    pair newPair;
    for(int i = 0; i < n; i++) {
        scanf("%d %d", &newPair.first, &newPair.second);
        relations[i] = newPair;
    }
    return n;
}

void print_int_array(const int *array, int n) {
    printf("%d\n", n);
    for(int i = 0; i < n; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

int main(void) {
    int to_do;
    pair relation[MAX_REL_SIZE];
    pair relation_2[MAX_REL_SIZE];
    pair comp_relation[MAX_REL_SIZE];
    int domain[MAX_REL_SIZE];
    int max_elements[MAX_REL_SIZE];
    int min_elements[MAX_REL_SIZE];

    scanf("%d",&to_do);
    int size = read_relation(relation);
    int ordered, size_2, n_domain;

    switch (to_do) {
        case 1:
            printf("%d ", is_reflexive(relation, size));
            printf("%d ", is_irreflexive(relation, size));
            printf("%d ", is_symmetric(relation, size));
            printf("%d ", is_antisymmetric(relation, size));
            printf("%d ", is_asymmetric(relation, size));
            printf("%d\n", is_transitive(relation, size));
            break;
        case 2:
            ordered = is_partial_order(relation, size);
            n_domain = get_domain(relation, size, domain);
            printf("%d %d\n", ordered, is_total_order(relation, size));
            print_int_array(domain, n_domain);
            if (!ordered) break;
            int no_max_elements = find_max_elements(relation, size, max_elements);
            int no_min_elements = find_min_elements(relation, size, min_elements);
            print_int_array(max_elements, no_max_elements);
            print_int_array(min_elements, no_min_elements);
            break;
        case 3:
            size_2 = read_relation(relation_2);
            printf("%d\n", composition(relation, size, relation_2, size_2, comp_relation));
            break;
        default:
            printf("NOTHING TO DO FOR %d\n", to_do);
            break;
    }
    return 0;
}