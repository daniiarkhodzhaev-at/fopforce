#include <grid.h>

#include <RandomNumberGenerator.h>

#include <iostream>

Grid::Grid(const Settings &settings)
    : mesh(), settings(settings)
{
    unsigned i_x, i_y, i_z;
    for (i_x = 0; i_x < settings.x_size; ++i_x) {
        for (i_y = 0; i_y < settings.y_size; ++i_y) {
            for (i_z = 0; i_z < settings.z_size; ++i_z) {
                mesh.push_back(Cell(i_x * settings.lattice,
                                    i_y * settings.lattice,
                                    i_z * settings.lattice,
                                    settings.lattice));
                another_mesh.push_back(Cell((i_x + 0.5f) * settings.lattice,
                                    (i_y + 0.5f) * settings.lattice,
                                    (i_z + 0.5f) * settings.lattice,
                                    settings.lattice));
            }
        }
    }
}


Grid::~Grid() {}

void Grid::init() { /* TODO: add initial conditions */
    unsigned N = 10;
    unsigned i, j;

    RandomNumberGenerator rnd;

    for (i = 0; i < mesh.size(); ++i) {
        for (j = 0; j < N; ++j) {
            Cell *pCell = &(mesh[i]);
            pCell->addMember(Molecule{MoleculeType::GAS, 0, 0,
                             rnd.getRandomFloat(pCell->pos.x, pCell->pos.x + pCell->size),
                             rnd.getRandomFloat(pCell->pos.y, pCell->pos.y + pCell->size),
                             rnd.getRandomFloat(pCell->pos.z, pCell->pos.z + pCell->size),
                             rnd.getRandomFloat(0.0f, 0.1f),
                             rnd.getRandomFloat(0.0f, 0.1f),
                             rnd.getRandomFloat(0.0f, 0.1f),});
        }
    }
}

void Grid::update(float fps) {
    unsigned i;
    for (i = 0; i < mesh.size(); ++i) {
        Cell *pCell = &(mesh[i]);
        for (auto it = pCell->particles.begin(); it != pCell->particles.end(); ++it) {
            it->second.update(fps);
            if (!pCell->particleInCell(it->second)) {
                pCell->removeMember(it);
                for (auto pCell : getCellNeighboursMesh(i)) {
                    if (pCell->particleInCell(it->second)) {
                        pCell->addMember(it->second);
                        break;
                    }
                }
            }
        }
    }
    for (i = 0; i < another_mesh.size(); ++i) {
        Cell *pCell = &(another_mesh[i]);
        for (auto it = pCell->particles.begin(); it != pCell->particles.end(); ++it) {
            if (!pCell->particleInCell(it->second)) {
                pCell->removeMember(it);
                for (auto pCell : getCellNeighboursAnotherMesh(i)) {
                    if (pCell->particleInCell(it->second)) {
                        pCell->addMember(it->second);
                        break;
                    }
                }
            }
        }
    }
}

std::list<Cell *> Grid::getCellNeighboursMesh(const int cellPos) {
    std::list<Cell *> ans;
    int a = settings.z_size;
    int b = settings.y_size;
    int i, j, k;

    for (k = -1; k < 2; ++k) {
        for (i = -1; i < 2; ++i) {
            for (j = -1; j < 2; ++j) {
                if (i == 0 && j == 0 && k == 0) {
                    continue;
                }
                if (0 < cellPos + i + a*j + a*b*k && (unsigned)(cellPos + i + a*j + a*b*k) < mesh.size()) {
                    ans.push_back(&(mesh[cellPos + i + a*j + a*b*k]));
                }
            }
        }
    }

    return ans;
}

std::list<Cell *> Grid::getCellNeighboursAnotherMesh(const int cellPos) {
    std::list<Cell *> ans;
    int a = settings.z_size;
    int b = settings.y_size;
    int i, j, k;

    for (k = -1; k < 2; ++k) {
        for (i = -1; i < 2; ++i) {
            for (j = -1; j < 2; ++j) {
                if (i == 0 && j == 0 && k == 0) {
                    continue;
                }
                if (0 < cellPos + i + a*j + a*b*k && (unsigned)(cellPos + i + a*j + a*b*k) < another_mesh.size()) {
                    ans.push_back(&(another_mesh[cellPos + i + a*j + a*b*k]));
                }
            }
        }
    }

    return ans;
}
