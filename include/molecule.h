#ifndef __MOLECULE_H__
#define __MOLECULE_H__

#include <vector>
#include <cmath>


enum class MoleculeType {
    INVALID = 0,
    GAS,
};


std::pair<int, int> get_id(float x, float y, float z, int y_size, int z_size, float scale){
    std::pair<int, int> res;
    int i_x, i_y, i_z, n, k;

    i_x = static_cast<int>(std::floor(x / scale));
    i_y = static_cast<int>(std::floor(y / scale));
    i_z = static_cast<int>(std::floor(z / scale));
    n = i_x * y_size * z_size + i_y * z_size + i_z;

    i_x = static_cast<int>(roundf(x / scale - 0.5f));
    i_y = static_cast<int>(roundf(y / scale - 0.5f));
    i_z = static_cast<int>(roundf(z / scale - 0.5f));
    k =  i_x * y_size * z_size + i_y * z_size + i_z;

    res = std::make_pair(2 * n, 2 * k + 1);

    return res;
}


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
             float ax, float ay, float az
            );

    Molecule(MoleculeType type, float m, float q,
             float x, float y, float z,
             float vx, float vy, float vz
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
