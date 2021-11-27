#ifndef FOPFORCE_SETTINGS_H
#define FOPFORCE_SETTINGS_H


class Settings {
public:
    int x_size;
    int y_size;
    int z_size;
    float lattice;

    Settings(){
        x_size = 100;
        y_size = 100;
        z_size = 300;
        lattice = 20.0f;
    };
};


#endif //FOPFORCE_SETTINGS_H
