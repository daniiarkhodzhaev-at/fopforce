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
    std::vector<Cell> another_mesh;
    Settings settings;

    std::list<Cell *> getCellNeighbours(const int cellPos) const;

public:
    std::list<Molecule> listNeighbours(const Cell &) const;
    std::list<Molecule> listNeighbours(const Molecule &) const;

    std::list<Molecule> listNeighboursType(const Cell &, const MoleculeType) const;
    std::list<Molecule> listNeighboursType(const Molecule &) const;

    Grid(const Settings &settings);

    void init();

    void update(float fps);

    ~Grid();
};

#endif /* __GRID_H__ */
