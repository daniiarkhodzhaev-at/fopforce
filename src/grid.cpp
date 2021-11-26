#include <grid.h>

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
                mesh.push_back(Cell((i_x + 0.5f) * settings.lattice,
                                    (i_y + 0.5f) * settings.lattice,
                                    (i_z + 0.5f) * settings.lattice,
                                    settings.lattice));
            }
        }
    }
}


Grid::~Grid() {}

void Grid::setup(std::list<Molecule> molecules) {
    for (auto molecule : molecules) {
        int id = get_id(molecule.x, molecule.y, molecule.z, settings.y_size, settings.z_size, settings.lattice);

        mesh[id].addMember(molecule);
    }
}
