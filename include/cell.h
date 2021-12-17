#ifndef __CELL_H__
#define __CELL_H__

#include <molecule.h>

#include <map>

class Cell {
public:
    using mol_container = std::multimap<MoleculeType, Molecule *>;
    mol_container particles;
    /* left-up-smth (the most left in all directions) corner */
    union {
        struct {
            float x;
            float y;
            float z;
        };
        float r[3];
    } pos;
    float size;

    Cell(float x, float y, float z, float size);
    ~Cell();

    void addMember(Molecule *);
    void removeMember(mol_container::iterator);

    bool particleInCell(Molecule *) const;
};

#endif /* __CELL_H__ */
