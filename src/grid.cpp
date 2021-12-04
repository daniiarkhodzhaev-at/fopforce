#include <grid.h>

#include <RandomNumberGenerator.h>

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

    for (i = 0; i < mesh.size(); ++i) {
        for (j = 0; j < N; ++j) {
            Cell *pCell = &(mesh[i]);
            pCell->addMember(Molecule(MoleculeType::GAS, 0, 0,
                             getRandomFloat(pCell->pos.x, pCell->pos.x + pCell->size),
                             getRandomFloat(pCell->pos.y, pCell->pos.y + pCell->size),
                             getRandomFloat(pCell->pos.z, pCell->pos.z + pCell->size),
                             getRandomFloat(0.0f, 0.1f),
                             getRandomFloat(0.0f, 0.1f),
                             getRandomFloat(0.0f, 0.1f),));
        }
    }
}

void Grid::update(float fps) {
    unsigned i;
    for (i = 0; i < mesh.size(); ++i) {
        Cell *pCell = &(mesh[i]);
        for (auto it = pCell->particles.begin(); it != pCell->particles.end(); ++it) {
            it->update();
            if (!pCell->particleInCell(it->second)) {
                pCell->removeMember(it);
                for (auto &cell : getCellNeighboursMesh(i)) {
                    if (cell.particleInCell(it->second)) {
                        cell.addMember(it->second);
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
                for (auto &pCell : getCellNeighboursAnotherMesh(i)) {
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

    if (0 < cellPos - 1 < mesh.size()) {
        ans.insert(&(mesh[cellPos - 1]));
    }
    if (0 < cellPos + 1 < mesh.size()) {
        ans.insert(&(mesh[cellPos + 1]));
    }
    if (0 < cellPos - a < mesh.size()) {
        ans.insert(&(mesh[cellPos - a]));
    }
    if (0 < cellPos + a < mesh.size()) {
        ans.insert(&(mesh[cellPos + a]));
    }
    if (0 < cellPos - 1 - a < mesh.size()) {
        ans.insert(&(mesh[cellPos - 1 - a]));
    }
    if (0 < cellPos + 1 - a < mesh.size()) {
        ans.insert(&(mesh[cellPos + 1 - a]));
    }
    if (0 < cellPos - 1 + a < mesh.size()) {
        ans.insert(&(mesh[cellPos - 1 + a]));
    }
    if (0 < cellPos + 1 + a < mesh.size()) {
        ans.insert(&(mesh[cellPos + 1 + a]));
    }

    if (0 < cellPos - a*b < mesh.size()) {
        ans.insert(&(mesh[cellPos - a*b]));
    }
    if (0 < cellPos - 1 - a*b < mesh.size()) {
        ans.insert(&(mesh[cellPos - 1 - a*b]));
    }
    if (0 < cellPos + 1 - a*b < mesh.size()) {
        ans.insert(&(mesh[cellPos + 1 - a*b]));
    }
    if (0 < cellPos - a - a*b < mesh.size()) {
        ans.insert(&(mesh[cellPos - a - a*b]));
    }
    if (0 < cellPos + a - a*b < mesh.size()) {
        ans.insert(&(mesh[cellPos + a - a*b]));
    }
    if (0 < cellPos - 1 - a - a*b < mesh.size()) {
        ans.insert(&(mesh[cellPos - 1 - a - a*b]));
    }
    if (0 < cellPos + 1 - a - a*b < mesh.size()) {
        ans.insert(&(mesh[cellPos + 1 - a - a*b]));
    }
    if (0 < cellPos - 1 + a - a*b < mesh.size()) {
        ans.insert(&(mesh[cellPos - 1 + a - a*b]));
    }
    if (0 < cellPos + 1 + a - a*b < mesh.size()) {
        ans.insert(&(mesh[cellPos + 1 + a - a*b]));
    }

    if (0 < cellPos + a*b < mesh.size()) {
        ans.insert(&(mesh[cellPos + a*b]));
    }
    if (0 < cellPos - 1 + a*b < mesh.size()) {
        ans.insert(&(mesh[cellPos - 1 + a*b]));
    }
    if (0 < cellPos + 1 + a*b < mesh.size()) {
        ans.insert(&(mesh[cellPos + 1 + a*b]));
    }
    if (0 < cellPos - a + a*b < mesh.size()) {
        ans.insert(&(mesh[cellPos - a + a*b]));
    }
    if (0 < cellPos + a + a*b < mesh.size()) {
        ans.insert(&(mesh[cellPos + a + a*b]));
    }
    if (0 < cellPos - 1 - a + a*b < mesh.size()) {
        ans.insert(&(mesh[cellPos - 1 - a + a*b]));
    }
    if (0 < cellPos + 1 - a + a*b < mesh.size()) {
        ans.insert(&(mesh[cellPos + 1 - a + a*b]));
    }
    if (0 < cellPos - 1 + a + a*b < mesh.size()) {
        ans.insert(&(mesh[cellPos - 1 + a + a*b]));
    }
    if (0 < cellPos + 1 + a + a*b < mesh.size()) {
        ans.insert(&(mesh[cellPos + 1 + a + a*b]));
    }

    return ans;
}

std::list<Cell *> Grid::getCellNeighboursAnotherMesh(const int cellPos) {
    std::list<Cell *> ans;
    int a = settings.z_size;
    int b = settings.y_size;

    if (0 < cellPos - 1 < another_mesh.size()) {
        ans.insert(&(another_mesh[cellPos - 1]));
    }
    if (0 < cellPos + 1 < another_mesh.size()) {
        ans.insert(&(another_mesh[cellPos + 1]));
    }
    if (0 < cellPos - a < another_mesh.size()) {
        ans.insert(&(another_mesh[cellPos - a]));
    }
    if (0 < cellPos + a < another_mesh.size()) {
        ans.insert(&(another_mesh[cellPos + a]));
    }
    if (0 < cellPos - 1 - a < another_mesh.size()) {
        ans.insert(&(another_mesh[cellPos - 1 - a]));
    }
    if (0 < cellPos + 1 - a < another_mesh.size()) {
        ans.insert(&(another_mesh[cellPos + 1 - a]));
    }
    if (0 < cellPos - 1 + a < another_mesh.size()) {
        ans.insert(&(another_mesh[cellPos - 1 + a]));
    }
    if (0 < cellPos + 1 + a < another_mesh.size()) {
        ans.insert(&(another_mesh[cellPos + 1 + a]));
    }

    if (0 < cellPos - a*b < another_mesh.size()) {
        ans.insert(&(another_mesh[cellPos - a*b]));
    }
    if (0 < cellPos - 1 - a*b < another_mesh.size()) {
        ans.insert(&(another_mesh[cellPos - 1 - a*b]));
    }
    if (0 < cellPos + 1 - a*b < another_mesh.size()) {
        ans.insert(&(another_mesh[cellPos + 1 - a*b]));
    }
    if (0 < cellPos - a - a*b < another_mesh.size()) {
        ans.insert(&(another_mesh[cellPos - a - a*b]));
    }
    if (0 < cellPos + a - a*b < another_mesh.size()) {
        ans.insert(&(another_mesh[cellPos + a - a*b]));
    }
    if (0 < cellPos - 1 - a - a*b < another_mesh.size()) {
        ans.insert(&(another_mesh[cellPos - 1 - a - a*b]));
    }
    if (0 < cellPos + 1 - a - a*b < another_mesh.size()) {
        ans.insert(&(another_mesh[cellPos + 1 - a - a*b]));
    }
    if (0 < cellPos - 1 + a - a*b < another_mesh.size()) {
        ans.insert(&(another_mesh[cellPos - 1 + a - a*b]));
    }
    if (0 < cellPos + 1 + a - a*b < another_mesh.size()) {
        ans.insert(&(another_mesh[cellPos + 1 + a - a*b]));
    }

    if (0 < cellPos + a*b < another_mesh.size()) {
        ans.insert(&(another_mesh[cellPos + a*b]));
    }
    if (0 < cellPos - 1 + a*b < another_mesh.size()) {
        ans.insert(&(another_mesh[cellPos - 1 + a*b]));
    }
    if (0 < cellPos + 1 + a*b < another_mesh.size()) {
        ans.insert(&(another_mesh[cellPos + 1 + a*b]));
    }
    if (0 < cellPos - a + a*b < another_mesh.size()) {
        ans.insert(&(another_mesh[cellPos - a + a*b]));
    }
    if (0 < cellPos + a + a*b < another_mesh.size()) {
        ans.insert(&(another_mesh[cellPos + a + a*b]));
    }
    if (0 < cellPos - 1 - a + a*b < another_mesh.size()) {
        ans.insert(&(another_mesh[cellPos - 1 - a + a*b]));
    }
    if (0 < cellPos + 1 - a + a*b < another_mesh.size()) {
        ans.insert(&(another_mesh[cellPos + 1 - a + a*b]));
    }
    if (0 < cellPos - 1 + a + a*b < another_mesh.size()) {
        ans.insert(&(another_mesh[cellPos - 1 + a + a*b]));
    }
    if (0 < cellPos + 1 + a + a*b < another_mesh.size()) {
        ans.insert(&(another_mesh[cellPos + 1 + a + a*b]));
    }

    return ans;
}
