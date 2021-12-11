#include <molecule.h>

Molecule::Molecule(MoleculeType type, float m, float q,
             float x, float y, float z,
             float vx, float vy, float vz,
             float ax, float ay, float az
            )
    : type(type)
    , m(m)
    , q(q)
    , updated(false)
    , to_del(false)
    , x(x)
    , y(y)
    , z(z)
    , vx(vx)
    , vy(vy)
    , vz(vz)
    , ax(ax)
    , ay(ay)
    , az(az)
{}

Molecule::Molecule(MoleculeType type, float m, float q,
             float x, float y, float z,
             float vx, float vy, float vz
            ) : Molecule(type, m, q,
                         x, y, z,
                         vx, vy, vz,
                         0, 0, 0)
{}

Molecule::~Molecule() {}

void Molecule::update(float fps) {

    if (updated) {
        return;
    }

    unsigned i;
    float dt;

    dt = 1 / fps;

    for (i = 0; i < 3; ++i) {
        r[i] += v[i] * dt + a[i] * dt * dt / 2.0f;
        v[i] += a[i] * dt;
        a[i] = 0;
    }

    updated = true;
}
