#ifndef FOPFORCE_SETTINGS_H
#define FOPFORCE_SETTINGS_H


class Settings {
public:
    unsigned x_size;
    unsigned y_size;
    unsigned z_size;
    float lattice;

    Settings();

    ~Settings();
};


#endif //FOPFORCE_SETTINGS_H
