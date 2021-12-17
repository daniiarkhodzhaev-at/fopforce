#include <cell.h>

Cell::Cell(float x, float y, float z, float size)
    : pos({x, y, z})
    , size(size)
{}

Cell::~Cell() {}

void Cell::addMember(Molecule *pMolecule) {
    particles.insert({pMolecule->type, pMolecule});
}

void Cell::removeMember(Cell::mol_container::iterator it) {
    particles.erase(it);
}

bool Cell::particleInCell(Molecule *molecule) const {
    return (
                (pos.x < molecule->x && molecule->x < pos.x + size) &&
                (pos.y < molecule->y && molecule->y < pos.y + size) &&
                (pos.z < molecule->z && molecule->z < pos.z + size)
            );
}
