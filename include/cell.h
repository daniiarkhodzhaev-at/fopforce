#ifndef __CELL_H__
#define __CELL_H__

#include <molecule.h>

#include <unordered_map>

class Cell {
public:
    std::unordered_multimap<MoleculeType, Molecule> particles;
    union pos {
        struct {
            float x;
            float y;
            float z;
        };
        float r[3];
    };
    float size;

    Cell(float x, float y, float z, float size);

    void addMember(const Molecule &);
    void removeMember(const Molecule &);

    bool particleInCell(const Molecule &) const;
};

#endif /* __CELL_H__ */
