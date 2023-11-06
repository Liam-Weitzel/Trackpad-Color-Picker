#include <strings.h>

#include <iostream>

#include "hyprmag.hpp"

static void help(void) {
    std::cout << "Hyprmag usage: hyprmag [arg [...]].\n\nArguments:\n"
              << " -h | --help              | Show this help message\n"
              << " -i | --render-inactive   | Render (freeze) inactive displays\n";
}

int main(int argc, char** argv, char** envp) {
    g_pHyprmag = std::make_unique<CHyprmag>();

    while (true) {
        int                  option_index   = 0;
        static struct option long_options[] = {{"help", no_argument, NULL, 'h'},
                                               {"render-inactive", no_argument, NULL, 'i'},
                                               {NULL, 0, NULL, 0}};

        int                  c = getopt_long(argc, argv, ":hr", long_options, &option_index);
        if (c == -1)
            break;

        switch (c) {
            case 'h': help(); exit(0);
            case 'i': g_pHyprmag->m_bRenderInactive = true; break;

            default: help(); exit(1);
        }
    }

    g_pHyprmag->init();

    return 0;
}
