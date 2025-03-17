#ifndef EEVEE_H
#define EEVEE_H

#include <string>

using namespace std;

class eevee {
    public:
        int hp = 55;
        int atk = 55;
        int def = 55;

        eevee();
        void tackle();
};

class enemy {
    public:
        int hp = 200;
        int atk = 300;
        int def = 0;

        enemy();
};

class Flareon : public eevee {
    public:
        Flareon();
        virtual void flamethrower();
};

class Jolteon : public eevee {
    public:
        Jolteon();
        virtual void thunderbolt();
};

class Vaporeon : public eevee {
    public:
        Vaporeon();
        virtual void hydro_pump();
};

class Glaceon : public eevee {
    public:
        Glaceon();
        virtual void blizzard();
};

class Leafeon : public eevee {
    public:
        Leafeon();
        virtual void solar_blade();
};

class Espeon : public eevee {
    public:
        Espeon();
        virtual void future_sight();
};

class Umbreon : public eevee {
    public:
        Umbreon();
        virtual void dark_pulse();
};

class Sylveon : public eevee {
    public:
        Sylveon();
        virtual void alluring_voice();
};

#endif /* EEVEE_H */