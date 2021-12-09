#ifndef __CELL_H__
#define __CELL_H__

#include <molecule.h>

#include <unordered_map>

class Cell {
public:
    std::unordered_multimap<MoleculeType, Molecule> particles;
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

    void addMember(const Molecule &);
    void removeMember(std::unordered_multimap<MoleculeType, Molecule>::iterator);

    bool particleInCell(const Molecule &) const;
};

#endif /* __CELL_H__ */
