#ifndef __GRID_H__
#define __GRID_H__

#include <cell.h>
#include <molecule.h>

#include <vector>

class Grid {
private:
    std::vector<Cell> mesh;
    Settings settings;

public:
    /* TODO */
    /*  */ listNeighbours(const Cell &) const;
    /*  */ listNeighbours(const Molecule &) const;

    /*  */ listNeighboursType(const Cell &, const MoleculeType) const;
    /*  */ listNeighboursType(const Molecule &) const;
};

#endif /* __GRID_H__ */
