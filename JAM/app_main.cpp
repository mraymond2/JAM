#include "App.h"

int main(int argc, char** argv) {
    GlutApp* app = new App(argc, argv, 1000, 500, "JAM Studios");

    app->run();
}
