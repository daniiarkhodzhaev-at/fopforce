#include <cell.h>

Cell::Cell(float x, float y, float z, float size)
    : pos({x, y, z})
    , size(size)
{}

Cell::~Cell() {}

void Cell::addMember(const Molecule &molecule) {
    particles.insert({molecule.type, molecule});
}

void Cell::removeMember(std::unordered_multimap<MoleculeType, Molecule>::iterator it) {
    particles.erase(it);
}

bool Cell::particleInCell(const Molecule &molecule) const {
    return (
                (pos.x < molecule.x && molecule.x < pos.x + size) &&
                (pos.y < molecule.y && molecule.y < pos.y + size) &&
                (pos.z < molecule.z && molecule.z < pos.z + size)
            );
}
