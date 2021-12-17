#ifndef __GRID_H__
#define __GRID_H__

#include <cell.h>
#include <molecule.h>
#include <settings.h>

#include <tuple>
#include <vector>
#include <list>

class Grid {
public:
    std::vector<Cell> mesh;
    std::vector<Cell> another_mesh;
private:
    Settings settings;
    std::vector<Molecule *> molecules_pull;

    std::list<Cell *> getCellNeighboursMesh(const int cellPos);
    std::list<Cell *> getCellNeighboursAnotherMesh(const int cellPos);

public:
    std::list<Molecule> listNeighbours(const Cell &) const;
    std::list<Molecule> listNeighbours(const Molecule &) const;

    std::list<Molecule> listNeighboursType(const Cell &, const MoleculeType) const;
    std::list<Molecule> listNeighboursType(const Molecule &) const;

    Grid(const Settings &settings);

    void init();

    void update(float fps);

    std::tuple<float, float, float> getOffsets() const;

    std::pair<int, int> getId(const Molecule &);

    ~Grid();
};

#endif /* __GRID_H__ */
