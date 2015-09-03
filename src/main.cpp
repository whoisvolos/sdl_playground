#include <iostream>
#include <string>
#include <SDL.h>
#include "AppContainer.h"
#include "SpacexContainer.h"
#include "modelRenderer/ModelRenderer.h"

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cerr << "Specify path to model as 1st argument" << std::endl;
        return 1;
    }
    //auto *concreteCont = new SpacexContainer("Spacex");
    auto concreteCont = new ModelRenderer("Model renderer", argv[1]);
    AppContainer& container = *concreteCont;

    int result = 0;
    if ((result = container.init(640, 480)) != 0) {
        delete concreteCont;
        return result;
    }

    container.run();

    delete concreteCont;
    return 0;
}