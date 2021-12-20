#ifndef FOPFORCE_SETTINGS_H
#define FOPFORCE_SETTINGS_H


class Settings {
public:
    const unsigned x_size;
    const unsigned y_size;
    const unsigned z_size;
    const float lattice;

    Settings();

    ~Settings();
};


#endif //FOPFORCE_SETTINGS_H
