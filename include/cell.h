#ifndef __CELL_H__
#define __CELL_H__

#include <molecule.h>

#include <unordered_map>

class Cell {
    std::unordered_multimap<MoleculeType, Molecule> pastMembers, futureMembers;
};

#endif /* __CELL_H__ */
