#include <molecule.h>


int* Molecule::update(float dt, Settings &settings) {
    int *res = new int[4];
    auto tmp = get_id(*this, settings);
    res[0] = tmp.first;
    res[2] = tmp.second;

    unsigned i;

    for (i = 0; i < 3; ++i) {
        r[i] += v[i] * dt + a[i] * dt * dt / 2.0f;
        v[i] += a[i] * dt;
        a[i] = 0;
    }

    tmp = get_id(*this, settings);
    res[1] = tmp.first;
    res[3] = tmp.second;

    return res;
}


std::pair<int, int> get_id(Molecule &molecule, Settings &settings) {
    std::pair<int, int> res;
    float x, y, z, scale;
    int y_size, z_size,
        i_x, i_y, i_z, n, k;

    x = molecule.x;
    y = molecule.y;
    z = molecule.z;
    y_size = settings.y_size;
    z_size = settings.z_size;
    scale = settings.lattice;

    i_x = static_cast<int>(std::floor(x / scale));
    i_y = static_cast<int>(std::floor(y / scale));
    i_z = static_cast<int>(std::floor(z / scale));
    n = i_x * y_size * z_size + i_y * z_size + i_z;

    i_x = static_cast<int>(std::floor(x / scale - 0.5f));
    i_y = static_cast<int>(std::floor(y / scale - 0.5f));
    i_z = static_cast<int>(std::floor(z / scale - 0.5f));
    k =  i_x * y_size * z_size + i_y * z_size + i_z;

    res = std::make_pair(n >= 0 ? 2 * n : -1, k >= 0 ? 2 * k + 1 : -1);

    return res;
}
