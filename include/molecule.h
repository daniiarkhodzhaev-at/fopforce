#ifndef __MOLECULE_H__
#define __MOLECULE_H__

enum class MoleculeType {
    INVALID = 0,
    GAS,
};

class Molecule {
public:
    MoleculeType type;

    float m;
    float q;

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
             float ax, float ay, float az,
            );

    Molecule(MoleculeType type, float m, float q,
             float x, float y, float z,
             float vx, float vy, float vz,
            );

    ~Molecule();

    void update(float dt) {
        unsigned i;
        for (i = 0; i < 3; ++i) {
            r[i] += v[i] * dt + a[i] * dt * dt / 2.0f;
            v[i] += a[i] * dt;
            a[i] = 0;
        }
    }
};

#endif /* __MOLECULE_H__*/
