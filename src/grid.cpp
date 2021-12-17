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


Grid::~Grid() {
    for (Molecule *tmp : molecules_pull) {
        delete tmp;
    }
}

void Grid::init() { /* TODO: add initial conditions */
    unsigned N = 10;
    unsigned i, j;
    Molecule *tmp;
    Cell *pCell;
    std::pair<int, int> cellIds;

    RandomNumberGenerator rnd;

    for (i = 0; i < mesh.size(); ++i) {
        for (j = 0; j < N; ++j) {
            pCell =&(mesh[i]);
            tmp = new Molecule(MoleculeType::GAS, 0, 0,
                               rnd.getRandomFloat(pCell->pos.x, pCell->pos.x + pCell->size),
                               rnd.getRandomFloat(pCell->pos.y, pCell->pos.y + pCell->size),
                               rnd.getRandomFloat(pCell->pos.z, pCell->pos.z + pCell->size),
                               rnd.getRandomFloat(0.0f, 0.1f),
                               rnd.getRandomFloat(0.0f, 0.1f),
                               rnd.getRandomFloat(0.0f, 0.1f));
            cellIds = getId(*tmp);
            molecules_pull.push_back(tmp);
            if (cellIds.first != -1) {
                mesh[cellIds.first].addMember(tmp);
            }
            if (cellIds.second != -1) {
                another_mesh[cellIds.second].addMember(tmp);
            }
        }
    }
}

std::pair<int, int> Grid::getId(const Molecule &molecule) {
    std::pair<int, int> res;
    float x, y, z, scale;
    int y_size, z_size,
        i_x, i_y, i_z, n, k;

    x = molecule.x;
    y = molecule.y;
    z = molecule.z;
    y_size = settings.y_size;
    z_size = settings.z_size;
    scale = settings.lattice;

    i_x = static_cast<int>(std::floor(x / scale));
    i_y = static_cast<int>(std::floor(y / scale));
    i_z = static_cast<int>(std::floor(z / scale));
    n = i_x * y_size * z_size + i_y * z_size + i_z;

    i_x = static_cast<int>(std::floor(x / scale - 0.5f));
    i_y = static_cast<int>(std::floor(y / scale - 0.5f));
    i_z = static_cast<int>(std::floor(z / scale - 0.5f));
    k =  i_x * y_size * z_size + i_y * z_size + i_z;

    res = std::make_pair(n >= 0 ? n : -1, k >= 0 ? k : -1);

    return res;
}

void Grid::update(float fps) {
    unsigned i;
    for (i = 0; i < mesh.size(); ++i) {
        Cell *pCell = &(mesh[i]);
        for (auto it = pCell->particles.begin(); it != pCell->particles.end(); ++it) {
            if (!it->second->updated) {
                it->second->update(fps);
                if (!pCell->particleInCell(it->second)) {
                    it->second->to_del = true;
                    auto cellIds = getId(*(it->second));
                    if (cellIds.first != -1) {
                        mesh[i].addMember(it->second);
                    }
                }
            }
        }
        std::erase_if(pCell->particles, [](const auto &data) { return data.second->to_del; });
    }
    for (i = 0; i < another_mesh.size(); ++i) {
        Cell *pCell = &(another_mesh[i]);
        for (auto it = pCell->particles.begin(); it != pCell->particles.end(); ++it) {
            if (!it->second->updated) {
                it->second->update(fps);
                if (!pCell->particleInCell(it->second)) {
                    it->second->to_del = true;
                    auto cellIds = getId(*(it->second));
                    if (cellIds.second != -1) {
                        another_mesh[i].addMember(it->second);
                    }
                }
            }
        }
        std::erase_if(pCell->particles, [](const auto &data) { return data.second->to_del; });
    }
    for (auto pMol : molecules_pull) {
        pMol->updated = false;
    }
}
