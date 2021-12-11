#ifndef __MOLECULE_H__
#define __MOLECULE_H__


#include <settings.h>

#include <vector>
#include <cmath>


enum class MoleculeType {
    INVALID = 0,
    GAS,
};


class Molecule {
public:
    MoleculeType type;

    float m;
    float q;

    bool updated;
    bool to_del;

    union {
        struct {
            float x;
            float y;
            float z;
        };
        float r[3];
    };
    union {
        struct {
            float vx;
            float vy;
            float vz;
        };
        float v[3];
    };
    union {
        struct {
            float ax;
            float ay;
            float az;
        };
        float a[3];
    };

    Molecule(MoleculeType type, float m, float q,
             float x, float y, float z,
             float vx, float vy, float vz,
             float ax, float ay, float az
            );

    Molecule(MoleculeType type, float m, float q,
             float x, float y, float z,
             float vx, float vy, float vz
            );

    ~Molecule();

    void update(float fps);
};


#endif /* __MOLECULE_H__*/
