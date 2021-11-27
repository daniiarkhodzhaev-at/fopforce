#ifndef __GRID_H__
#define __GRID_H__

#include <cell.h>
#include <molecule.h>
#include <settings.h>

#include <vector>
#include <list>

class Grid {
private:
    std::vector<Cell> mesh;
    Settings settings;

public:
    std::list<Molecule> listNeighbours(const Cell &) const;
    std::list<Molecule> listNeighbours(const Molecule &) const;

    std::list<Molecule> listNeighboursType(const Cell &, const MoleculeType) const;
    std::list<Molecule> listNeighboursType(const Molecule &) const;

    Grid(const Settings &settings);

    void setup(std::list<Molecule> molecules);

    ~Grid();
};

#endif /* __GRID_H__ */
