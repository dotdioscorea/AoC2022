//
// Created by Aaron Rucinski on 14/12/2022.
//


struct position {
    int x = -1;
    int y = -1;
};

struct sand {
    position position;
};

struct rock {
    position start;
    position end;
};
